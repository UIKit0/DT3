//==============================================================================
///	
///	File: ScriptingVideoTexture.cpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3HWVideoPlayer/ScriptingVideoTexture.hpp"
#include "DT3Core/System/Factory.hpp"
#include "DT3Core/System/SystemCallbacks.hpp"
#include "DT3Core/Types/FileBuffer/ArchiveData.hpp"
#include "DT3Core/Types/FileBuffer/Archive.hpp"
#include "DT3Core/World/World.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_SCRIPT(ScriptingVideoTexture,"Video",NULL)
IMPLEMENT_PLUG_NODE(ScriptingVideoTexture)

IMPLEMENT_PLUG_INFO_INDEX(_file_or_url)
IMPLEMENT_PLUG_INFO_INDEX(_is_playing)
IMPLEMENT_PLUG_INFO_INDEX(_out)
IMPLEMENT_PLUG_INFO_INDEX(_rectangle)
IMPLEMENT_PLUG_INFO_INDEX(_current_time)
IMPLEMENT_PLUG_INFO_INDEX(_length)

IMPLEMENT_EVENT_INFO_INDEX(_play)
IMPLEMENT_EVENT_INFO_INDEX(_pause)
IMPLEMENT_EVENT_INFO_INDEX(_rewind)
		
//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ScriptingVideoTexture)
		
	PLUG_INIT(_file_or_url,"File_Or_URL")
		.set_input(true);

	PLUG_INIT(_out,"Tex_Out")
		.set_output(true);

	PLUG_INIT(_current_time,"Current_time")
		.set_output(true);

	PLUG_INIT(_length,"Length")
		.set_output(true);

	PLUG_INIT(_is_playing,"Is_Playing")
		.set_output(true);

	PLUG_INIT(_rectangle,"Rect")
		.set_output(true);

	EVENT_INIT(_play,"Start")
        .set_input(true)
        .set_event(&ScriptingVideoTexture::play);

	EVENT_INIT(_pause,"Stop")
        .set_input(true)
        .set_event(&ScriptingVideoTexture::pause);

	EVENT_INIT(_rewind,"Rewind")
        .set_input(true)
        .set_event(&ScriptingVideoTexture::rewind);

END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ScriptingVideoTexture::ScriptingVideoTexture (void)
    :	_file_or_url            (PLUG_INFO_INDEX(_file_or_url)),
        _out                    (PLUG_INFO_INDEX(_out)),
        _current_time           (PLUG_INFO_INDEX(_current_time), 0.0F),
        _length                 (PLUG_INFO_INDEX(_length), 0.0F),
        _is_playing             (PLUG_INFO_INDEX(_is_playing), false),
		_rectangle              (PLUG_INFO_INDEX(_rectangle), Rectangle(0.0F,1.0F,0.0F,1.0F)),
        _play                   (EVENT_INFO_INDEX(_play)),
        _pause                  (EVENT_INFO_INDEX(_pause)),
        _rewind                 (EVENT_INFO_INDEX(_rewind)),
        _hw                     (NULL)
{

}
		
ScriptingVideoTexture::ScriptingVideoTexture (const ScriptingVideoTexture &rhs)
    :   ScriptingBase           (rhs),
		_file_or_url            (rhs._file_or_url),
		_out                    (rhs._out),
		_current_time           (rhs._current_time),
		_length                 (rhs._length),
		_is_playing             (rhs._is_playing),
		_rectangle              (rhs._rectangle),
        _play                   (EVENT_INFO_INDEX(_play)),
        _pause                  (EVENT_INFO_INDEX(_pause)),
        _rewind                 (EVENT_INFO_INDEX(_rewind)),
        _hw                     (NULL)
{

}

ScriptingVideoTexture & ScriptingVideoTexture::operator = (const ScriptingVideoTexture &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ScriptingBase::operator = (rhs);

        _file_or_url = rhs._file_or_url;
        _last_file_or_url.clear();
        
        _out = rhs._out;
        _current_time = rhs._current_time;
        _length = rhs._length;
        
        _is_playing = rhs._is_playing;
        _rectangle = rhs._rectangle;
        
        close();
	}
    return (*this);
}
			
ScriptingVideoTexture::~ScriptingVideoTexture (void)
{
    close();
}

//==============================================================================
//==============================================================================

void ScriptingVideoTexture::initialize (void)
{
	ScriptingBase::initialize();
}

//==============================================================================
//==============================================================================

void ScriptingVideoTexture::archive (const std::shared_ptr<Archive> &archive)
{
    ScriptingBase::archive(archive);

	archive->push_domain (class_id ());
    
    *archive << ARCHIVE_PLUG(_file_or_url, DATA_PERSISTENT | DATA_SETTABLE);
    
    archive->pop_domain ();
}

void ScriptingVideoTexture::archive_done (const std::shared_ptr<Archive> &archive)
{

    // Kickstart opening and getting the first frame of video
    _last_file_or_url = _file_or_url;
    
    // Check if we have a URL
    if (URL::is_URL(_file_or_url)) {
        open(URL(_file_or_url));
    } else {
        open(FilePath(_file_or_url));
    }

    _out = Video::frame(_hw);
}

//==============================================================================
//==============================================================================

void ScriptingVideoTexture::open (const FilePath &path)
{
    close();
    
    _hw = Video::open(path);
}

void ScriptingVideoTexture::open (const URL &url)
{
    close();
    
    _hw = Video::open(url);
}

void ScriptingVideoTexture::close (void)
{
    if (_hw) {
        Video::close(_hw);
    }
}

//==============================================================================
//==============================================================================

void ScriptingVideoTexture::play (PlugNode *sender)
{   
    if (_hw) {
        Video::play(_hw);
    }
}

void ScriptingVideoTexture::pause (PlugNode *sender)
{
    if (_hw) {
        Video::pause(_hw);
    }
}

void ScriptingVideoTexture::rewind (PlugNode *sender)
{
    if (_hw) {
        Video::rewind(_hw);
    }
}

//==============================================================================
//==============================================================================

DTfloat ScriptingVideoTexture::length (void) const
{
    if (_hw) {
        return Video::length(_hw);
    } else {
        return 0.0F;
    }
}

void ScriptingVideoTexture::seek (DTfloat time)
{
    if (_hw) {
        Video::seek(_hw, time);
    }
}

//==============================================================================
//==============================================================================

void ScriptingVideoTexture::tick (const DTfloat dt)
{
    // Check for path change
    if (_last_file_or_url != *_file_or_url) {
        _last_file_or_url = _file_or_url;
    
        close();
        
        // Check if we have a URL
        if (URL::is_URL(_file_or_url)) {
            open(URL(_file_or_url));
        } else {
            open(FilePath(_file_or_url));
        }
    
    }

    if (!_hw)
        return;
    
    Video::State state = Video::state(_hw);
    
    if (state == Video::STATE_PAUSED || state == Video::STATE_PLAYING) {
        std::shared_ptr<TextureResource2D> tex = Video::frame(_hw);
        
        _out = tex;
        _rectangle->set(0.0F, 1.0F, 0.0F, 1.0F);
        _rectangle.set_dirty();
    }
    
    _current_time = Video::current_time(_hw);
    _length = Video::length(_hw);
    _is_playing = (state == Video::STATE_PLAYING);
}

//==============================================================================
//==============================================================================

void ScriptingVideoTexture::add_to_world (World *world)
{
    ScriptingBase::add_to_world(world);
    
    world->register_for_tick(this, make_callback(this, &type::tick));
}

void ScriptingVideoTexture::remove_from_world (void)
{
    world()->unregister_for_tick(this, make_callback(this, &type::tick));

    ScriptingBase::remove_from_world();
}

//==============================================================================
//==============================================================================

} // DT3

