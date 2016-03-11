//==============================================================================
///	
///	File: HWVideoPlayerFFDataSourceFile.cpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3HWVideoPlayer/FFmpeg/HWVideoPlayerFFDataSourceFile.hpp"

#include "FileManager.hpp"
#include "MoreMath.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

HWVideoPlayerFFDataSourceFile::HWVideoPlayerFFDataSourceFile (void)
    :   //_buffer                 (NULL),
        //_av_io_context          (NULL),
        _format_context         (NULL),
        _video_stream_index     (-1),
        _audio_stream_index     (-1),
        _video_codec_context    (NULL),
        _audio_codec_context    (NULL)
{

}

HWVideoPlayerFFDataSourceFile::~HWVideoPlayerFFDataSourceFile (void)
{
    close();
}

//==============================================================================
//==============================================================================

//int HWVideoPlayerFFDataSourceFile::read_func(void *opaque, uint8_t *buf, int buf_size)
//{
//    BinaryFileStream *file = (BinaryFileStream*) opaque;
//    
//    DTsize nbytes = file->read_raw((DTubyte*) buf, buf_size);
//    if (file->is_eof())  return 0;
//    
//    return (int) nbytes;
//}
//
//int64_t HWVideoPlayerFFDataSourceFile::seek_func(void *opaque, int64_t offset, int whence)
//{
//    BinaryFileStream *file = (BinaryFileStream*) opaque;
//
//    switch (whence) {
//        case SEEK_SET:  {
//            file->seek_g(offset, Stream::FROM_BEGINNING);
//            DTsize g = file->g();
//            return g;
//        }
//        case SEEK_CUR:  {
//            file->seek_g(offset, Stream::FROM_CURRENT);
//            DTsize g = file->g();
//            return g;
//        }
//        case SEEK_END:  {
//            file->seek_g(offset, Stream::FROM_END);
//            DTsize g = file->g();
//            return g;
//        }
//        case AVSEEK_SIZE: {
//            return file->length();
//        }
//    }
//    
//    return -1;
//}

//==============================================================================
//==============================================================================

DTerr HWVideoPlayerFFDataSourceFile::open   (const FilePath &path)
{
    _path = path;
    
    //
	// Open the file
    //
    
	DTerr err;
	if ((err = FileManager::open(_file, _path, true)) != DT3_ERR_NONE) {
        close();
        return DT3_ERR_FILE_OPEN_FAILED;
    }
    
    // Open the input
    _format_context = NULL;
    err = ::avformat_open_input(&_format_context, _path.full_path().c_str(), NULL, NULL);
    if (err < 0) {
        close();
        return DT3_ERR_FILE_OPEN_FAILED;
    }
    
    // Ok we should now be able to read from our archive
    
    // Retrieve stream information
    if(::avformat_find_stream_info(_format_context, NULL) < 0) {
        close();
        return DT3_ERR_FILE_OPEN_FAILED;
    }
    
    // Display information
    ::av_dump_format(_format_context,0,"",false);

    // Stream indices
    _video_stream_index = -1;
    _audio_stream_index = -1;

    // Get the streams
    _video_codec_context = NULL;
    _audio_codec_context = NULL;

    for(DTuint i = 0; i < _format_context->nb_streams; ++i) {
    
        if(_format_context->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO && _video_stream_index < 0) {
            _video_codec_context = _format_context->streams[i]->codec;
            _video_stream_index = i;
        }

        if(_format_context->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO && _audio_stream_index < 0) {
            _audio_codec_context = _format_context->streams[i]->codec;
            _audio_stream_index = i;
        }
        
    }
    
    // Validate. If no video then we assume a problem.
    if (!_video_codec_context) {
        close();
        return DT3_ERR_FILE_OPEN_FAILED;
    }
    
    // Get the codecs
    // Find the decoder for the video stream
    
    if (_video_codec_context) {
        AVCodec *video_codec = ::avcodec_find_decoder(_video_codec_context->codec_id);
        if(video_codec) {
        
            if (::avcodec_open2(_video_codec_context, video_codec, NULL) < 0) {
                _video_codec_context = NULL;
                close();
                return DT3_ERR_FILE_OPEN_FAILED;
            }
            
        } else {
            _video_codec_context = NULL;
            close();
            return DT3_ERR_FILE_OPEN_FAILED;
        }
    }

    if (_audio_codec_context) {
        AVCodec *audio_codec = ::avcodec_find_decoder(_audio_codec_context->codec_id);
        if(audio_codec) {
        
            if (::avcodec_open2(_audio_codec_context, audio_codec, NULL) < 0) {
                _audio_codec_context = NULL;
                close();
                return DT3_ERR_FILE_OPEN_FAILED;
            }

        } else {
            _audio_codec_context = NULL;
            close();
            return DT3_ERR_FILE_OPEN_FAILED;
        }
    }
    
//    _video_codec_context->thread_count = 2;
//    _audio_codec_context->thread_count = 2;
    
    return DT3_ERR_NONE;
}
    
void HWVideoPlayerFFDataSourceFile::close   (void)
{
    if (_video_codec_context)   {   ::avcodec_close(_video_codec_context);      _video_codec_context = NULL;    }
    if (_audio_codec_context)   {   ::avcodec_close(_audio_codec_context);      _audio_codec_context = NULL;    }
    
    if (_format_context)        {   ::avformat_free_context(_format_context);   _format_context = NULL;         }
}

DTsize HWVideoPlayerFFDataSourceFile::size (void)
{
    return _path.length();
}

//==============================================================================
//==============================================================================

} // DT3

