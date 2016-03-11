//==============================================================================
///	
///	File: ComponentDrawSky.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentDrawSky.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "GeometryGroupResource.hpp"
#include "GeometryResource.hpp"
#include "MaterialResource.hpp"
#include "World.hpp"
#include "System.hpp"
#include "DrawBatcher.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentDrawSky,"Drawing","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentDrawSky)

IMPLEMENT_PLUG_INFO(_material_front)
IMPLEMENT_PLUG_INFO(_material_back)
IMPLEMENT_PLUG_INFO(_material_left)
IMPLEMENT_PLUG_INFO(_material_right)
IMPLEMENT_PLUG_INFO(_material_up)
IMPLEMENT_PLUG_INFO(_material_down)

IMPLEMENT_PLUG_INFO(_color)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentDrawSky)

	PLUG_INIT(_material_front,"Material_Front")
		.setInput(true);

	PLUG_INIT(_material_back,"Material_Back")
		.setInput(true);
		
	PLUG_INIT(_material_left,"Material_Left")
		.setInput(true);
		
	PLUG_INIT(_material_right,"Material_Right")
		.setInput(true);
		
	PLUG_INIT(_material_up,"Material_Up")
		.setInput(true);
		
	PLUG_INIT(_material_down,"Material_Down")
		.setInput(true);
    
    PLUG_INIT(_color, "Color")
		.setInput(true);

END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentDrawSky::ComponentDrawSky (void)
	:   _center_on_camera   (true),
        _material_front		(PLUG_INFO(_material_front)),
		_material_back		(PLUG_INFO(_material_back)),
		_material_left		(PLUG_INFO(_material_left)),
		_material_right		(PLUG_INFO(_material_right)),
		_material_up		(PLUG_INFO(_material_up)),
		_material_down		(PLUG_INFO(_material_down)),
        _color              (PLUG_INFO(_color), Color(1.0F,1.0F,1.0F,1.0F))
{

}
		
ComponentDrawSky::ComponentDrawSky (const ComponentDrawSky &rhs)
    :   ComponentBase       (rhs),
        _center_on_camera   (rhs._center_on_camera),
		_material_front		(rhs._material_front),
		_material_back		(rhs._material_back),
		_material_left		(rhs._material_left),
		_material_right		(rhs._material_right),
		_material_up		(rhs._material_up),
		_material_down		(rhs._material_down),
        _color              (rhs._color)
{

}

ComponentDrawSky & ComponentDrawSky::operator = (const ComponentDrawSky &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        
        _center_on_camera = rhs._center_on_camera;
        
		_material_front = rhs._material_front;
		_material_back = rhs._material_back;
		_material_left = rhs._material_left;
		_material_right = rhs._material_right;
		_material_up = rhs._material_up;
		_material_down = rhs._material_down;
        
        _color = rhs._color;
    }
    return (*this);
}
			
ComponentDrawSky::~ComponentDrawSky (void)
{

}

//==============================================================================
//==============================================================================

void ComponentDrawSky::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentDrawSky::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
    
    if (archive->getVersion() >= 1377) {
        *archive << ARCHIVE_DATA(_center_on_camera, DATA_PERSISTENT | DATA_SETTABLE);
    }
        		
	*archive << ARCHIVE_PLUG(_material_front, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_material_back, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_material_left, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_material_right, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_material_up, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_material_down, DATA_PERSISTENT | DATA_SETTABLE);

    if (archive->getVersion() >= 1373)
        *archive << ARCHIVE_PLUG(_color, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

void ComponentDrawSky::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	
    *archive << ARCHIVE_DATA(_center_on_camera, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_PLUG(_material_front, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_material_back, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_material_left, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_material_right, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_material_up, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_material_down, DATA_PERSISTENT | DATA_SETTABLE);

    *archive << ARCHIVE_PLUG(_color, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentDrawSky::draw (CameraObject* camera)
{
    PlaceableObject *placeable = checkedCast<PlaceableObject*>(getOwner());
    if (!placeable)
        return;

	DrawBatcher b;
    
    Color c(_color);
    
    Matrix4 transform = placeable->getTransform();
    
    if (_center_on_camera) {
        transform.setTranslation(camera->getTranslation()); // Move to camera
    }
	
	b.batchBegin (_material_front->get(), transform, DrawBatcher::BATCH_TRI_STRIP, DrawBatcher::FMT_V | DrawBatcher::FMT_T1 | DrawBatcher::FMT_C);
	b.vertex ( Vector3(300.0F,300.0F,300.0F), Texcoord2(0.0F,1.0F), c );
	b.vertex ( Vector3(-300.0F,300.0F,300.0F), Texcoord2(1.0F,1.0F), c );
	b.vertex ( Vector3(300.0F,-300.0F,300.0F), Texcoord2(0.0F,0.0F), c );
	b.vertex ( Vector3(-300.0F,-300.0F,300.0F), Texcoord2(1.0F,0.0F), c );
	b.batchEnd();
	b.flush();	
	
	b.batchBegin (_material_back->get(), transform, DrawBatcher::BATCH_TRI_STRIP, DrawBatcher::FMT_V | DrawBatcher::FMT_T1 | DrawBatcher::FMT_C);
	b.vertex ( Vector3(-300.0F,300.0F,-300.0F), Texcoord2(0.0F,1.0F), c );
	b.vertex ( Vector3(300.0F,300.0F,-300.0F), Texcoord2(1.0F,1.0F), c );
	b.vertex ( Vector3(-300.0F,-300.0F,-300.0F), Texcoord2(0.0F,0.0F), c );
	b.vertex ( Vector3(300.0F,-300.0F,-300.0F), Texcoord2(1.0F,0.0F), c );
	b.batchEnd();
	b.flush();
	
	b.batchBegin (_material_left->get(), transform, DrawBatcher::BATCH_TRI_STRIP, DrawBatcher::FMT_V | DrawBatcher::FMT_T1 | DrawBatcher::FMT_C);
	b.vertex ( Vector3(-300.0F,300.0F,300.0F), Texcoord2(0.0F,1.0F), c );
	b.vertex ( Vector3(-300.0F,300.0F,-300.0F), Texcoord2(1.0F,1.0F), c );
	b.vertex ( Vector3(-300.0F,-300.0F,300.0F), Texcoord2(0.0F,0.0F), c );
	b.vertex ( Vector3(-300.0F,-300.0F,-300.0F), Texcoord2(1.0F,0.0F), c );
	b.batchEnd();
	b.flush();
	
	b.batchBegin (_material_right->get(), transform, DrawBatcher::BATCH_TRI_STRIP, DrawBatcher::FMT_V | DrawBatcher::FMT_T1 | DrawBatcher::FMT_C);
	b.vertex ( Vector3(300.0F,300.0F,-300.0F), Texcoord2(0.0F,1.0F), c );
	b.vertex ( Vector3(300.0F,300.0F,300.0F), Texcoord2(1.0F,1.0F), c );
	b.vertex ( Vector3(300.0F,-300.0F,-300.0F), Texcoord2(0.0F,0.0F), c );
	b.vertex ( Vector3(300.0F,-300.0F,300.0F), Texcoord2(1.0F,0.0F), c );
	b.batchEnd();
	b.flush();
	
	b.batchBegin (_material_down->get(), transform, DrawBatcher::BATCH_TRI_STRIP, DrawBatcher::FMT_V | DrawBatcher::FMT_T1 | DrawBatcher::FMT_C);
	b.vertex ( Vector3(300.0F,-300.0F,-300.0F), Texcoord2(0.0F,0.0F), c );
	b.vertex ( Vector3(300.0F,-300.0F,300.0F), Texcoord2(0.0F,1.0F), c );
	b.vertex ( Vector3(-300.0F,-300.0F,-300.0F), Texcoord2(1.0F,0.0F), c );
	b.vertex ( Vector3(-300.0F,-300.0F,300.0F), Texcoord2(1.0F,1.0F), c );
	b.batchEnd();
	b.flush();

	b.batchBegin (_material_up->get(), transform, DrawBatcher::BATCH_TRI_STRIP, DrawBatcher::FMT_V | DrawBatcher::FMT_T1 | DrawBatcher::FMT_C);
	b.vertex ( Vector3(300.0F,300.0F,-300.0F), Texcoord2(0.0F,1.0F), c );
	b.vertex ( Vector3(300.0F,300.0F,300.0F), Texcoord2(0.0F,0.0F), c );
	b.vertex ( Vector3(-300.0F,300.0F,-300.0F), Texcoord2(1.0F,1.0F), c );
	b.vertex ( Vector3(-300.0F,300.0F,300.0F), Texcoord2(1.0F,0.0F), c );
	b.batchEnd();
	b.flush();
}

//==============================================================================
//==============================================================================

void ComponentDrawSky::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    World *w = getOwner()->getWorld();

    w->registerForDraw(getOwner(), makeCallback(this, &type::draw));
}

void ComponentDrawSky::removeFromOwner (void)
{
    World *w = getOwner()->getWorld();

    w->unregisterForDraw(getOwner(), makeCallback(this, &type::draw));

    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

} // DT3

