#ifndef DT3_HWVIDEOPLAYERFF
#define DT3_HWVIDEOPLAYERFF
//==============================================================================
///	
///	File: HWVideoPlayerFF.hpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3Core/Types/Base/BaseInclude.hpp"

#include "DT3Core/Types/FileBuffer/FilePath.hpp"
#include "DT3Core/Types/Network/URL.hpp"
#include "DT3Core/Types/Utility/Callback.hpp"
#include "DT3Core/Types/Math/Rectangle.hpp"
#include "DT3Core/Resources/ResourceTypes/TextureResource2D.hpp"

#include "DT3HWVideoPlayer/FFmpeg/HWVideoPlayerFFInstance.hpp"

extern "C" {
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
    #include "libswscale/swscale.h"
}

//==============================================================================
/// Namespace
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class TextureResource2D;

//==============================================================================
/// Class
//==============================================================================

class HWVideoPlayerFF {
    private:
                                        HWVideoPlayerFF     (void);
                                        HWVideoPlayerFF     (const HWVideoPlayerFF &rhs);
        HWVideoPlayerFF&                operator =          (const HWVideoPlayerFF &rhs);
        virtual                         ~HWVideoPlayerFF	(void);
    
	public:
    
        typedef std::shared_ptr<HWVideoPlayerFFInstance>    HWVideoPlayerType;
    
		/// Initialize the FFMpeg Subsystem
        static void                         initialize          (void);

		/// Destroy the FFMpeg Subsystem
        static void                         destroy             (void);

		/// Open a video file
		/// \param path path to video file
        /// \return video handle
        static HWVideoPlayerType            open                (const FilePath &path);

		/// Open a video URL
		/// \param purl url of video file
        /// \return video handle
        static HWVideoPlayerType            open                (const URL &url);

		/// Close the currently opened video
        /// \param hwvp video handle
        static void                         close               (HWVideoPlayerType hwvp);


        /// Checks if streaming video is likely to finish loading in time to play unterrupted
        /// \param hwvp video handle
        /// \return Is playback likely to succeed skip free
        static DTboolean                    is_playback_likely_to_keep_up   (HWVideoPlayerType hwvp);

		/// Play the currently opened video
        /// \param hwvp video handle
		/// \param sender pointer to node that fired the event
        static void                         play                (HWVideoPlayerType hwvp);

		/// Pause the currently opened video
        /// \param hwvp video handle
		/// \param sender pointer to node that fired the event
        static void                         pause               (HWVideoPlayerType hwvp);

		/// Rewinds the video to the beginning
        /// \param hwvp video handle
		/// \param sender pointer to node that fired the event
        static void                         rewind              (HWVideoPlayerType hwvp);

		/// Returns the length of the video
        /// \param hwvp video handle
        /// \return length (in seconds) of the video
        static DTfloat                      length              (HWVideoPlayerType hwvp);

		/// Returns the length of the video
        /// \param hwvp video handle
        /// \return length (in seconds) of the video
        static DTfloat                      current_time        (HWVideoPlayerType hwvp);

		/// Seeks to a position in the video
        /// \param hwvp video handle
		/// \param time time to seek to
        static void                         seek                (HWVideoPlayerType hwvp, DTfloat time);
    
        enum State {
            STATE_IDLE,
            STATE_PAUSED,   // Loaded and waiting
            STATE_PLAYING,  // Currently playing
            STATE_CLOSING,
            STATE_ERROR
        };
    
		/// Returns the state of playback of the video
        /// \param hwvp video handle
        /// \return lstate of the video
        static State                        state               (HWVideoPlayerType hwvp);

		/// Returns the size of the video
        /// \param hwvp video handle
		/// \param width width of video
		/// \param height height of video
        static void                         size                (HWVideoPlayerType hwvp, DTuint &width, DTuint &height);
    
		/// Returns the current frame for the video
        /// \param hwvp video handle
        /// \return current frame of the video
        static std::shared_ptr<TextureResource2D> frame         (HWVideoPlayerType hwvp);
    
		/// Returns a pixel from the current frame
        /// \param x x location
        /// \param y y location
        /// \return current pixel from the video
        static Color4f                      sample_pixel        (HWVideoPlayerType hwvp, DTint x, DTint y);
    
    private:
        static int                          lock_manager        (void **mutex, enum AVLockOp op);
    
};

//==============================================================================
//==============================================================================

} // DT3

#endif
