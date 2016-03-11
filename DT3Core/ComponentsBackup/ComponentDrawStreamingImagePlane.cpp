//==============================================================================
///	
///	File: ComponentDrawStreamingImagePlane.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentDrawStreamingImagePlane.hpp"
#include "ArchiveObjectQueue.hpp"
#include "ConsoleStream.hpp"
#include "Factory.hpp"
#include "MaterialResource.hpp"
#include "World.hpp"
#include "PlaceableObject.hpp"
#include "ArchivePropertyReaderWriter.hpp"
#include "ShaderResource.hpp"
#include "DeviceGraphics.hpp"
#include "System.hpp"
#include "DrawBatcherQuads.hpp"
#include "Box.hpp"
#include "CameraObject.hpp"
#include "LatentCall.hpp"

#include "ThreadTaskQueue.hpp"
#include "ThreadMainTaskQueue.hpp"

#include "PNGWriter.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentDrawStreamingImagePlane,"Drawing","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentDrawStreamingImagePlane)

IMPLEMENT_PLUG_INFO(_preview_texture)
IMPLEMENT_PLUG_INFO(_full_texture)
IMPLEMENT_PLUG_INFO(_material)
IMPLEMENT_PLUG_INFO(_color)
IMPLEMENT_PLUG_INFO(_flip_horz)
IMPLEMENT_PLUG_INFO(_flip_vert)

IMPLEMENT_PLUG_INFO(_p0)
IMPLEMENT_PLUG_INFO(_p1)
IMPLEMENT_PLUG_INFO(_p2)
IMPLEMENT_PLUG_INFO(_p3)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentDrawStreamingImagePlane)
        
    PLUG_INIT(_preview_texture, "Preview_texture")
		.setInput(true);

    PLUG_INIT(_full_texture, "Full_Texture")
		.setInput(true);
        
    PLUG_INIT(_material, "Material")
		.setInput(true);
        
    PLUG_INIT(_color, "Color")
		.setInput(true);
        
    PLUG_INIT(_flip_horz, "Flip_Horz")
		.setInput(true);
        
    PLUG_INIT(_flip_vert, "Flip_Vert")
		.setInput(true);
        
    PLUG_INIT(_p0, "Param0")
		.setInput(true);

    PLUG_INIT(_p1, "Param1")
		.setInput(true);

    PLUG_INIT(_p2, "Param2")
		.setInput(true);

    PLUG_INIT(_p3, "Param3")
		.setInput(true);

END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentDrawStreamingImagePlane::ComponentDrawStreamingImagePlane (void)
    :   _preview_texture    (PLUG_INFO(_preview_texture)),
        _full_texture       (PLUG_INFO(_full_texture)),
        _material           (PLUG_INFO(_material)),
        _fade_speed          (1.0F),
        _preview_fade       (0.0F),
        _full_fade          (0.0F),
        _color              (PLUG_INFO(_color), Color(1.0F,1.0F,1.0F,1.0F)),
        _aspect             (1.0F),
        _flip_horz          (PLUG_INFO(_flip_horz), false),
        _flip_vert          (PLUG_INFO(_flip_vert), false),
        _p0                 (PLUG_INFO(_p0), 0.0F),
        _p1                 (PLUG_INFO(_p1), 0.0F),
        _p2                 (PLUG_INFO(_p2), 0.0F),
        _p3                 (PLUG_INFO(_p3), 0.0F),
        _params_pos         (-1),
        _preview_state              (STATE_UNLOADED),
        _full_state                 (STATE_UNLOADED),
        _preview_load_behaviour     (LOAD_NORMAL),
        _full_load_behaviour        (LOAD_THREADED),
        _preview_unload_behaviour   (UNLOAD_NEVER),
        _full_unload_behaviour      (UNLOAD_ALWAYS)
{

}
		
ComponentDrawStreamingImagePlane::ComponentDrawStreamingImagePlane (const ComponentDrawStreamingImagePlane &rhs)
    :   ComponentBase       (rhs),
        _preview_texture    (rhs._preview_texture),
        _full_texture       (rhs._full_texture),
        _material           (rhs._material),
        _fade_speed         (rhs._fade_speed),
        _preview_fade       (rhs._preview_fade),
        _full_fade          (rhs._full_fade),
        _color              (rhs._color),
        _aspect             (rhs._aspect),
        _flip_horz          (rhs._flip_horz),
        _flip_vert          (rhs._flip_vert),
        _p0                 (rhs._p0),
        _p1                 (rhs._p1),
        _p2                 (rhs._p2),
        _p3                 (rhs._p3),
        _params_pos         (rhs._params_pos),
        _preview_state              (STATE_UNLOADED),
        _full_state                 (STATE_UNLOADED),
        _preview_load_behaviour     (rhs._preview_load_behaviour),
        _full_load_behaviour        (rhs._full_load_behaviour),
        _preview_unload_behaviour   (rhs._preview_unload_behaviour),
        _full_unload_behaviour      (rhs._full_unload_behaviour)
{

}

ComponentDrawStreamingImagePlane & ComponentDrawStreamingImagePlane::operator = (const ComponentDrawStreamingImagePlane &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        
        _preview_texture = rhs._preview_texture;
        _full_texture = rhs._full_texture;
        _material = rhs._material;
        
        _fade_speed = rhs._fade_speed;
        
        _preview_fade = rhs._preview_fade;
        _full_fade = rhs._full_fade;
        
        _aspect = rhs._aspect;
        _color = rhs._color;
        
        _flip_horz = rhs._flip_horz;
        _flip_vert = rhs._flip_vert;
        
        _p0 = rhs._p0;
        _p1 = rhs._p1;
        _p2 = rhs._p2;
        _p3 = rhs._p3;
        
        _params_pos = rhs._params_pos;
        
        unloadPreview();
        unloadFull();

        _preview_load_behaviour = rhs._preview_load_behaviour;
        _full_load_behaviour = rhs._full_load_behaviour;
        _preview_unload_behaviour = rhs._preview_unload_behaviour;
        _full_unload_behaviour = rhs._full_unload_behaviour;
    }
    return (*this);
}
			
ComponentDrawStreamingImagePlane::~ComponentDrawStreamingImagePlane (void)
{
    // Finish loading so we can clean up properly
    while (_preview_state == STATE_LOADING || _full_state == STATE_LOADING) {
        ThreadMainTaskQueue::runQueue();
        ThreadTaskQueue::runQueue();
    }

    unloadPreview();
    unloadFull();
}

//==============================================================================
//==============================================================================

void ComponentDrawStreamingImagePlane::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentDrawStreamingImagePlane::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
    
    *archive << ARCHIVE_DATA_ACCESSORS("Preview_Texture", ComponentDrawStreamingImagePlane::getPreviewTexture, ComponentDrawStreamingImagePlane::setPreviewTexture, DATA_PERSISTENT | DATA_SETTABLE);
   
    if (archive->getVersion() >= 1376) {
        *archive << ARCHIVE_DATA(_preview_load_behaviour, DATA_PERSISTENT | DATA_SETTABLE)
            .addEnum("Normal Load")
            .addEnum("Threaded Load");
        *archive << ARCHIVE_DATA(_preview_unload_behaviour, DATA_PERSISTENT | DATA_SETTABLE)
            .addEnum("Never Unload")
            .addEnum("Always Unload");
    }
   
    if (archive->isA(ArchivePropertyReaderWriter::kind()))
        *archive << ARCHIVE_DATA_ACCESSORS("Full_Texture", ComponentDrawStreamingImagePlane::getTexture, ComponentDrawStreamingImagePlane::setTextureProp, DATA_PERSISTENT | DATA_SETTABLE);
	else
        *archive << ARCHIVE_DATA_ACCESSORS("Full_Texture", ComponentDrawStreamingImagePlane::getTexture, ComponentDrawStreamingImagePlane::setTexture, DATA_PERSISTENT | DATA_SETTABLE);
    
    if (archive->getVersion() >= 1376) {
        *archive << ARCHIVE_DATA(_full_load_behaviour, DATA_PERSISTENT | DATA_SETTABLE)
            .addEnum("Normal Load")
            .addEnum("Threaded Load");
        *archive << ARCHIVE_DATA(_full_unload_behaviour, DATA_PERSISTENT | DATA_SETTABLE)
            .addEnum("Never Unload")
            .addEnum("Always Unload");
    }

    *archive << ARCHIVE_DATA_ACCESSORS("Material", ComponentDrawStreamingImagePlane::getMaterial, ComponentDrawStreamingImagePlane::setMaterial, DATA_PERSISTENT | DATA_SETTABLE);

    if (archive->getVersion() >= 1376) {
        *archive << ARCHIVE_DATA(_fade_speed, DATA_PERSISTENT | DATA_SETTABLE);
    }
    
	*archive << ARCHIVE_PLUG(_color, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_aspect, DATA_PERSISTENT | DATA_SETTABLE);
    
    *archive << ARCHIVE_PLUG(_flip_horz, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_flip_vert, DATA_PERSISTENT | DATA_SETTABLE);

    *archive << ARCHIVE_PLUG(_p0, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_p1, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_p2, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_p3, DATA_PERSISTENT | DATA_SETTABLE);
    
    archive->pop_domain ();
}

void ComponentDrawStreamingImagePlane::archive_read_done()
{
    ComponentBase::archive_read_done();
}

void ComponentDrawStreamingImagePlane::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	
    *archive << ARCHIVE_DATA_ACCESSORS("Preview_Texture", ComponentDrawStreamingImagePlane::getPreviewTexture, ComponentDrawStreamingImagePlane::setPreviewTexture, DATA_PERSISTENT | DATA_SETTABLE);

    *archive << ARCHIVE_DATA(_preview_load_behaviour, DATA_PERSISTENT | DATA_SETTABLE)
        .addEnum("Normal Load")
        .addEnum("Threaded Load");
    *archive << ARCHIVE_DATA(_preview_unload_behaviour, DATA_PERSISTENT | DATA_SETTABLE)
        .addEnum("Never Unload")
        .addEnum("Always Unload");

    if (archive->isA(ArchivePropertyReaderWriter::kind()))
        *archive << ARCHIVE_DATA_ACCESSORS("Full_Texture", ComponentDrawStreamingImagePlane::getTexture, ComponentDrawStreamingImagePlane::setTextureProp, DATA_PERSISTENT | DATA_SETTABLE);
	else
        *archive << ARCHIVE_DATA_ACCESSORS("Full_Texture", ComponentDrawStreamingImagePlane::getTexture, ComponentDrawStreamingImagePlane::setTexture, DATA_PERSISTENT | DATA_SETTABLE);

    *archive << ARCHIVE_DATA(_full_load_behaviour, DATA_PERSISTENT | DATA_SETTABLE)
        .addEnum("Normal Load")
        .addEnum("Threaded Load");
    *archive << ARCHIVE_DATA(_full_unload_behaviour, DATA_PERSISTENT | DATA_SETTABLE)
        .addEnum("Never Unload")
        .addEnum("Always Unload");

    *archive << ARCHIVE_DATA_ACCESSORS("Material", ComponentDrawStreamingImagePlane::getMaterial, ComponentDrawStreamingImagePlane::setMaterial, DATA_PERSISTENT | DATA_SETTABLE);

    *archive << ARCHIVE_DATA(_fade_speed, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_PLUG(_color, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_aspect, DATA_PERSISTENT | DATA_SETTABLE);

    *archive << ARCHIVE_PLUG(_flip_horz, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_flip_vert, DATA_PERSISTENT | DATA_SETTABLE);

    *archive << ARCHIVE_PLUG(_p0, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_p1, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_p2, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_p3, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentDrawStreamingImagePlane::beginLoadPreview (void)
{
    // Make sure image isn't loaded yet
    if (_preview_state != STATE_UNLOADED)
        return;
    
#ifndef DT3_EDITOR
    if (_preview_load_behaviour == LOAD_THREADED) {

        retain();   // Retain this object so it doesn't disappear while thread is running
        _preview_state = STATE_LOADING;
        _preview_fade = 0.0F;

        // Load file in task thread
        ThreadTaskQueue::addTask(0, makeLatentCall(this, &ComponentDrawStreamingImagePlane::loadPreview, _preview_texture.asRef()));
    
    } else {
#endif
        
        // All gets done immediately
        std::shared_ptr<TextureResource> tex = makeSmartPtr(TextureResource::create());
        if (tex->import(_preview_texture,"") == DT3_ERR_NONE && tex->load() == DT3_ERR_NONE) {
            
            _cache_preview_texture = tex;
            _preview_state = STATE_LOADED;
            _preview_fade = _fade_speed;
        } else {
            _preview_state = STATE_ERROR;
        }
        
        _preview_fade = _fade_speed;
        
#ifndef DT3_EDITOR
    }
#endif
}

void ComponentDrawStreamingImagePlane::loadPreview (FilePath path)
{
    // All gets done immediately
    std::shared_ptr<TextureResource> tex = makeSmartPtr(TextureResource::create());
    if (tex->import(path,"") == DT3_ERR_NONE && tex->load() == DT3_ERR_NONE) {
        
        Assert(_cache_preview_texture.isNull());

        _cache_preview_texture = tex;
        _preview_state = STATE_LOADED;
    } else {
        _preview_state = STATE_ERROR;
    }
    
    ThreadMainTaskQueue::addTask(0, makeLatentCall(this, &ComponentDrawStreamingImagePlane::loadPreviewDone, tex));
}

void ComponentDrawStreamingImagePlane::loadPreviewDone (std::shared_ptr<TextureResource> tex)
{
    release();
}

void ComponentDrawStreamingImagePlane::unloadPreview (void)
{
    if (_preview_state == STATE_LOADED) {
        _preview_state = STATE_UNLOADED;
        _preview_fade = 0.0F;
        
        _cache_preview_texture = std::shared_ptr<TextureResource>();
    }
}

//==============================================================================
//==============================================================================

void ComponentDrawStreamingImagePlane::beginLoadFull (void)
{
    // Make sure image isn't loaded yet
    if (_full_state != STATE_UNLOADED)
        return;
    
#ifndef DT3_EDITOR
    if (_full_load_behaviour == LOAD_THREADED) {

        retain();   // Retain this object so it doesn't disappear while thread is running
        _full_state = STATE_LOADING;
        _full_fade = 0.0F;

        // Load file in task thread
        ThreadTaskQueue::addTask(0, makeLatentCall(this, &ComponentDrawStreamingImagePlane::loadFull, _full_texture.asRef()));
    
    } else {
#endif
    
        // All gets done immediately
        std::shared_ptr<TextureResource> tex = makeSmartPtr(TextureResource::create());
        if (tex->import(_full_texture,"") == DT3_ERR_NONE && tex->load() == DT3_ERR_NONE) {
            _cache_full_texture = tex;
            _full_state = STATE_LOADED;
            _full_fade = _fade_speed;
        } else {
            _full_state = STATE_ERROR;
        }
        
#ifndef DT3_EDITOR
    }
#endif
}

void ComponentDrawStreamingImagePlane::loadFull (FilePath path)
{
    std::shared_ptr<TextureResource> tex = makeSmartPtr(TextureResource::create());
    if (tex->import(path,"") == DT3_ERR_NONE && tex->load() == DT3_ERR_NONE) {
        Assert(_cache_full_texture.isNull());
        
        _cache_full_texture = tex;
        _full_state = STATE_LOADED;
    } else {
        _full_state = STATE_ERROR;
    }
    
    ThreadMainTaskQueue::addTask(0, makeLatentCall(this, &ComponentDrawStreamingImagePlane::loadFullDone, tex));
}

void ComponentDrawStreamingImagePlane::loadFullDone (std::shared_ptr<TextureResource> tex)
{
    release();
}

void ComponentDrawStreamingImagePlane::unloadFull (void)
{
    if (_full_state == STATE_LOADED) {
        _full_state = STATE_UNLOADED;
        _full_fade = 0.0F;
        
        _cache_full_texture = std::shared_ptr<TextureResource>();
    }
}

//==============================================================================
//==============================================================================

const FilePath& ComponentDrawStreamingImagePlane::getTexture (void) const
{
    return _full_texture.asRef();
}

void ComponentDrawStreamingImagePlane::setTexture (const FilePath &texture)
{
    unloadFull();
    _full_texture = texture;
    _full_state = STATE_UNLOADED;
}

void ComponentDrawStreamingImagePlane::setTextureProp (const FilePath &texture)
{
    unloadFull();
    _full_texture = texture;
    
    // Okay, this is a stupid hack for the editor. Just load in the image to get its
    // aspect ratio.
    
    std::shared_ptr<TextureResource> tex = makeSmartPtr(TextureResource::create());
    if (tex->import(_full_texture,"") == DT3_ERR_NONE && tex->load() == DT3_ERR_NONE) {
        setAspect(tex->getWidth()/tex->getHeight());
    }

}

//==============================================================================
//==============================================================================

const FilePath& ComponentDrawStreamingImagePlane::getPreviewTexture (void) const
{
    return _preview_texture.asRef();
}

void ComponentDrawStreamingImagePlane::setPreviewTexture (const FilePath & preview_texture)
{
    unloadPreview();
    _preview_texture = preview_texture;
    _preview_state = STATE_UNLOADED;
}

//==============================================================================
//==============================================================================

void ComponentDrawStreamingImagePlane::draw (CameraObject* camera)
{
    if (_material->isNull()) {
        unloadPreview();
        unloadFull();
        return;
    }
        
    if (getColor().getA() <= 0) {
        unloadPreview();
        unloadFull();
        return;
    }
        
    PlaceableObject *placeable = checkedCast<PlaceableObject*>(getOwner());
    if (!placeable)
        return;
    
    DTfloat width, height;
    if (_aspect > 1.0F) {
        width = 1.0F;
        height = 1.0F / _aspect;
        
    } else if (_aspect < 1.0F) {
        width = _aspect;
        height = 1.0F;

    } else {
        width = 1.0F;
        height = 1.0F;

    }
    
    DTfloat tc_s_min = 0.0F;
    DTfloat tc_s_max = 1.0F;
    DTfloat tc_t_min = 0.0F;
    DTfloat tc_t_max = 1.0F;
    
    if (_flip_horz) std::swap(tc_s_min, tc_s_max);
    if (_flip_vert) std::swap(tc_t_min, tc_t_max);
    
    // Check visibility
    Matrix4 transform = placeable->getTransform();
    
    Vector3 p0 = transform * Vector3(-width,-height,0.0F);
    Vector3 p1 = transform * Vector3(width,-height,0.0F);
    Vector3 p2 = transform * Vector3(width,height,0.0F);
    Vector3 p3 = transform * Vector3(-width,height,0.0F);
    
    DTfloat min_x = min4(p0.x, p1.x, p2.x, p3.x);
    DTfloat max_x = max4(p0.x, p1.x, p2.x, p3.x);
    DTfloat min_y = min4(p0.y, p1.y, p2.y, p3.y);
    DTfloat max_y = max4(p0.y, p1.y, p2.y, p3.y);
    DTfloat min_z = min4(p0.z, p1.z, p2.z, p3.z);
    DTfloat max_z = max4(p0.z, p1.z, p2.z, p3.z);
    
    if (!camera->boxInFrustum(Box(min_x, max_x, min_y, max_y, min_z, max_z))) {
    
        if (!camera->isPicking()) {
            if (_preview_unload_behaviour == UNLOAD_ALWAYS) unloadPreview();
            if (_full_unload_behaviour == UNLOAD_ALWAYS)    unloadFull();
        }
        
        return;
    }
    
    //
    // Make sure we are loading or are loaded
    //
    
    if (_full_state != STATE_LOADED) {
        beginLoadPreview();
        beginLoadFull();
    }
    
    //
    // Animate Preview and Full images
    //
    
    DTfloat dt = _fade_timer.getDeltaTime();
    if (dt > 0.05F)
        dt = 0.05F;

    if (_full_state == STATE_LOADED) {
        
        // Ramp up ful image
        _full_fade = MoreMath::clampZeroOne(_full_fade + dt * _fade_speed);
        
        // If full fully displayed
        if (_full_fade >= 1.0F) {
            _preview_fade = MoreMath::clampZeroOne(_preview_fade - dt * _fade_speed);

            // If preview fully ramped down
            if (_preview_fade <= 0.0F) {
                if (_preview_unload_behaviour == UNLOAD_ALWAYS)
                    unloadPreview();
            }
        }
        
    } else if (_preview_state == STATE_LOADED) {
        _preview_fade = MoreMath::clampZeroOne(_preview_fade + dt * _fade_speed);

    }
    
    
    // Get full image loading
    if (_params_pos >= 0)
        (*_material)->getShader()->setParameterValue(_params_pos,0, _p0,_p1,_p2,_p3);
    
    // Draw preview image
    if (_preview_state == STATE_LOADED) {
    
        (*_material)->setCurrentUnit(0);
        (*_material)->setTexture(_cache_preview_texture);
        
        DrawBatcherQuads b;
        b.batchBegin(_material->get(), placeable->getTransform(), DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);

        Color c(_color * Color(1.0F,1.0F,1.0F,_preview_fade));
        
        b.vertex(Vector3(-width,-height,0.0F), Texcoord2(tc_s_min,tc_t_min), c);
        b.vertex(Vector3(+width,-height,0.0F), Texcoord2(tc_s_max,tc_t_min), c);
        b.vertex(Vector3(+width,+height,0.0F), Texcoord2(tc_s_max,tc_t_max), c);
        b.vertex(Vector3(-width,+height,0.0F), Texcoord2(tc_s_min,tc_t_max), c);
        
        b.batchEnd();
    }

    // Draw the full image
    if (_full_state == STATE_LOADED) {
    
        (*_material)->setCurrentUnit(0);
        (*_material)->setTexture(_cache_full_texture);
        
        DrawBatcherQuads b;
        b.batchBegin(_material->get(), placeable->getTransform(), DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);

        Color c(_color * Color(1.0F,1.0F,1.0F,_full_fade));
        
        b.vertex(Vector3(-width,-height,0.0F), Texcoord2(tc_s_min,tc_t_min), c);
        b.vertex(Vector3(+width,-height,0.0F), Texcoord2(tc_s_max,tc_t_min), c);
        b.vertex(Vector3(+width,+height,0.0F), Texcoord2(tc_s_max,tc_t_max), c);
        b.vertex(Vector3(-width,+height,0.0F), Texcoord2(tc_s_min,tc_t_max), c);
        
        b.batchEnd();
        
    }
    
    
}

//==============================================================================
//==============================================================================

void ComponentDrawStreamingImagePlane::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    World *w = getOwner()->getWorld();

    w->registerForDraw(getOwner(), makeCallback(this, &type::draw));
}

void ComponentDrawStreamingImagePlane::removeFromOwner (void)
{
    World *w = getOwner()->getWorld();

    w->unregisterForDraw(getOwner(), makeCallback(this, &type::draw));

    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

} // DT3

