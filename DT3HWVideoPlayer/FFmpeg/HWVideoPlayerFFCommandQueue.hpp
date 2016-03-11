#ifndef DT3_HWVIDEOPLAYERFFCOMMANDQUEUE
#define DT3_HWVIDEOPLAYERFFCOMMANDQUEUE
//==============================================================================
///	
///	URL: HWVideoPlayerFFCommandQueue.hpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3Core/Types/Base/BaseInclude.hpp"
#include <list>
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

class HWVideoPlayerFFCommandQueue {
    public:

                                        HWVideoPlayerFFCommandQueue     (void);
    private:
                                        HWVideoPlayerFFCommandQueue     (const HWVideoPlayerFFCommandQueue &rhs);
        HWVideoPlayerFFCommandQueue&    operator =                      (const HWVideoPlayerFFCommandQueue &rhs);
    public:
                                        ~HWVideoPlayerFFCommandQueue    (void);
    
	public:
    
        enum Command {
            CMD_PLAY,
            CMD_PAUSE,
            CMD_SEEK
        };
    
        /// Pushes the play command
        void            push_play           (void);
    
        /// Pushes the play command
        void            push_pause          (void);

        /// Pushes the seek command
        /// \param time Time to seek to
        void            push_seek           (DTdouble time);
    
    
        /// Gets the next command in the queue
        DTboolean       pop_command         (Command &command, DTdouble &param);
    
    private:

        struct CommandEntry {
            Command             _command;
            DTdouble            _parameter;
        };

        std::list<CommandEntry> _commands;
        std::mutex              _lock;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
