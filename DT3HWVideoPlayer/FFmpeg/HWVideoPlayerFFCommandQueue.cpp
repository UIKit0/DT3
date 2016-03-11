//==============================================================================
///	
///	File: HWVideoPlayerFFCommandQueue.cpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3HWVideoPlayer/FFmpeg/HWVideoPlayerFFCommandQueue.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

HWVideoPlayerFFCommandQueue::HWVideoPlayerFFCommandQueue (void)
{
    
}

HWVideoPlayerFFCommandQueue::~HWVideoPlayerFFCommandQueue (void)
{

}

//==============================================================================
//==============================================================================

void HWVideoPlayerFFCommandQueue::push_play (void)
{
    CommandEntry ce;
    ce._command = CMD_PLAY;
    ce._parameter = 0.0;
    
    _lock.lock();
    _commands.push_back(ce);
    _lock.unlock();
}

void HWVideoPlayerFFCommandQueue::push_pause (void)
{
    CommandEntry ce;
    ce._command = CMD_PAUSE;
    ce._parameter = 0.0;
    
    _lock.lock();
    _commands.push_back(ce);
    _lock.unlock();
}

void HWVideoPlayerFFCommandQueue::push_seek (DTdouble time)
{
    CommandEntry ce;
    ce._command = CMD_SEEK;
    ce._parameter = time;
    
    _lock.lock();
    
    // Remove any other pending seeks
    std::list<CommandEntry>::iterator i;
    
    for (i = _commands.begin(); i != _commands.end(); ) {
    
        if (i->_command == CMD_SEEK) {
            i = _commands.erase(i);
        } else {
            ++i;
        }
    
    }
    
    // Push new seek command
    _commands.push_back(ce);
    
    _lock.unlock();
}

DTboolean HWVideoPlayerFFCommandQueue::pop_command (Command &command, DTdouble &param)
{
    _lock.lock();

    if (_commands.size() > 0) {
        CommandEntry ce = _commands.front();
        _commands.pop_front();
    
        command = ce._command;
        param = ce._parameter;
        
        _lock.unlock();
        return true;
    } else {
        _lock.unlock();
        return false;
    }

}

//==============================================================================
//==============================================================================

} // DT3

