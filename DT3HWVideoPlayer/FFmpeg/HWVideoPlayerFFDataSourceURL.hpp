#ifndef DT3_HWVIDEOPLAYERFFDATASOURCEURL
#define DT3_HWVIDEOPLAYERFFDATASOURCEURL
//==============================================================================
///	
///	File: HWVideoPlayerFFDataSourceURL.hpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3HWVideoPlayer/FFmpeg/HWVideoPlayerFFDataSourceBase.hpp"

#include "DT3Core/Types/Network/URL.hpp"

//==============================================================================
/// Namespace
//==============================================================================

namespace DT3 {

//==============================================================================
/// Class
//==============================================================================

class HWVideoPlayerFFDataSourceURL: public HWVideoPlayerFFDataSourceBase {
    public:
        DEFINE_CREATE

                                        HWVideoPlayerFFDataSourceURL    (void);
    private:
                                        HWVideoPlayerFFDataSourceURL    (const HWVideoPlayerFFDataSourceURL &rhs);
        HWVideoPlayerFFDataSourceURL&   operator =                      (const HWVideoPlayerFFDataSourceURL &rhs);
    public:
        virtual                         ~HWVideoPlayerFFDataSourceURL	(void);
    
	public:
    
		/// Open a video data source
        /// \return Error code
        virtual DTerr                   open                (const URL &url);
    
		/// Closes a video source
        virtual void                    close               (void);

        /// Returns Format Context
        virtual AVFormatContext*        format_context      (void)  {   return NULL;    }

        /// Index of video stream
        virtual int                     video_stream_index  (void)  {   return 0;       }

        /// Index of audio stream
        virtual int                     audio_stream_index  (void)  {   return 0;       }
    
        /// Returns Codec Context
        virtual AVCodecContext*         video_codec_context (void)  {   return NULL;    }

        /// Returns Codec Context
        virtual AVCodecContext*         audio_codec_context (void)  {   return NULL;    }
    
        /// Returns AVStream
        virtual AVStream*               video_stream        (void)  {   return NULL;    }

        /// Returns AVStream
        virtual AVStream*               audio_stream        (void)  {   return NULL;    }
    
    private:
        URL                             _url;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
