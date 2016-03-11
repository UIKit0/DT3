#ifndef DT3_HWVIDEOPLAYERFFDATASOURCEFILE
#define DT3_HWVIDEOPLAYERFFDATASOURCEFILE
//==============================================================================
///	
///	File: HWVideoPlayerFFDataSourceFile.hpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3HWVideoPlayer/FFmpeg/HWVideoPlayerFFDataSourceBase.hpp"

#include "DT3Core/Types/FileBuffer/FilePath.hpp"
#include "DT3Core/Types/FileBuffer/BinaryFileStream.hpp"

//==============================================================================
/// Namespace
//==============================================================================

namespace DT3 {

//==============================================================================
/// Class
//==============================================================================

class HWVideoPlayerFFDataSourceFile: public HWVideoPlayerFFDataSourceBase {
    public:
        DEFINE_CREATE

                                        HWVideoPlayerFFDataSourceFile   (void);
    private:
                                        HWVideoPlayerFFDataSourceFile   (const HWVideoPlayerFFDataSourceFile &rhs);
        HWVideoPlayerFFDataSourceFile&  operator =                      (const HWVideoPlayerFFDataSourceFile &rhs);
    public:
        virtual                         ~HWVideoPlayerFFDataSourceFile	(void);
    
	public:
    
		/// Open a video data source
        /// \return Error code
        virtual DTerr                   open                (const FilePath &path);
    
		/// Closes a video source
        virtual void                    close               (void);
    
        /// Returns size of file
        virtual DTsize                  size                (void);
    
        /// Returns Format Context
        virtual AVFormatContext*        format_context      (void)  {   return _format_context;  }

        /// Index of video stream
        virtual int                     video_stream_index  (void)  {   return _video_stream_index;  }

        /// Index of audio stream
        virtual int                     audio_stream_index  (void)  {   return _audio_stream_index;  }
    
        /// Returns Codec Context
        virtual AVCodecContext*         video_codec_context (void)  {   return _video_codec_context;  }

        /// Returns Codec Context
        virtual AVCodecContext*         audio_codec_context (void)  {   return _audio_codec_context;  }
    
        /// Returns AVStream
        virtual AVStream*               video_stream        (void)  {   return _video_stream_index >= 0 ? _format_context->streams[_video_stream_index] : NULL; }

        /// Returns AVStream
        virtual AVStream*               audio_stream        (void)  {   return _audio_stream_index >= 0 ? _format_context->streams[_audio_stream_index] : NULL; }

    private:
        // This function must read “buf_size” number of bytes from your
        // file handle (which is the “opaque” parameter) and store the data
        // into “buf”. The return value is the number of bytes actually read /
        // from your file handle. If the function fails you must return <0.
        static int                      read_func   (void *opaque, uint8_t *buf, int buf_size);
    
        // This function is like the fseek() C stdio function. “whence” can
        // be either one of the standard C values (SEEK_SET, SEEK_CUR, SEEK_END)
        // or one more value: AVSEEK_SIZE.
        static int64_t                  seek_func   (void *opaque, int64_t offset, int whence);


        FilePath                _path;
        BinaryFileStream        _file;
    
        DTubyte                 *_buffer;
    
        AVIOContext             *_av_io_context;
        AVFormatContext         *_format_context;

        int                     _video_stream_index;
        int                     _audio_stream_index;
    
        AVCodecContext          *_video_codec_context;
        AVCodecContext          *_audio_codec_context;

};

//==============================================================================
//==============================================================================

} // DT3

#endif
