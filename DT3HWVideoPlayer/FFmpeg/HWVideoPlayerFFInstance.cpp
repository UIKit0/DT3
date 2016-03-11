//==============================================================================
///	
///	File: HWVideoPlayerFFInstance.cpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================
#include "DT3HWVideoPlayer/FFmpeg/HWVideoPlayerFFInstance.hpp"
#include "DT3HWVideoPlayer/FFmpeg/HWVideoPlayerFFDataSourceFile.hpp"
#include "DT3HWVideoPlayer/FFmpeg/HWVideoPlayerFFDataSourceURL.hpp"

#include "DT3Core/Types/Utility/Assert.hpp"
#include "DT3Core/Types/Utility/ConsoleStream.hpp"
#include "DT3Core/Types/Utility/TimerHires.hpp"
#include "DT3Core/Types/Math/MoreMath.hpp"
#include "DT3Core/System/System.hpp"
#include "DT3Core/Devices/DeviceAudio.hpp"
#include "DT3Core/Devices/DeviceGraphics.hpp"

#include <chrono>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
//==============================================================================

const DTint     MIN_NUM_PACKETS_TARGET = 2048;

const DTint     AUDIO_FREQUENCY = 44100;
const DTint     AUDIO_BUFFER_SIZE = 1024*32;    // 32k chunks of audio data
const DTdouble  AUDIO_READ_AHEAD = 1.0;         // How much audio is read ahead of time
const DTdouble  VIDEO_READ_AHEAD = 1.0/30.0;    // How much video is read ahead of time

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

HWVideoPlayerFFInstance::HWVideoPlayerFFInstance (void)
    :   _data_source                    (NULL),
        _src_frame                      (NULL),
        _src_audio_frame                (NULL),
        _state                          (STATE_IDLE),
        _img_convert_ctx                (NULL),
        _snd_convert_ctx                (NULL),
        _current_time                   (0.0),
        _first_audio_timestamp          (0.0),
        _first_audio_timestamp_set      (false),
        _dst_frame_read_buffer_index    (0),
        _dst_frame_buffer_dirty         (false),
        _playback_thread_running        (false),
        _data_thread_running            (false)
{
    _dst_frame[0] = NULL;
    _dst_frame[1] = NULL;

    _dst_frame_buffer[0] = NULL;
    _dst_frame_buffer[1] = NULL;

    _sound_source = SoundSourceQueue::create();
    _sound_source->set_ends_on_empty(false);
}

HWVideoPlayerFFInstance::~HWVideoPlayerFFInstance (void)
{
    close();
}

//==============================================================================
//==============================================================================

DTerr HWVideoPlayerFFInstance::open (const FilePath &path)
{
    close();
    
    // Open Data source
    auto data_source = std::shared_ptr<HWVideoPlayerFFDataSourceFile>::make_shared();
    DTerr err = data_source->open(path);
    if (err != DT3_ERR_NONE) {
        _state = STATE_ERROR;
        return err;
    }
    

    // Data source is opened, open player
    err = open_common(data_source);
    if (err != DT3_ERR_NONE) {
        _state = STATE_ERROR;
        return err;
    }
    
    // Final setup
    _data_source = data_source;
    
    // Spool up worker threads
    _data_thread_running = true;
    _playback_thread_running = true;

    _data_thread = std::thread(&HWVideoPlayerFFInstance::data_thread, this);
    _playback_thread = std::thread(&HWVideoPlayerFFInstance::playback_thread, this);

    pause();
    
    return DT3_ERR_NONE;
}

DTerr HWVideoPlayerFFInstance::open (const URL &url)
{
    close();
    
    // Open Data source
    auto data_source = std::shared_ptr<HWVideoPlayerFFDataSourceURL>::make_shared();
    DTerr err = data_source->open(url);
    if (err != DT3_ERR_NONE) {
        _state = STATE_ERROR;
        return err;
    }

    // Data source is opened, open player
    err = open_common(data_source);
    if (err != DT3_ERR_NONE) {
        _state = STATE_ERROR;
        return err;
    }

    // Final setup
    _data_source = data_source;
    
    // Spool up worker threads
    _data_thread_running = true;
    _playback_thread_running = true;

    _data_thread = std::thread(&HWVideoPlayerFFInstance::data_thread, this);
    _playback_thread = std::thread(&HWVideoPlayerFFInstance::playback_thread, this);

    pause();

    return DT3_ERR_NONE;
}

void HWVideoPlayerFFInstance::close (void)
{
    pause();
    
    
    close_common();

    if (_data_source) {
        _data_source->close();
        _data_source.reset();
    }
}

//==============================================================================
//==============================================================================

DTerr HWVideoPlayerFFInstance::open_common (std::shared_ptr<HWVideoPlayerFFDataSourceBase> data_source)
{
    //
    // Open the stream
    //
    
    AVFormatContext *format_context = data_source->format_context();
    AVCodecContext *video_codec_context = data_source->video_codec_context();
    AVCodecContext *audio_codec_context = data_source->audio_codec_context();
    AVStream *video_stream = data_source->video_stream();
    AVStream *audio_stream = data_source->audio_stream();

    //
    // Get video parameters
    //
    
    // Reset the playhead and get movie duration
    _length = (DTdouble) format_context->duration / (DTdouble) AV_TIME_BASE;
    
    // Timebase
    _video_time_base = ::av_q2d(video_stream->time_base);
    _video_time_start = video_stream->start_time;

    if (audio_stream) {
        _audio_time_base = ::av_q2d(audio_stream->time_base);
        _audio_time_start = audio_stream->start_time;
    }

    // Get dimensions
    _width = video_codec_context->width;
    _height = video_codec_context->height;

    
    //
    // Build software scaler
    //
    
    // Software scaler
    _img_convert_ctx = ::sws_getContext(    _width, _height, video_codec_context->pix_fmt,
                                            _width, _height, AV_PIX_FMT_RGBA,
                                            SWS_POINT,
                                            NULL, NULL, NULL);

    //
    // Build audio resampler
    //
    
    // Software scaler
    if (audio_codec_context) {
        _snd_convert_ctx = ::swr_alloc_set_opts	(	NULL,
                                                    AV_CH_LAYOUT_STEREO, AV_SAMPLE_FMT_S16, AUDIO_FREQUENCY,
                                                    audio_codec_context->channel_layout,
                                                    audio_codec_context->sample_fmt,
                                                    audio_codec_context->sample_rate,
                                                    0, NULL);

        ::swr_init(_snd_convert_ctx);
    }
    
    
    //
    // Allocate source frame
    //

    _src_frame = ::avcodec_alloc_frame();
    if (!_src_frame) {
        return DT3_ERR_FILE_OPEN_FAILED;
    }
    

    //
    // Allocate destination frame
    //

    // Allocate a texture to hold the final frames
    DTsize size = ::avpicture_get_size(AV_PIX_FMT_RGBA, _width, _height);

    for (DTuint i = 0; i < 2; ++i) {
        _dst_frame[i] = ::avcodec_alloc_frame();
        if (!_dst_frame[i]) {
            return DT3_ERR_FILE_OPEN_FAILED;
        }
    
        // Aligned allocator
        _dst_frame_buffer[i] = ::av_mallocz(size);

        // Associate frame to buffer
        ::avpicture_fill( (AVPicture *) _dst_frame[i], (DTubyte*) _dst_frame_buffer[i], AV_PIX_FMT_RGBA, _width, _height);
    
        // Flip the frame
        for (DTint j = 0; j < 4; ++j) {
            _dst_frame[i]->data[j] += _dst_frame[i]->linesize[j] * (_height-1);
            _dst_frame[i]->linesize[j] = -_dst_frame[i]->linesize[j];
        }
    }
    
    // Setup textures manually for low level access
    _tex_raw = System::renderer()->create_texture_2D(_width, _height, (DTubyte*) _dst_frame_buffer[0], DT3GL_FORMAT_RGBA, false, DT3GL_ACCESS_CPU_WRITE | DT3GL_ACCESS_GPU_READ);
    _tex_resource = TextureResource2D::create();
    _tex_resource->set_resource_textels(_tex_raw);

    //
    // Allocate destination audio frame
    //
    
    _src_audio_frame = ::avcodec_alloc_frame();
    if (!_src_audio_frame) {
        return DT3_ERR_FILE_OPEN_FAILED;
    }

    // Now in the loaded state
    _state = STATE_PAUSED;
    
    return DT3_ERR_NONE;
}

void HWVideoPlayerFFInstance::close_common (void)
{
    if (_data_source) {
        AVCodecContext *audio_codec_context = _data_source->audio_codec_context();
        if (audio_codec_context) {
            System::audio_renderer()->stop(_sound_source);
            _sound_source->clear_packets();
        }
    }

    // Set state to closing
    _state = STATE_CLOSING;
    
    while (_playback_thread_running || _playback_thread.joinable()) {
        _playback_thread_condition.notify_one();
        if (_playback_thread.joinable())
            _playback_thread.join();
    }
    
    while (_data_thread_running || _data_thread.joinable()) {
        _data_thread_condition.notify_one();
        if (_data_thread.joinable())
            _data_thread.join();
    }
    
    _video_packet_queue.clear();
    _audio_packet_queue.clear();

    // Free scaler context
    if (_img_convert_ctx)   {   ::sws_freeContext(_img_convert_ctx);    _img_convert_ctx = NULL;    }
    if (_snd_convert_ctx)   {   ::swr_free(&_snd_convert_ctx);          _snd_convert_ctx = NULL;    }

    // Free the frames
    ::av_frame_free(&_src_frame);
    ::av_frame_free(&_src_audio_frame);

    for (DTuint i = 0; i < 2; ++i) {
        ::av_frame_free(&_dst_frame[i]);

        ::av_free(_dst_frame_buffer[i]);
        _dst_frame_buffer[i] = NULL;
    }
    
    _data_source.reset();
    
    _tex_resource.reset();
    _tex_raw.reset();

    _state = STATE_IDLE;
}

//==============================================================================
// This is the data thread!!
//==============================================================================

void HWVideoPlayerFFInstance::data_thread (void)
{
    //
    // Fill up the packet queue
    //
    
    AVFormatContext *format_context = _data_source->format_context();
    
    DTint video_stream_index = _data_source->video_stream_index();
    DTint audio_stream_index = _data_source->audio_stream_index();

    AVPacket packet;
    ::av_init_packet(&packet);
    
    while (_state != STATE_CLOSING) {
    
        DTboolean command_processed = false;
        DTboolean packet_processed = false;
    
        //
        // Read in commands
        //
        
        HWVideoPlayerFFCommandQueue::Command command;
        DTdouble param;
        
        while (_data_command_queue.pop_command(command, param)) {
        
            switch (command) {
            
                case HWVideoPlayerFFCommandQueue::CMD_PLAY: {
                    
                    // Seeking cases all of the packets to be flushed
                    _video_packet_queue.clear();
                    _audio_packet_queue.clear();
                    
                    _video_packet_queue.push_back_flush();
                    _audio_packet_queue.push_back_flush();
                    
                    // Seek the data source
                    int64_t tc_pos = (_current_time + _first_audio_timestamp) * AV_TIME_BASE;
                    
                    DTint err = ::av_seek_frame(    format_context, -1,
                                                    tc_pos,
                                                    (param < current_time() ?  AVSEEK_FLAG_BACKWARD : 0));    // Should flag be AVSEEK_FLAG_BACKWARD?
                    if (err < 0) {
                        LOG_MESSAGE << "Unable to seek";
                    }
                    
                    _state = STATE_PLAYING;

                    // Bump the playback thread so it'll process the data packet
                    _playback_thread_condition.notify_one();
                    
                } break;

                case HWVideoPlayerFFCommandQueue::CMD_PAUSE: {
                    _state = STATE_PAUSED;
                    
                    // Seeking cases all of the packets to be flushed
                    _video_packet_queue.clear();
                    _audio_packet_queue.clear();
                    
                    _video_packet_queue.push_back_flush();
                    _audio_packet_queue.push_back_flush();

                    // Bump the playback thread so it'll process the data packet
                    _playback_thread_condition.notify_one();

                } break;

                case HWVideoPlayerFFCommandQueue::CMD_SEEK: {

                    // Seeking cases all of the packets to be flushed
                    _video_packet_queue.clear();
                    _audio_packet_queue.clear();
                    
                    _video_packet_queue.push_back_flush();
                    _audio_packet_queue.push_back_flush();
                    
                    // Seek the data source
                    int64_t tc_pos = param * AV_TIME_BASE;
                    
                    DTint err = ::av_seek_frame(    format_context, -1,
                                                    tc_pos,
                                                    (param < current_time() ?  AVSEEK_FLAG_BACKWARD : 0));    // Should flag be AVSEEK_FLAG_BACKWARD?
                    if (err < 0) {
                        LOG_MESSAGE << "Unable to seek";
                    }
                    
                    // Bump the playback thread so it'll process the data packet
                    _playback_thread_condition.notify_one();

                } break;

            }
            
            command_processed = true;
        }
    
        //
        // Read in more packets
        //
        
        if (_video_packet_queue.size() < MIN_NUM_PACKETS_TARGET && _audio_packet_queue.size() < MIN_NUM_PACKETS_TARGET) {
            
            DTint err = ::av_read_frame(format_context, &packet);
            if (err == 0) {
            
                // Insert into packet queue
                if (packet.stream_index == video_stream_index)
                    _video_packet_queue.push_back(&packet);
                else if (packet.stream_index == audio_stream_index)
                    _audio_packet_queue.push_back(&packet);
                
                // Bump the playback thread so it'll process the data packet
                _playback_thread_condition.notify_one();

                packet_processed = true;
            }
            
        }
        
        //
        // If there wasn't anything to process, suspend the thread
        //
        
        if (!command_processed && !packet_processed) {
            // If there's no more packets or commands, suspend the thread
            std::unique_lock<std::mutex> lock(_data_thread_mutex);
            _data_thread_condition.wait(lock);
        }
        
    }
    
    //::av_free_packet(&packet);
   
    _data_thread_running = false;

}

//==============================================================================
// This is the playback thread!!
//==============================================================================

void HWVideoPlayerFFInstance::playback_thread (void)
{

    //
    // Process playback queue
    //
    
    AVCodecContext *video_codec_context = _data_source->video_codec_context();
    AVCodecContext *audio_codec_context = _data_source->audio_codec_context();

    AVPacket packet;
    ::av_init_packet(&packet);
    
    
    // Flag for determining if the output texture contains valid frame data. The
    // loop tries to keep this true after seeking and loading
    DTboolean valid_video_frame = false;
    DTboolean valid_audio_frame = false;
    
    DTdouble video_timestamp = 0.0;
    DTdouble audio_timestamp = 0.0;
    
    DTboolean is_sound_playing = false;

    SoundPacket dst_sound_packet;
    dst_sound_packet.set_format(SoundResource::FORMAT_STEREO16);
    dst_sound_packet.set_frequency(AUDIO_FREQUENCY);
    
    DTsize dst_sound_packet_count = 0;
    DTsize dst_sound_byte_count = 0;
    
    // Loop until done
    while (_state == STATE_PAUSED || _state == STATE_PLAYING) {
        
        //
        // Read in more packets if playing or if we need a valid frame
        //
        
        // Check for flush coming down the pipe. Reset all timing info.
        if (_audio_packet_queue.peek_front(&packet) && _audio_packet_queue.is_flush(&packet)) {
            audio_timestamp = 0.0;
            video_timestamp = 0.0;
            _first_audio_timestamp_set = false;
            _first_audio_timestamp = 0.0;
            _current_time = 0.0;
            
            // Stop sound on flush
            System::audio_renderer()->stop(_sound_source);
            _sound_source->clear_packets();
            dst_sound_packet.set_num_bytes(0);

            is_sound_playing = false;
        }

        if (_state == STATE_PLAYING || !valid_video_frame) {
        
            //
            // Process Audio Frame
            //
            
            // Queue up audio to the end of the read packets if we are playing
            while ( audio_timestamp < (_first_audio_timestamp + _current_time + AUDIO_READ_AHEAD) &&
                    _audio_packet_queue.pop_front(&packet) ) {
                
                // Check for flush
                if (_audio_packet_queue.is_flush(&packet)) {
                
                    // Stop source and flush buffers
                    if (audio_codec_context)
                        ::avcodec_flush_buffers(audio_codec_context);
                    
                    valid_audio_frame = false;
                    
                    // Reset timing due to race condition with queue
                    audio_timestamp = 0.0;
                    video_timestamp = 0.0;
                    _first_audio_timestamp_set = false;
                    _first_audio_timestamp = 0.0;
                    _current_time = 0.0;

                    // Stop sound on flush
                    System::audio_renderer()->stop(_sound_source);
                    _sound_source->clear_packets();
                    dst_sound_packet.set_num_bytes(0);

                    is_sound_playing = false;

                } else {
                
                    ::avcodec_get_frame_defaults(_src_audio_frame);

                    // Decode audio frame
                    int got_frame = 0;
                    ::avcodec_decode_audio4(audio_codec_context, _src_audio_frame, &got_frame, &packet);

                    if (got_frame) {

                        // Get the best timestamp
                        int64_t presentation_time_stamp = packet.pts;
                        audio_timestamp = (DTdouble) (presentation_time_stamp - _audio_time_start) * _audio_time_base;

                        // Record the first audio timestamp because the sound source was reset
                        if (!_first_audio_timestamp_set) {
                            _first_audio_timestamp = audio_timestamp;
                            _first_audio_timestamp_set = true;
                        }
                        
                        DTsize old_num_samples = dst_sound_packet.num_samples();
                        
                        // Append new samples
                        dst_sound_packet.set_num_samples(old_num_samples + _src_audio_frame->nb_samples);
                        
                        const uint8_t **in_buf = (const uint8_t**) _src_audio_frame->extended_data;
                        uint8_t* out_buf[SWR_CH_MAX] = { (uint8_t*) dst_sound_packet.buffer() + old_num_samples*4, NULL};  // 4 bytes per sample

                        DTint num_samples = ::swr_convert(	_snd_convert_ctx,
                                                            out_buf,
                                                            _src_audio_frame->nb_samples,
                                                            in_buf,
                                                            _src_audio_frame->nb_samples);
                        
                        // Readjust num samples
                        dst_sound_packet.set_num_samples(old_num_samples + num_samples);
                        
                        // Queue up dound data
                        if (dst_sound_packet.num_samples() >= AUDIO_BUFFER_SIZE) {
                            // Sync timer here because adding audio packets seems to cause contention in OpenAL
                            _sound_source->push_packet(dst_sound_packet);
                            
                            dst_sound_byte_count += dst_sound_packet.num_bytes();
                            ++dst_sound_packet_count;
                            
//                            LOG_MESSAGE << "OpenAL Buffers Submitted: " << dst_sound_packet_count << " (ts=" << audio_timestamp << " bytes=" << dst_sound_byte_count << ")";

                            dst_sound_packet.set_num_bytes(0);
                            
                            // We now have a valid frame
                            valid_audio_frame = true;
                            
                        }
                        
                    }
                    
                    if(audio_codec_context->refcounted_frames == 1)
                        ::av_frame_unref(_src_audio_frame);

                    ::av_free_packet(&packet);

                    // Bump the data thread so it'll process the data packet
                    _data_thread_condition.notify_one();

                }
            }
            
            //
            // Calculate video timestamp based on audio position when playing. When seeking it
            // is set directly until audio packets are read.
            //
        
            if (audio_codec_context && _first_audio_timestamp_set) {
                _current_time = System::audio_renderer()->playback_time(_sound_source);
            }
        
            //
            // Process video frames
            //

            while ( video_timestamp < (_first_audio_timestamp + _current_time + VIDEO_READ_AHEAD) &&
                    _video_packet_queue.pop_front(&packet)) {
            
                // Check for flush
                if (_video_packet_queue.is_flush(&packet)) {
                
                    // Stop source and flush buffers
                    if (video_codec_context)
                        ::avcodec_flush_buffers(video_codec_context);

                    valid_video_frame = false;

                } else {

                    // Decode video frame
                    int got_frame = 0;
                    ::avcodec_decode_video2(video_codec_context, _src_frame, &got_frame, &packet);
                    
                    // Did we get a video frame?
                    if(got_frame) {
                    
                        // Get the best timestamp
                        int64_t presentation_time_stamp = ::av_frame_get_best_effort_timestamp(_src_frame);
                        video_timestamp = (DTdouble) (presentation_time_stamp - _video_time_start) * _video_time_base;
                        
//                        LOG_MESSAGE << "Audio Time: " << current_time() << "(" << audio_timestamp << ")"
//                                    << " Presentation Time: " << video_timestamp;

                        //
                        // Unlocked writes to back buffer.
                        //
                        
                        // Convert the image from its native format to RGBA
                        ::sws_scale(    _img_convert_ctx,
                                        _src_frame->data,
                                        _src_frame->linesize,
                                        0,
                                        _height,
                                        _dst_frame[1-_dst_frame_read_buffer_index]->data,
                                        _dst_frame[1-_dst_frame_read_buffer_index]->linesize);
                        
                        //
                        // Swap this to the front only if not currently reading elsewhere
                        //

                        _dst_frame_mutex.lock();

                        _dst_frame_buffer_dirty = true; 
                        _dst_frame_read_buffer_index = 1 - _dst_frame_read_buffer_index;  
                     
                        _dst_frame_mutex.unlock();
                        
                        // We now have a valid frame
                        valid_video_frame = true;
                    }
                
                    if(video_codec_context->refcounted_frames == 1)
                        ::av_frame_unref(_src_frame);
                    
                    ::av_free_packet(&packet);
                    
                    // Bump the data thread so it'll process the data packet
                    _data_thread_condition.notify_one();

                }
                
            }
            
            // If in preroll, then switch out if audio data is queued up
            if (_state == STATE_PLAYING && !is_sound_playing && valid_video_frame && valid_audio_frame) {
                System::audio_renderer()->play(_sound_source, NULL, NULL);
                is_sound_playing = true;
            }
        
            //
            // Figure out if we can sleep
            //

            DTdouble video_delay = video_timestamp - _current_time;
            if (video_delay > 0.0 && video_delay < 0.5) {
                std::this_thread::sleep_for(std::chrono::milliseconds( (DTint) (video_delay*1000) ));
            }

        } else {
        
            // Don't pause thread if closing
            if (_state != STATE_CLOSING) {
                // Pause the thread
                std::unique_lock<std::mutex> lock(_playback_thread_mutex);
                _playback_thread_condition.wait(lock);
            }
            
        }
        
    }
    
    _playback_thread_running = false;
}

//==============================================================================
//==============================================================================

void HWVideoPlayerFFInstance::play (void)
{
    if (_state != STATE_PAUSED && _state != STATE_PLAYING)
        return;

    _data_command_queue.push_play();

    _data_thread_condition.notify_one();        // Make sure thread is going
    _playback_thread_condition.notify_one();    // Make sure thread is going
}

void HWVideoPlayerFFInstance::pause (void)
{
    if (_state != STATE_PAUSED && _state != STATE_PLAYING)
        return;

    _data_command_queue.push_pause();

    _data_thread_condition.notify_one();        // Make sure thread is going
    _playback_thread_condition.notify_one();    // Make sure thread is going
}

void HWVideoPlayerFFInstance::seek (DTdouble t)
{
    if (_state != STATE_PAUSED && _state != STATE_PLAYING)
        return;

    _data_command_queue.push_seek(t);

    _data_thread_condition.notify_one();        // Make sure thread is going
    _playback_thread_condition.notify_one();    // Make sure thread is going
}

//==============================================================================
//==============================================================================

std::shared_ptr<TextureResource2D> HWVideoPlayerFFInstance::texture (void)
{
    // Upload frame data if we have a new frame
    _dst_frame_mutex.lock();

    if (_dst_frame_buffer_dirty) {
        System::renderer()->update_texture_2D (_tex_raw, 0, 0, _width, _height, (DTubyte*) _dst_frame_buffer[_dst_frame_read_buffer_index]);
        _dst_frame_buffer_dirty = false;
    }

    _dst_frame_mutex.unlock();
    
    return _tex_resource;
}

//==============================================================================
//==============================================================================

Color4f HWVideoPlayerFFInstance::sample_pixel (DTint x, DTint y)
{
    DTubyte *base_address = (DTubyte*) _dst_frame_buffer[_dst_frame_read_buffer_index];
    base_address += (y * _width + x) * 4;  // Skip to pixel

    return Color4f(base_address[0], base_address[1], base_address[2], 0);
}

//==============================================================================
//==============================================================================

} // DT3

