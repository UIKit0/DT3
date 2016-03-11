//==============================================================================
///	
///	File: HWVideoPlayerFF.cpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3HWVideoPlayer/FFmpeg/HWVideoPlayerFF.hpp"

#include "DT3Core/System/StaticInitializer.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
//==============================================================================

GLOBAL_STATIC_INITIALIZATION(0,HWVideoPlayerFF::initialize())
GLOBAL_STATIC_DESTRUCTION(0,HWVideoPlayerFF::destroy())

//==============================================================================
//==============================================================================

int HWVideoPlayerFF::lock_manager(void **mutex, enum AVLockOp op)
{
    if (mutex == NULL)
        return -1;

    switch(op) {
        case AV_LOCK_CREATE:
        {
            *mutex = static_cast<void*>(new std::mutex());
            break;
        }
        case AV_LOCK_OBTAIN:
        {
            std::mutex *m =  static_cast<std::mutex*>(*mutex);
            m->lock();
            break;
        }
        case AV_LOCK_RELEASE:
        {
            std::mutex *m =  static_cast<std::mutex*>(*mutex);
            m->unlock();
            break;
        }
        case AV_LOCK_DESTROY:
        {
            std::mutex *m =  static_cast<std::mutex*>(*mutex);
            delete m;
            break;
        }
        default:
        break;
    }
    return 0;
}

void HWVideoPlayerFF::initialize (void)
{
#ifndef DT3_EDITOR
    ::av_register_all();
    ::av_lockmgr_register(&HWVideoPlayerFF::lock_manager);
    //::av_log_set_level (AV_LOG_DEBUG);
#endif
}

void HWVideoPlayerFF::destroy (void)
{

}

//==============================================================================
//==============================================================================

HWVideoPlayerFF::HWVideoPlayerType HWVideoPlayerFF::open (const FilePath &path)
{
#ifndef DT3_EDITOR
    auto hwvpi = std::make_shared<HWVideoPlayerFFInstance>();
    DTerr err = hwvpi->open(path);
    if (err != DT3_ERR_NONE) {
        return NULL;
    }
    
    return hwvpi;
#else
    return NULL;
#endif
}

HWVideoPlayerFF::HWVideoPlayerType HWVideoPlayerFF::open (const URL &url)
{
#ifndef DT3_EDITOR
    auto hwvpi = std::make_shared<HWVideoPlayerFFInstance>();
    DTerr err = hwvpi->open(url);
    if (err != DT3_ERR_NONE) {
        return NULL;
    }

    return hwvpi;
#else
    return NULL;
#endif
}

void HWVideoPlayerFF::close (HWVideoPlayerFF::HWVideoPlayerType hwvp)
{
#ifndef DT3_EDITOR
    if (!hwvp)
        return;
    
    hwvp->close();
#endif
}

//==============================================================================
//==============================================================================

DTboolean HWVideoPlayerFF::is_playback_likely_to_keep_up (HWVideoPlayerType hwvp)
{
    ASSERT(hwvp);

    //HWVideoPlayerFFInstance* hwvpi = reinterpret_cast<HWVideoPlayerFFInstance*>(hwvp);

    return true;
}

//==============================================================================
//==============================================================================

void HWVideoPlayerFF::play (HWVideoPlayerFF::HWVideoPlayerType hwvp)
{
#ifndef DT3_EDITOR
    ASSERT(hwvp);

    hwvp->play();
#endif
}

void HWVideoPlayerFF::pause (HWVideoPlayerFF::HWVideoPlayerType hwvp)
{
#ifndef DT3_EDITOR
    ASSERT(hwvp);

    hwvp->pause();
#endif
}

void HWVideoPlayerFF::rewind (HWVideoPlayerFF::HWVideoPlayerType hwvp)
{
    ASSERT(hwvp);

    seek(hwvp, 0.0F);
}

DTfloat HWVideoPlayerFF::length (HWVideoPlayerFF::HWVideoPlayerType hwvp)
{
#ifndef DT3_EDITOR
    ASSERT(hwvp);
    return hwvp->length();
#else
    return 0.0F;
#endif
}

DTfloat HWVideoPlayerFF::current_time (HWVideoPlayerFF::HWVideoPlayerType hwvp)
{
#ifndef DT3_EDITOR
    ASSERT(hwvp);
    return hwvp->current_time();
#else
    return 0.0F;
#endif
}

void HWVideoPlayerFF::seek (HWVideoPlayerFF::HWVideoPlayerType hwvp, DTfloat time)
{
#ifndef DT3_EDITOR
    ASSERT(hwvp);
    hwvp->seek(time);
#endif
}

//==============================================================================
//==============================================================================

void HWVideoPlayerFF::size (HWVideoPlayerType hwvp, DTuint &width, DTuint &height)
{
#ifndef DT3_EDITOR
    ASSERT(hwvp);
    
    width = hwvp->width();
    height = hwvp->height();
#else
    width = 0;
    height = 0;
#endif
}

HWVideoPlayerFF::State HWVideoPlayerFF::state (HWVideoPlayerFF::HWVideoPlayerType hwvp)
{
#ifndef DT3_EDITOR
    ASSERT(hwvp);
    
    switch (hwvp->state()) {
        case HWVideoPlayerFFInstance::STATE_IDLE:       return STATE_IDLE;
        case HWVideoPlayerFFInstance::STATE_PAUSED:     return STATE_PAUSED;
        case HWVideoPlayerFFInstance::STATE_PLAYING:    return STATE_PLAYING;
        case HWVideoPlayerFFInstance::STATE_CLOSING:    return STATE_CLOSING;
        case HWVideoPlayerFFInstance::STATE_ERROR:      return STATE_ERROR;
    }
#else
    return STATE_IDLE;
#endif
}

//==============================================================================
//==============================================================================

std::shared_ptr<TextureResource2D> HWVideoPlayerFF::frame (HWVideoPlayerType hwvp)
{
#ifndef DT3_EDITOR
    
    if (hwvp)
        return hwvp->texture();
    else
        return std::shared_ptr<TextureResource2D>();

#else
    return std::shared_ptr<TextureResource2D>();
#endif
}

//==============================================================================
//==============================================================================

Color4f HWVideoPlayerFF::sample_pixel (HWVideoPlayerType hwvp, DTint x, DTint y)
{
    return hwvp->sample_pixel(x,y);
}

//==============================================================================
//==============================================================================

} // DT3

