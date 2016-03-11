//==============================================================================
///	
///	File: ComponentDrawStreamingImageSequencePlane.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentDrawStreamingImageSequencePlane.hpp"
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

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentDrawStreamingImageSequencePlane,"Drawing","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentDrawStreamingImageSequencePlane)

IMPLEMENT_PLUG_INFO(_preview_texture)
IMPLEMENT_PLUG_INFO(_texture)

IMPLEMENT_PLUG_INFO(_loaded_index)
IMPLEMENT_PLUG_INFO(_index)

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

BEGIN_IMPLEMENT_PLUGS(ComponentDrawStreamingImageSequencePlane)
    
    PLUG_INIT(_texture, "Texture")
		.setInput(true);

    PLUG_INIT(_index, "Index")
		.setInput(true);

    PLUG_INIT(_loaded_index, "Loaded_Index")
		.setOutput(true);
    
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

ComponentDrawStreamingImageSequencePlane::ComponentDrawStreamingImageSequencePlane (void)
    :   _texture            (PLUG_INFO(_texture)),
        _index              (PLUG_INFO(_index), -1),
        _loaded_index       (PLUG_INFO(_loaded_index), -1),
        _material           (PLUG_INFO(_material)),
        _color              (PLUG_INFO(_color), Color(1.0F,1.0F,1.0F,1.0F)),
        _aspect             (1.0F),
        _flip_horz          (PLUG_INFO(_flip_horz), false),
        _flip_vert          (PLUG_INFO(_flip_vert), false),
        _p0                 (PLUG_INFO(_p0), 0.0F),
        _p1                 (PLUG_INFO(_p1), 0.0F),
        _p2                 (PLUG_INFO(_p2), 0.0F),
        _p3                 (PLUG_INFO(_p3), 0.0F),
        _params_pos         (-1),
        _state              (STATE_UNLOADED),
        _load_behaviour     (LOAD_THREADED),
        _unload_behaviour   (UNLOAD_ALWAYS)
{

}
		
ComponentDrawStreamingImageSequencePlane::ComponentDrawStreamingImageSequencePlane (const ComponentDrawStreamingImageSequencePlane &rhs)
    :   ComponentBase       (rhs),
        _texture            (rhs._texture),
        _index              (rhs._index),
        _loaded_index       (rhs._loaded_index),
        _material           (rhs._material),
        _color              (rhs._color),
        _aspect             (rhs._aspect),
        _flip_horz          (rhs._flip_horz),
        _flip_vert          (rhs._flip_vert),
        _p0                 (rhs._p0),
        _p1                 (rhs._p1),
        _p2                 (rhs._p2),
        _p3                 (rhs._p3),
        _params_pos         (rhs._params_pos),
        _state              (STATE_UNLOADED),
        _load_behaviour     (LOAD_THREADED),
        _unload_behaviour   (UNLOAD_ALWAYS)
{

}

ComponentDrawStreamingImageSequencePlane & ComponentDrawStreamingImageSequencePlane::operator = (const ComponentDrawStreamingImageSequencePlane &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        
        _texture = rhs._texture;
        
        _index = rhs._index;
        _loaded_index = rhs._loaded_index;
        
        _material = rhs._material;
        
        _aspect = rhs._aspect;
        _color = rhs._color;
        
        _flip_horz = rhs._flip_horz;
        _flip_vert = rhs._flip_vert;
        
        _p0 = rhs._p0;
        _p1 = rhs._p1;
        _p2 = rhs._p2;
        _p3 = rhs._p3;
        
        _params_pos = rhs._params_pos;
        
        unload();

        _load_behaviour = rhs._load_behaviour;
        _unload_behaviour = rhs._unload_behaviour;
    }
    return (*this);
}
			
ComponentDrawStreamingImageSequencePlane::~ComponentDrawStreamingImageSequencePlane (void)
{
    // Finish loading so we can clean up properly
    while (_state == STATE_LOADING) {
        ThreadMainTaskQueue::runQueue();
        ThreadTaskQueue::runQueue();
    }

    unload();
}

//==============================================================================
//==============================================================================

void ComponentDrawStreamingImageSequencePlane::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentDrawStreamingImageSequencePlane::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
    
    if (archive->isA(ArchivePropertyReaderWriter::kind()))
        *archive << ARCHIVE_DATA_ACCESSORS("Texture", ComponentDrawStreamingImageSequencePlane::getTexture, ComponentDrawStreamingImageSequencePlane::setTextureProp, DATA_PERSISTENT | DATA_SETTABLE);
	else
        *archive << ARCHIVE_DATA_ACCESSORS("Texture", ComponentDrawStreamingImageSequencePlane::getTexture, ComponentDrawStreamingImageSequencePlane::setTexture, DATA_PERSISTENT | DATA_SETTABLE);
    
    if (archive->getVersion() >= 1376) {
        *archive << ARCHIVE_DATA(_load_behaviour, DATA_PERSISTENT | DATA_SETTABLE)
            .addEnum("Normal Load")
            .addEnum("Threaded Load");
        *archive << ARCHIVE_DATA(_unload_behaviour, DATA_PERSISTENT | DATA_SETTABLE)
            .addEnum("Never Unload")
            .addEnum("Always Unload");
    }

	*archive << ARCHIVE_PLUG(_index, DATA_PERSISTENT | DATA_SETTABLE);

    *archive << ARCHIVE_DATA_ACCESSORS("Material", ComponentDrawStreamingImageSequencePlane::getMaterial, ComponentDrawStreamingImageSequencePlane::setMaterial, DATA_PERSISTENT | DATA_SETTABLE);
    
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

void ComponentDrawStreamingImageSequencePlane::archive_read_done()
{
    ComponentBase::archive_read_done();
}

void ComponentDrawStreamingImageSequencePlane::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	
    if (archive->isA(ArchivePropertyReaderWriter::kind()))
        *archive << ARCHIVE_DATA_ACCESSORS("Texture", ComponentDrawStreamingImageSequencePlane::getTexture, ComponentDrawStreamingImageSequencePlane::setTextureProp, DATA_PERSISTENT | DATA_SETTABLE);
	else
        *archive << ARCHIVE_DATA_ACCESSORS("Texture", ComponentDrawStreamingImageSequencePlane::getTexture, ComponentDrawStreamingImageSequencePlane::setTexture, DATA_PERSISTENT | DATA_SETTABLE);

    *archive << ARCHIVE_DATA(_load_behaviour, DATA_PERSISTENT | DATA_SETTABLE)
        .addEnum("Normal Load")
        .addEnum("Threaded Load");
    *archive << ARCHIVE_DATA(_unload_behaviour, DATA_PERSISTENT | DATA_SETTABLE)
        .addEnum("Never Unload")
        .addEnum("Always Unload");

	*archive << ARCHIVE_PLUG(_index, DATA_PERSISTENT | DATA_SETTABLE);

    *archive << ARCHIVE_DATA_ACCESSORS("Material", ComponentDrawStreamingImageSequencePlane::getMaterial, ComponentDrawStreamingImageSequencePlane::setMaterial, DATA_PERSISTENT | DATA_SETTABLE);

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

void ComponentDrawStreamingImageSequencePlane::beginLoad (void)
{
    // Make sure image isn't loaded yet
    if (_state == STATE_LOADING)
        return;
    
#ifndef DT3_EDITOR
    if (_load_behaviour == LOAD_THREADED) {

        retain();   // Retain this object so it doesn't disappear while thread is running

        _state = STATE_LOADING;

        // Load file in task thread
        ThreadTaskQueue::removeTask(_pending_task);
        _pending_task = ThreadTaskQueue::addTask(0, makeLatentCall(this, &ComponentDrawStreamingImageSequencePlane::load, FilePath(fillInPath(_index, _texture)), _index.asRef() ));
    
    } else {
#endif

        // All gets done immediately
        std::shared_ptr<TextureResource> tex = makeSmartPtr(TextureResource::create());
        if (tex->import(FilePath(fillInPath(_index, _texture)),"") == DT3_ERR_NONE && tex->load() == DT3_ERR_NONE) {

            _cache_texture = tex;
            _loaded_index = _index;
            _state = STATE_LOADED;
        } else {
            _state = STATE_ERROR;
        }
        
#ifndef DT3_EDITOR
    }
#endif

}

void ComponentDrawStreamingImageSequencePlane::load (FilePath path, DTint loaded_index)
{

    // All gets done immediately
    std::shared_ptr<TextureResource> tex = makeSmartPtr(TextureResource::create());
    if (tex->import(path,"") == DT3_ERR_NONE && tex->load() == DT3_ERR_NONE) {
        
        _pending_texture = tex;
        
    } else {
        _state = STATE_ERROR;
    }
    
    ThreadMainTaskQueue::addTask(0, makeLatentCall(this, &ComponentDrawStreamingImageSequencePlane::loadDone, tex, loaded_index));
}

void ComponentDrawStreamingImageSequencePlane::loadDone (std::shared_ptr<TextureResource> tex, DTint loaded_index)
{
    if (_pending_texture.isValid()) {
        // This is to fix a race condition that makes some textures not update properly
        _cache_texture = _pending_texture;
        _loaded_index = loaded_index;

        _state = STATE_LOADED;
    }
    release();
}

void ComponentDrawStreamingImageSequencePlane::unload (void)
{
    if (_state == STATE_LOADED) {
        _loaded_index = -1;
        _state = STATE_UNLOADED;
        
        _pending_texture = std::shared_ptr<TextureResource>();
        _cache_texture = std::shared_ptr<TextureResource>();
    }
}

//==============================================================================
//==============================================================================

String ComponentDrawStreamingImageSequencePlane::fillInPath(DTint index, const String &path)
{
    // Replaces a sequence of "#" characters with an integer index padded with zeros
    
    DTsize first = path.findFirstOf("#");
    DTsize last = path.findLastOf("#");
    
    if (first == String::NPOS)
        return path;
    
    DTsize len = last - first + 1;
    
    String index_string = castToString(index);
    
    // Pad string to length
    while (index_string.size() < len) {
        index_string = "0" + index_string;
    }
    
    String out = path;
    
    DTsize i,j;
    for (i = first, j = 0; i <= last; ++i, ++j) {
        out[i] = index_string[j];
    }
    
    return out;
}

//==============================================================================
//==============================================================================

const String& ComponentDrawStreamingImageSequencePlane::getTexture (void) const
{
    return _texture.asRef();
}

void ComponentDrawStreamingImageSequencePlane::setTexture (const String &texture)
{
    unload();
    _texture = texture;
    _state = STATE_UNLOADED;
}

void ComponentDrawStreamingImageSequencePlane::setTextureProp (const String &texture)
{
    unload();
    _texture = texture;
    _state = STATE_UNLOADED;

    // Okay, this is a stupid hack for the editor. Just load in the image to get its
    // aspect ratio.
    
    // All gets done immediately
    std::shared_ptr<TextureResource> tex = makeSmartPtr(TextureResource::create());
    if (tex->import(FilePath(fillInPath(_index, _texture)),"") == DT3_ERR_NONE && tex->load() == DT3_ERR_NONE) {

        setAspect(tex->getWidth()/tex->getHeight());
    }

}

//==============================================================================
//==============================================================================

void ComponentDrawStreamingImageSequencePlane::draw (CameraObject* camera)
{
    if (_material->isNull()) {
        unload();
        return;
    }
        
    if (getColor().getA() <= 0) {
        unload();
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
            if (_unload_behaviour == UNLOAD_ALWAYS)    unload();
        }
        
        return;
    }
    
    //
    // Make sure we are loading or are loaded
    //
    
    // Load new frame if needed
    if (_index != _loaded_index) {
        beginLoad();
    }
    
    // Get full image loading
    if (_params_pos >= 0)
        (*_material)->getShader()->setParameterValue(_params_pos,0, _p0,_p1,_p2,_p3);
    
    // Draw the full image
    if (_cache_texture.isValid()) {
    
        (*_material)->setCurrentUnit(0);
        (*_material)->setTexture(_cache_texture);

        DrawBatcherQuads b;
        b.batchBegin(_material->get(), placeable->getTransform(), DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);

        Color c(_color);
        
        b.vertex(Vector3(-width,-height,0.0F), Texcoord2(tc_s_min,tc_t_min), c);
        b.vertex(Vector3(+width,-height,0.0F), Texcoord2(tc_s_max,tc_t_min), c);
        b.vertex(Vector3(+width,+height,0.0F), Texcoord2(tc_s_max,tc_t_max), c);
        b.vertex(Vector3(-width,+height,0.0F), Texcoord2(tc_s_min,tc_t_max), c);
        
        b.batchEnd();
    }
    
    
}

//==============================================================================
//==============================================================================

void ComponentDrawStreamingImageSequencePlane::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    World *w = getOwner()->getWorld();

    w->registerForDraw(getOwner(), makeCallback(this, &type::draw));
}

void ComponentDrawStreamingImageSequencePlane::removeFromOwner (void)
{
    World *w = getOwner()->getWorld();

    w->unregisterForDraw(getOwner(), makeCallback(this, &type::draw));

    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

} // DT3

