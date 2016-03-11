#ifndef DT3_HWVIDEOPLAYERFFINSTANCE
#define DT3_HWVIDEOPLAYERFFINSTANCE
//==============================================================================
///	
///	URL: HWVideoPlayerFFInstance.hpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3HWVideoPlayer/FFmpeg/HWVideoPlayerFFDataSourceBase.hpp"
#include "DT3HWVideoPlayer/FFmpeg/HWVideoPlayerFFPacketQueue.hpp"
#include "DT3HWVideoPlayer/FFmpeg/HWVideoPlayerFFCommandQueue.hpp"

#include "DT3Core/Types/Network/URL.hpp"
#include "DT3Core/Types/Sound/SoundSourceQueue.hpp"
#include "DT3Core/Resources/ResourceTypes/TextureResource2D.hpp"

#include <thread>
#include <mutex>
#include <condition_variable>

//==============================================================================
/// Namespace
//==============================================================================

namespace DT3 {

//==============================================================================
/// Class
//==============================================================================

class HWVideoPlayerFFInstance: public BaseClass {
    public:
        DEFINE_CREATE

                                        HWVideoPlayerFFInstance     (void);
    private:
                                        HWVideoPlayerFFInstance     (const HWVideoPlayerFFInstance &rhs);
        HWVideoPlayerFFInstance&        operator =                  (const HWVideoPlayerFFInstance &rhs);
    public:
        virtual                         ~HWVideoPlayerFFInstance	(void);
    
	public:
    
        /// Open a video file
		/// \param path path to video file
        /// \return Error
        DTerr                           open                (const FilePath &path);

		/// Open a video URL
		/// \param purl url of video file
        /// \return Error
        DTerr                           open                (const URL &url);

		/// Close the instance
        void                            close               (void);


        //
        // Playback controls
        //

        /// Start the movie playing
        void                            play                (void);
    
        /// Pause the movie
        void                            pause               (void);
    
        /// Seek the movie
        void                            seek                (DTdouble t);
        void                            seek_percent        (DTdouble p);


        //
        // Info about movie
        //

        /// Returns the width of the video
        /// \return width
        DTint                           width               (void) const    {   return _width;  }
    
        /// Returns the height of the video
        /// \return height
        DTint                           height              (void) const    {   return _height; }
    
        /// Returns the texture that is being rendered
        std::shared_ptr<TextureResource2D>  texture         (void);
    
		/// Returns a pixel from the current frame
        /// \param x x location
        /// \param y y location
        /// \return current pixel from the video
        Color4f                         sample_pixel        (DTint x, DTint y);

        /// Returns the Duration of the video
        DTdouble                        length              (void) const    {   return _length;  }

        /// Returns the current playback time of the video
        DTdouble                        current_time        (void) const    {   return _first_audio_timestamp + _current_time;  }
    
        enum State {
            STATE_IDLE,
            STATE_PAUSED,   // Loaded and waiting
            STATE_PLAYING,  // Currently playing
            STATE_CLOSING,
            STATE_ERROR
        };
    
        State                           state               (void) const    {   return _state;  }

    private:
    
        DTerr                           open_common         (std::shared_ptr<HWVideoPlayerFFDataSourceBase> data_source);
        void                            close_common        (void);

        void                            playback_thread     (void);
        void                            data_thread         (void);

    
        // Video meta data
        DTdouble                            _length;
    
        DTdouble                            _video_time_base;
        int64_t                             _video_time_start;

        DTdouble                            _audio_time_base;
        int64_t                             _audio_time_start;
    
        DTdouble                            _current_time;
    
        DTboolean                           _first_audio_timestamp_set;
        DTdouble                            _first_audio_timestamp;

        DTuint                              _width;
        DTuint                              _height;
    
        // Instance info
        std::shared_ptr<HWVideoPlayerFFDataSourceBase>  _data_source;
    
        AVFrame                             *_src_frame;

        // Two buffers for double buffering
        AVFrame                             *_dst_frame[2];
        void                                *_dst_frame_buffer[2];

        // Syncing double buffering
        DTint                               _dst_frame_read_buffer_index;
        DTboolean                           _dst_frame_buffer_dirty;
        std::mutex                          _dst_frame_mutex;

        AVFrame                             *_src_audio_frame;
            
        SwsContext                          *_img_convert_ctx;
        SwrContext                          *_snd_convert_ctx;

        State                               _state;

        // Thread references
        std::thread                         _playback_thread;
        std::mutex                          _playback_thread_mutex;
        std::condition_variable             _playback_thread_condition;
        DTboolean                           _playback_thread_running;
    
        std::thread                         _data_thread;
        std::mutex                          _data_thread_mutex;
        std::condition_variable             _data_thread_condition;
        DTboolean                           _data_thread_running;

        // Packet queue
        HWVideoPlayerFFPacketQueue          _video_packet_queue;
        HWVideoPlayerFFPacketQueue          _audio_packet_queue;
    
        // Command queue
        HWVideoPlayerFFCommandQueue         _data_command_queue;
        //HWVideoPlayerFFCommandQueue         _playback_command_queue;    // This is only filled out after data thread
                                                                        // processes its command queue
    
        // Output texture

        std::shared_ptr<DT3GLTexture2DResource> _tex_raw;
        std::shared_ptr<TextureResource2D>      _tex_resource;
    
        // Audio Packets
        std::shared_ptr<SoundSourceQueue>   _sound_source;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
