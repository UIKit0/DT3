//==============================================================================
///	
///	File: HWVideoPlayerFFPacketQueue.cpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3HWVideoPlayer/FFmpeg/HWVideoPlayerFFPacketQueue.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
//==============================================================================

const DTubyte FLUSH[] = "flush";
const DTubyte PLAY[] = "play";
const DTubyte PAUSE[] = "pause";

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

HWVideoPlayerFFPacketQueue::HWVideoPlayerFFPacketQueue (void)
    :   _first_pkt  (NULL),
        _last_pkt   (NULL),
        _size       (0)
{
    ::av_init_packet(&_flush_pkt);
    _flush_pkt.data = (uint8_t*) FLUSH;

    ::av_init_packet(&_play_pkt);
    _play_pkt.data = (uint8_t*) PLAY;

    ::av_init_packet(&_pause_pkt);
    _pause_pkt.data = (uint8_t*) PAUSE;
}

HWVideoPlayerFFPacketQueue::~HWVideoPlayerFFPacketQueue (void)
{
    clear();
}

//==============================================================================
//==============================================================================

DTerr HWVideoPlayerFFPacketQueue::push_back (AVPacket *pkt)
{
    // Duplicate if not a flush packet
    if (!is_flush(pkt) && !is_play(pkt) && !is_pause(pkt)) {
        if(av_dup_packet(pkt) < 0)
            return DT3_ERR_FILE_OPEN_FAILED;
    }
    
    AVPacketList *packet_list = (AVPacketList *) ::av_malloc(sizeof(AVPacketList));
    
    packet_list->pkt = *pkt;
    packet_list->next = NULL;
    
    _lock.lock();
    
    // Queue is empty
    if (!_first_pkt) {
        _first_pkt = _last_pkt = packet_list;
    } else {
        _last_pkt->next = packet_list;
        _last_pkt = packet_list;
    }
    
    ++_size;
    
    _lock.unlock();
    
    return 0;
}

DTboolean HWVideoPlayerFFPacketQueue::pop_front (AVPacket *pkt)
{
    _lock.lock();

    if (_first_pkt) {
        AVPacketList *first_pkt = _first_pkt;
        
        *pkt = _first_pkt->pkt;
        _first_pkt = _first_pkt->next;
        
        if (!_first_pkt)
            _last_pkt = NULL;
        
        ::av_free(first_pkt);
    
        --_size;

        _lock.unlock();
        return true;
    } else {

        _lock.unlock();
        return false;
    }
}

DTboolean HWVideoPlayerFFPacketQueue::peek_front (AVPacket *pkt)
{
    _lock.lock();

    if (_first_pkt) {
        *pkt = _first_pkt->pkt;

        _lock.unlock();
        return true;
    } else {

        _lock.unlock();
        return false;
    }
}

void HWVideoPlayerFFPacketQueue::clear (void)
{
    _lock.lock();

    while (_first_pkt) {
        AVPacketList *first_pkt = _first_pkt;

        _first_pkt = _first_pkt->next;
        
        ::av_free_packet(&first_pkt->pkt);
        ::av_free(first_pkt);
    }
    
    _first_pkt = NULL;
    _last_pkt = NULL;
    _size = 0;
    
    _lock.unlock();
}

//==============================================================================
//==============================================================================

DTerr HWVideoPlayerFFPacketQueue::push_back_flush (void)
{
    return push_back(&_flush_pkt);
}

DTboolean HWVideoPlayerFFPacketQueue::is_flush (AVPacket *pkt)
{
    return (pkt->data == (uint8_t*) FLUSH);
}


DTerr HWVideoPlayerFFPacketQueue::push_back_play (void)
{
    return push_back(&_play_pkt);
}

DTboolean HWVideoPlayerFFPacketQueue::is_play (AVPacket *pkt)
{
    return (pkt->data == (uint8_t*) PLAY);
}


DTerr HWVideoPlayerFFPacketQueue::push_back_pause (void)
{
    return push_back(&_pause_pkt);
}

DTboolean HWVideoPlayerFFPacketQueue::is_pause (AVPacket *pkt)
{
    return (pkt->data == (uint8_t*) PAUSE);
}


//==============================================================================
//==============================================================================

} // DT3

