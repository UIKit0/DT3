#ifndef DT3_SOUNDSOURCEQUEUE
#define DT3_SOUNDSOURCEQUEUE
//==============================================================================
///	
///	File: SoundSourceQueue.hpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3Core/Types/Sound/SoundSource.hpp"
#include <list>
#include <mutex>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class SoundPacket;

//==============================================================================
/// Class
//==============================================================================

class SoundSourceQueue: public SoundSource {
    public:
        DEFINE_TYPE(SoundSourceQueue,SoundSource)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                    SoundSourceQueue    (void);
                                    SoundSourceQueue    (const SoundSourceQueue &rhs);
        SoundSourceQueue &          operator =          (const SoundSourceQueue &rhs);
        virtual                     ~SoundSourceQueue   (void);
                
	public:
    
        /// Push a packet into the queue.
		/// \param packet Packet to push into the queue
        void                        push_packet         (SoundPacket& packet);

        /// Clears the packets from the queue.
        void                        clear_packets       (void);

        /// Returns the number of packets in the queue.
        DTsize                      num_packets         (void)  {   return _packet_count;   }

		/// Returns the next sound packet for playing from this source.
        virtual const SoundPacket&  next_sound_packet   (void);
        
	private:
        std::mutex                  _lock;
        std::list<SoundPacket>      _packets;
        DTsize                      _packet_count;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
