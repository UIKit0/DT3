//==============================================================================
///	
///	File: ComponentGUIVideoPlayer.cpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3HWVideoPlayer/ComponentGUIVideoPlayer.hpp"
#include "DT3Core/System/Factory.hpp"
#include "DT3Core/System/System.hpp"
#include "DT3Core/System/SystemCallbacks.hpp"
#include "DT3Core/Types/FileBuffer/ArchiveData.hpp"
#include "DT3Core/Types/FileBuffer/Archive.hpp"
#include "DT3Core/Types/Math/MoreMath.hpp"
#include "DT3Core/Types/Math/Color4f.hpp"
#include "DT3Core/Types/Network/URL.hpp"
#include "DT3Core/World/World.hpp"
#include "DT3Core/Objects/GUIObject.hpp"
#include "DT3Core/Objects/ObjectBase.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentGUIVideoPlayer,"GUI","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentGUIVideoPlayer)

IMPLEMENT_PLUG_INFO_INDEX(_file_or_url)

IMPLEMENT_PLUG_INFO_INDEX(_is_playing)
IMPLEMENT_PLUG_INFO_INDEX(_current_time)
IMPLEMENT_PLUG_INFO_INDEX(_length)

IMPLEMENT_PLUG_INFO_INDEX(_video_material)
IMPLEMENT_PLUG_INFO_INDEX(_play_material)
IMPLEMENT_PLUG_INFO_INDEX(_pause_material)
IMPLEMENT_PLUG_INFO_INDEX(_thumb_material)
IMPLEMENT_PLUG_INFO_INDEX(_track_loaded)
IMPLEMENT_PLUG_INFO_INDEX(_track_unloaded)
IMPLEMENT_PLUG_INFO_INDEX(_background)

IMPLEMENT_EVENT_INFO_INDEX(_play)
IMPLEMENT_EVENT_INFO_INDEX(_pause)
IMPLEMENT_EVENT_INFO_INDEX(_rewind)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentGUIVideoPlayer)
    
	PLUG_INIT(_file_or_url,"File_Or_URL")
		.set_input(true);

	PLUG_INIT(_current_time,"Current_time")
		.set_output(true);

	PLUG_INIT(_length,"Length")
		.set_output(true);

	PLUG_INIT(_is_playing,"Is_Playing")
		.set_output(true);

    PLUG_INIT(_video_material, "Video_Material")
		.set_input(true);

    PLUG_INIT(_play_material, "Play_Material")
		.set_input(true);
    
    PLUG_INIT(_pause_material, "Pause_Material")
		.set_input(true);
                
    PLUG_INIT(_thumb_material, "Thumb_Material")
		.set_input(true);
        
    PLUG_INIT(_track_loaded, "Track_Loaded")
		.set_input(true);

    PLUG_INIT(_track_unloaded, "Track_Unloaded")
		.set_input(true);

    PLUG_INIT(_background, "Background")
		.set_input(true);
    
	EVENT_INIT(_play,"Start")
        .set_input(true)
        .set_event(&ComponentGUIVideoPlayer::play);

	EVENT_INIT(_pause,"Stop")
        .set_input(true)
        .set_event(&ComponentGUIVideoPlayer::pause);

	EVENT_INIT(_rewind,"Rewind")
        .set_input(true)
        .set_event(&ComponentGUIVideoPlayer::rewind);

END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentGUIVideoPlayer::ComponentGUIVideoPlayer (void)
    :   _file_or_url    (PLUG_INFO_INDEX(_file_or_url)),
        _current_time   (PLUG_INFO_INDEX(_current_time), 0.0F),
        _length         (PLUG_INFO_INDEX(_length), 0.0F),
        _is_playing     (PLUG_INFO_INDEX(_is_playing), false),
        _video_material (PLUG_INFO_INDEX(_video_material)),
        _play_material  (PLUG_INFO_INDEX(_play_material)),
        _pause_material (PLUG_INFO_INDEX(_pause_material)),
        _thumb_material (PLUG_INFO_INDEX(_thumb_material)),
        _track_loaded   (PLUG_INFO_INDEX(_track_loaded)),
        _track_unloaded (PLUG_INFO_INDEX(_track_unloaded)),
        _background     (PLUG_INFO_INDEX(_background)),
        _play           (EVENT_INFO_INDEX(_play)),
        _pause          (EVENT_INFO_INDEX(_pause)),
        _rewind         (EVENT_INFO_INDEX(_rewind)),
        _controls_size  (0.02F),
        _track_size     (0.005F),
        _thumb_size     (0.01F),
        _hw             (NULL)
{

}
		
ComponentGUIVideoPlayer::ComponentGUIVideoPlayer (const ComponentGUIVideoPlayer &rhs)
    :   ComponentBase       (rhs),
		_file_or_url        (rhs._file_or_url),
		_current_time       (rhs._current_time),
		_length             (rhs._length),
		_is_playing         (rhs._is_playing),
        _video_material     (rhs._video_material),
        _play_material      (rhs._play_material),
        _pause_material     (rhs._pause_material),
        _thumb_material     (rhs._thumb_material),
        _track_loaded       (rhs._track_loaded),
        _track_unloaded     (rhs._track_unloaded),
        _background         (rhs._background),
        _play               (EVENT_INFO_INDEX(_play)),
        _pause              (EVENT_INFO_INDEX(_pause)),
        _rewind             (EVENT_INFO_INDEX(_rewind)),
        _controls_size      (rhs._controls_size),
        _track_size         (rhs._track_size),
        _thumb_size         (rhs._thumb_size),
        _hw                 (NULL)
{

}

ComponentGUIVideoPlayer & ComponentGUIVideoPlayer::operator = (const ComponentGUIVideoPlayer &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        
		_file_or_url = rhs._file_or_url;

		_current_time = rhs._current_time;
		_length = rhs._length;
		_is_playing = rhs._is_playing;

        _video_material = rhs._video_material;
        _play_material = rhs._play_material;
        _pause_material = rhs._pause_material;
        _thumb_material = rhs._thumb_material;
        _track_loaded = rhs._track_loaded;
        _track_unloaded = rhs._track_unloaded;
        _background = rhs._background;
        
        _controls_size = rhs._controls_size;
        _track_size = rhs._track_size;
        _thumb_size = rhs._thumb_size;

    }
    return (*this);
}
			
ComponentGUIVideoPlayer::~ComponentGUIVideoPlayer (void)
{
    close();
}

//==============================================================================
//==============================================================================

void ComponentGUIVideoPlayer::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentGUIVideoPlayer::archive (const std::shared_ptr<Archive> &archive)
{
    ComponentBase::archive(archive);

	archive->push_domain (class_id ());
    
	*archive << ARCHIVE_PLUG(_file_or_url, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_PLUG(_video_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_play_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_pause_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_thumb_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_track_loaded, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_track_unloaded, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_background, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA(_controls_size, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_track_size, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_thumb_size, DATA_PERSISTENT | DATA_SETTABLE);
    
    archive->pop_domain ();
}

void ComponentGUIVideoPlayer::archive_done (const std::shared_ptr<Archive> &archive)
{

    // Kickstart opening and getting the first frame of video
    _last_file_or_url = _file_or_url;
    
    // Check if we have a URL
    if (URL::is_URL(_file_or_url)) {
        open(URL(_file_or_url));
    } else {
        open(FilePath(_file_or_url));
    }
    
    
//    // Tie video texture to material
//    if (_hw && _video_material->is_valid()) {
//    
//        std::shared_ptr<TextureResource2D> tex = Video::get_frame(_hw);
//        (**_video_material).set_current_unit(0);
//        (**_video_material).set_texture(tex);
//    }

}

//==============================================================================
//==============================================================================

Rectangle ComponentGUIVideoPlayer::calc_play_pause_rect (const Rectangle &rect)
{
    DTfloat aspect = System::renderer()->screen_aspect();
    
    return Rectangle (  rect.minus_x(), rect.minus_x() + _controls_size / aspect,
                        rect.minus_y(), rect.minus_y() + _controls_size);
}

Rectangle ComponentGUIVideoPlayer::calc_seek_rect (const Rectangle &rect)
{
    DTfloat aspect = System::renderer()->screen_aspect();
    
    return Rectangle (  rect.minus_x() + _controls_size / aspect, rect.plus_x(),
                        rect.minus_y(), rect.minus_y() + _controls_size);
}

Rectangle ComponentGUIVideoPlayer::calc_track_rect (const Rectangle &rect)
{
    DTfloat aspect = System::renderer()->screen_aspect();
    DTfloat pad = (_controls_size - _track_size) * 0.5F;
    
    return Rectangle (  rect.minus_x() + (_controls_size + pad) / aspect, rect.plus_x() - pad / aspect,
                        rect.minus_y() + pad, rect.minus_y() + _controls_size - pad);

}

Rectangle ComponentGUIVideoPlayer::calc_thumb_rect (const Rectangle &rect, DTfloat current, DTfloat length)
{
    DTfloat aspect = System::renderer()->screen_aspect();
    DTfloat pad = (_controls_size - _track_size) * 0.5F;
    
    DTfloat min_x = rect.minus_x() + (_controls_size + pad) / aspect;
    DTfloat max_x = rect.plus_x() - pad / aspect;
    
    DTfloat t = MoreMath::clamp_zero_one(current / length);
    
    DTfloat x = (max_x - min_x) * t + min_x;
    DTfloat y = rect.minus_y() + _controls_size * 0.5F;
    
    return Rectangle (x - _thumb_size*0.5F/aspect, x + _thumb_size*0.5F/aspect, y - _thumb_size * 0.5F, y + _thumb_size*0.5F);
    
}

Rectangle ComponentGUIVideoPlayer::calc_background_rect (const Rectangle &rect)
{
    return Rectangle (  rect.minus_x(), rect.plus_x(),
                        rect.minus_y(), rect.minus_y() + _controls_size);
}

//==============================================================================
//==============================================================================

void ComponentGUIVideoPlayer::open (const FilePath &path)
{
    close();
    
    _hw = Video::open(path);
}

void ComponentGUIVideoPlayer::open (const URL &url)
{
    close();
    
    _hw = Video::open(url);
}

void ComponentGUIVideoPlayer::close (void)
{
    if (_hw) {
        Video::close(_hw);
    }
}

//==============================================================================
//==============================================================================

void ComponentGUIVideoPlayer::play (PlugNode *sender)
{   
    if (_hw) {
        Video::play(_hw);
    }
}

void ComponentGUIVideoPlayer::pause (PlugNode *sender)
{
    if (_hw) {
        Video::pause(_hw);
    }
}

void ComponentGUIVideoPlayer::rewind (PlugNode *sender)
{
    if (_hw) {
        Video::rewind(_hw);
    }
}

//==============================================================================
//==============================================================================

void ComponentGUIVideoPlayer::tick (const DTfloat dt)
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
    
    _current_time = Video::current_time(_hw);
    _length = Video::length(_hw);
    _is_playing = (Video::state(_hw) == Video::STATE_PLAYING);
}

//==============================================================================
//==============================================================================

void ComponentGUIVideoPlayer::draw (const std::shared_ptr<CameraObject> &camera, const Color4f &parent_color)
{
    GUIObject *gui = checked_cast<GUIObject*>(owner());
    if (!gui)
        return;
    
    if (gui->color().a_as_float() * parent_color.a_as_float() <= 0.0F)
        return;
       
    Rectangle local_rect = gui->rectangle();
    Matrix4 transform = gui->draw_transform();
    Color4f c = gui->color() * parent_color;
    
    
    // Video
//    if ( _video_material->valid() ) {
//        DrawBatcherQuads b;
//        
//        b.batchBegin(_video_material->get(), transform, DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);
//        
//        b.vertex(Vector3(local_rect.getMinusX(), local_rect.getMinusY(), 0.0F), Texcoord2(0.0F,0.0F), c);
//        b.vertex(Vector3(local_rect.getPlusX(), local_rect.getMinusY(), 0.0F), Texcoord2(1.0F,0.0F), c);
//        b.vertex(Vector3(local_rect.getPlusX(), local_rect.getPlusY(), 0.0F), Texcoord2(1.0F,1.0F), c);
//        b.vertex(Vector3(local_rect.getMinusX(), local_rect.getPlusY(), 0.0F), Texcoord2(0.0F,1.0F), c);
//        
//        b.batchEnd();
//    }

    // Background
//    if ( _background->valid() ) {
//        DrawBatcherQuads b;
//        Rectangle r = calc_background_rect(local_rect);
//        
//        b.batchBegin(_background->get(), transform, DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);
//        
//        b.vertex(Vector3(r.getMinusX(), r.getMinusY(), 0.0F), Texcoord2(0.0F,0.0F), c);
//        b.vertex(Vector3(r.getPlusX(), r.getMinusY(), 0.0F), Texcoord2(1.0F,0.0F), c);
//        b.vertex(Vector3(r.getPlusX(), r.getPlusY(), 0.0F), Texcoord2(1.0F,1.0F), c);
//        b.vertex(Vector3(r.getMinusX(), r.getPlusY(), 0.0F), Texcoord2(0.0F,1.0F), c);
//        
//        b.batchEnd();
//    }

    // Play/Pause
//    if ( _play_material->is_valid() && _pause_material->is_valid()) {
//        DrawBatcherQuads b;
//        Rectangle r = calc_play_pause_rect(local_rect);
//        
//        if (Video::get_state(_hw) == Video::STATE_PLAYING)
//            b.batchBegin(_pause_material->get(), transform, DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);
//        else
//            b.batchBegin(_play_material->get(), transform, DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);
//        
//        b.vertex(Vector3(r.getMinusX(), r.getMinusY(), 0.0F), Texcoord2(0.0F,0.0F), c);
//        b.vertex(Vector3(r.getPlusX(), r.getMinusY(), 0.0F), Texcoord2(1.0F,0.0F), c);
//        b.vertex(Vector3(r.getPlusX(), r.getPlusY(), 0.0F), Texcoord2(1.0F,1.0F), c);
//        b.vertex(Vector3(r.getMinusX(), r.getPlusY(), 0.0F), Texcoord2(0.0F,1.0F), c);
//        
//        b.batchEnd();
//    }

    // Track
//    if ( _track_unloaded->is_valid() ) {
//        DrawBatcherQuads b;
//        Rectangle r = calc_track_rect(local_rect);
//        
//        b.batchBegin(_track_unloaded->get(), transform, DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);
//        
//        b.vertex(Vector3(r.getMinusX(), r.getMinusY(), 0.0F), Texcoord2(0.0F,0.0F), c);
//        b.vertex(Vector3(r.getPlusX(), r.getMinusY(), 0.0F), Texcoord2(1.0F,0.0F), c);
//        b.vertex(Vector3(r.getPlusX(), r.getPlusY(), 0.0F), Texcoord2(1.0F,1.0F), c);
//        b.vertex(Vector3(r.getMinusX(), r.getPlusY(), 0.0F), Texcoord2(0.0F,1.0F), c);
//        
//        b.batchEnd();
//    }

    // Thumb
//    if ( _thumb_material->is_valid() ) {
//        DrawBatcherQuads b;
//        Rectangle r = calc_thumb_rect(local_rect, _current_time, _length);
//        
//        b.batchBegin(_thumb_material->get(), transform, DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);
//        
//        b.vertex(Vector3(r.getMinusX(), r.getMinusY(), 0.0F), Texcoord2(0.0F,0.0F), c);
//        b.vertex(Vector3(r.getPlusX(), r.getMinusY(), 0.0F), Texcoord2(1.0F,0.0F), c);
//        b.vertex(Vector3(r.getPlusX(), r.getPlusY(), 0.0F), Texcoord2(1.0F,1.0F), c);
//        b.vertex(Vector3(r.getMinusX(), r.getPlusY(), 0.0F), Texcoord2(0.0F,1.0F), c);
//        
//        b.batchEnd();
//    }
    
    
    
}

//==============================================================================
//==============================================================================

void ComponentGUIVideoPlayer::touches_began (GUITouchEvent *event)
{
    GUIObject *gui = checked_cast<GUIObject*>(owner());
    if (!gui)
        return;
    
}

void ComponentGUIVideoPlayer::touches_moved (GUITouchEvent *event)
{
    GUIObject *gui = checked_cast<GUIObject*>(owner());
    if (!gui)
        return;
    
}

void ComponentGUIVideoPlayer::touches_ended (GUITouchEvent *event)
{
    GUIObject *gui = checked_cast<GUIObject*>(owner());
    if (!gui)
        return;
    
    if (!_hw)
        return;
    
    // Transform touches into widget coordinates
    Vector2 pos = gui->position_to_object_coord(event->position());
    Rectangle local_rect = gui->rectangle();

    //
    // Play/Pause
    //
    
    Rectangle play_pause = calc_play_pause_rect(local_rect);
    if (play_pause.is_touching(pos)) {
        
        if (Video::state(_hw) == Video::STATE_PLAYING) {
            Video::pause(_hw);
        } else {
            Video::play(_hw);
        }
        
        return;
    }
    
    //
    // Timeline
    //
    
    Rectangle seek_rect = calc_seek_rect(local_rect);
    if (seek_rect.is_touching(pos)) {
        Rectangle track_rect = calc_track_rect(local_rect);

        DTfloat t = MoreMath::clamp_zero_one( (pos.x - track_rect.minus_x()) / (track_rect.plus_x() - track_rect.minus_x()) );
        Video::seek(_hw, t * Video::length(_hw));
        
        return;
    }
    
}

void ComponentGUIVideoPlayer::touches_cancelled (GUITouchEvent *event)
{
    GUIObject *gui = checked_cast<GUIObject*>(owner());
    if (!gui)
        return;

}

//==============================================================================
//==============================================================================

void ComponentGUIVideoPlayer::add_to_owner (ObjectBase *owner)
{
    ComponentBase::add_to_owner(owner);
    
    owner->world()->register_for_tick(owner, make_callback(this, &type::tick));

    GUIObject *gui = checked_cast<GUIObject*>(owner);
    if (gui) {
        gui->touches_began_callbacks().add(make_callback(this, &type::touches_began));
        gui->touches_moved_callbacks().add(make_callback(this, &type::touches_moved));
        gui->touches_ended_callbacks().add(make_callback(this, &type::touches_ended));
        gui->touches_cancelled_callbacks().add(make_callback(this, &type::touches_cancelled));

        gui->draw_gui_callbacks().add(make_callback(this, &type::draw));
    }
}

void ComponentGUIVideoPlayer::remove_from_owner (void)
{
    GUIObject *gui = checked_cast<GUIObject*>(owner());
    if (gui) {
        gui->touches_began_callbacks().remove(make_callback(this, &type::touches_began));
        gui->touches_moved_callbacks().remove(make_callback(this, &type::touches_moved));
        gui->touches_ended_callbacks().remove(make_callback(this, &type::touches_ended));
        gui->touches_cancelled_callbacks().remove(make_callback(this, &type::touches_cancelled));

        gui->draw_gui_callbacks().remove(make_callback(this, &type::draw));
    }

    owner()->world()->unregister_for_tick(owner(), make_callback(this, &type::tick));

    ComponentBase::remove_from_owner();
}

//==============================================================================
//==============================================================================

} // DT3

