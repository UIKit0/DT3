#ifndef DT3_HWVIDEOPLAYERFFDATASOURCEBASE
#define DT3_HWVIDEOPLAYERFFDATASOURCEBASE
//==============================================================================
///	
///	File: HWVideoPlayerFFDataSourceBase.hpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3Core/Types/Base/BaseClass.hpp"

extern "C" {
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
    #include "libswscale/swscale.h"
    #include "libswresample/swresample.h"
}

//==============================================================================
/// Namespace
//==============================================================================

namespace DT3 {

//==============================================================================
/// Class
//==============================================================================

class HWVideoPlayerFFDataSourceBase: public BaseClass {
    public:
    
                                        HWVideoPlayerFFDataSourceBase   (void);
    private:
                                        HWVideoPlayerFFDataSourceBase   (const HWVideoPlayerFFDataSourceBase &rhs);
        HWVideoPlayerFFDataSourceBase&  operator =                      (const HWVideoPlayerFFDataSourceBase &rhs);
    public:
        virtual                         ~HWVideoPlayerFFDataSourceBase	(void);
    
	public:
        
		/// Closes a video source
        virtual void                close               (void) {};
    
        /// Returns size of file
        virtual DTsize              size                (void) {    return 0;   }

        /// Returns Format Context
        virtual AVFormatContext*    format_context      (void) = 0;

        /// Index of video stream
        virtual int                 video_stream_index  (void) = 0;

        /// Index of audio stream
        virtual int                 audio_stream_index  (void) = 0;
    
        /// Returns Codec Context
        virtual AVCodecContext*     video_codec_context (void) = 0;

        /// Returns Codec Context
        virtual AVCodecContext*     audio_codec_context (void) = 0;
    
        /// Returns AVStream
        virtual AVStream*           video_stream        (void) = 0;

        /// Returns AVStream
        virtual AVStream*           audio_stream        (void) = 0;

};

//==============================================================================
//==============================================================================

} // DT3

#endif
