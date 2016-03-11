#ifndef DT3_HWVIDEOPLAYERFFPACKETQUEUE
#define DT3_HWVIDEOPLAYERFFPACKETQUEUE
//==============================================================================
///	
///	URL: HWVideoPlayerFFPacketQueue.hpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "BaseInclude.hpp"
#include <mutex>

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
/// Class
//==============================================================================

class HWVideoPlayerFFPacketQueue {
    public:

                                        HWVideoPlayerFFPacketQueue      (void);
    private:
                                        HWVideoPlayerFFPacketQueue      (const HWVideoPlayerFFPacketQueue &rhs);
        HWVideoPlayerFFPacketQueue&     operator =                      (const HWVideoPlayerFFPacketQueue &rhs);
    public:
                                        ~HWVideoPlayerFFPacketQueue     (void);
    
	public:
    
		/// Pushes a packet onto the back of the queue
        DTerr                           push_back       (AVPacket *pkt);

		/// Pops a packet from the front of the queue
        DTboolean                       pop_front       (AVPacket *pkt);
    
		/// Pops a packet from the front of the queue
        DTboolean                       peek_front      (AVPacket *pkt);
    
    
        /// Pushes a "flush" packet
        DTerr                           push_back_flush (void);
    
        /// Checks if a packet is a "flush" packet
        DTboolean                       is_flush        (AVPacket *pkt);


        /// Pushes a "play" packet
        DTerr                           push_back_play  (void);
    
        /// Checks if a packet is a "flush" packet
        DTboolean                       is_play         (AVPacket *pkt);


        /// Pushes a "pause" packet
        DTerr                           push_back_pause (void);
    
        /// Checks if a packet is a "flush" packet
        DTboolean                       is_pause        (AVPacket *pkt);


		/// Clears the packet queue
        void                            clear           (void);

		/// Returns the size of the queue
        DTsize                          size            (void) const    {   return _size;   }
    
    private:
        AVPacketList    *_first_pkt;
        AVPacketList    *_last_pkt;
        DTsize          _size;
    
        AVPacket        _flush_pkt;
        AVPacket        _play_pkt;
        AVPacket        _pause_pkt;

        std::mutex      _lock;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
