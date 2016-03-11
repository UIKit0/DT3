//==============================================================================
///	
///	File: ComponentDrawFlare.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentDrawFlare.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "GeometryGroupResource.hpp"
#include "GeometryResource.hpp"
#include "MaterialResource.hpp"
#include "World.hpp"
#include "System.hpp"
#include "DrawBatcherQuads.hpp"
#include "ConsoleStream.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentDrawFlare,"Drawing","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentDrawFlare)

IMPLEMENT_PLUG_INFO(_alpha)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentDrawFlare)

	PLUG_INIT(_alpha,"Alpha")
		.setInput(true);
        
END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentDrawFlare::ComponentDrawFlare (void)
	:	_alpha			(PLUG_INFO(_alpha), 1.0F)
{
	for (DTuint i = 0; i < NUM_FLARES; ++i) {
		_size[i] = 0.1F;
		_pos[i] = i / (DTfloat) NUM_FLARES;
	}
}
		
ComponentDrawFlare::ComponentDrawFlare (const ComponentDrawFlare &rhs)
    :   ComponentBase       (rhs),
	    _alpha				(rhs._alpha)
{
	for (DTuint i = 0; i < NUM_FLARES; ++i) {
		_mat[i] = rhs._mat[i];
		_size[i] = rhs._size[i];
		_pos[i] = rhs._pos[i];
	}
}

ComponentDrawFlare & ComponentDrawFlare::operator = (const ComponentDrawFlare &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        
		_alpha = rhs._alpha;
			
		for (DTuint i = 0; i < NUM_FLARES; ++i) {
            _mat[i] = rhs._mat[i];
			_size[i] = rhs._size[i];
			_pos[i] = rhs._pos[i];
		}
    }
    return (*this);
}
			
ComponentDrawFlare::~ComponentDrawFlare (void)
{

}

//==============================================================================
//==============================================================================

void ComponentDrawFlare::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentDrawFlare::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
        		
	*archive << ARCHIVE_PLUG(_alpha, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA_ACCESSORS("Material0", ComponentDrawFlare::getMaterial0, ComponentDrawFlare::setMaterial0, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Size0",_size[0], DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Pos0",_pos[0], DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA_ACCESSORS("Material1", ComponentDrawFlare::getMaterial1, ComponentDrawFlare::setMaterial1, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Size1",_size[1], DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Pos1",_pos[1], DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA_ACCESSORS("Material2", ComponentDrawFlare::getMaterial2, ComponentDrawFlare::setMaterial2, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Size2",_size[2], DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Pos2",_pos[2], DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA_ACCESSORS("Material3", ComponentDrawFlare::getMaterial3, ComponentDrawFlare::setMaterial3, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Size3",_size[3], DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Pos3",_pos[3], DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA_ACCESSORS("Material4", ComponentDrawFlare::getMaterial4, ComponentDrawFlare::setMaterial4, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Size4",_size[4], DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Pos4",_pos[4], DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA_ACCESSORS("Material5", ComponentDrawFlare::getMaterial5, ComponentDrawFlare::setMaterial5, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Size5",_size[5], DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Pos5",_pos[5], DATA_PERSISTENT | DATA_SETTABLE);
    
    archive->pop_domain ();
}

void ComponentDrawFlare::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	
	*archive << ARCHIVE_PLUG(_alpha, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA_ACCESSORS("Material0", ComponentDrawFlare::getMaterial0, ComponentDrawFlare::setMaterial0, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Size0",_size[0], DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Pos0",_pos[0], DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA_ACCESSORS("Material1", ComponentDrawFlare::getMaterial1, ComponentDrawFlare::setMaterial1, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Size1",_size[1], DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Pos1",_pos[1], DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA_ACCESSORS("Material2", ComponentDrawFlare::getMaterial2, ComponentDrawFlare::setMaterial2, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Size2",_size[2], DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Pos2",_pos[2], DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA_ACCESSORS("Material3", ComponentDrawFlare::getMaterial3, ComponentDrawFlare::setMaterial3, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Size3",_size[3], DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Pos3",_pos[3], DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA_ACCESSORS("Material4", ComponentDrawFlare::getMaterial4, ComponentDrawFlare::setMaterial4, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Size4",_size[4], DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Pos4",_pos[4], DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA_ACCESSORS("Material5", ComponentDrawFlare::getMaterial5, ComponentDrawFlare::setMaterial5, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Size5",_size[5], DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_NAMED("Pos5",_pos[5], DATA_PERSISTENT | DATA_SETTABLE);	

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentDrawFlare::draw (CameraObject* camera)
{
    PlaceableObject *placeable = checkedCast<PlaceableObject*>(getOwner());
    if (!placeable)
        return;
        
	for (DTuint i = 0; i < NUM_FLARES; ++i) {
		if (_mat[i].isNull())
			continue;
	
		Color c = _mat[i]->getColor();
		c.setAFloat(_alpha);
		_mat[i]->setColor(c);
    }
    
	Vector3 projected_point = camera->projectPoint (placeable->getTranslation());
    if (projected_point.z > 1.0F)
        return;
        
	Vector3 flare_vec = (Vector3(0.0F, 0.0F, 0.0F) - projected_point) * 2.0F;
    
	DTfloat aspect = System::getRenderer()->getViewportAspect();
    
	DrawBatcherQuads b;
	
	for (DTuint i = 0; i < NUM_FLARES; ++i) {
		if (_mat[i].isNull())
			continue;
		
		DTfloat size = _size[i];
		
		Matrix4 transform = Matrix4::identity();
        transform.setTranslation(projected_point + flare_vec * _pos[i]);	// TODO: Why is this backwards?

		b.batchBegin (_mat[i].get(), Matrix4::identity(), DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);
		b.vertex ( transform * Vector3(-size,-size*aspect,0.0F), Texcoord2(0.0F,0.0F), Color(_alpha,_alpha,_alpha,_alpha) );
		b.vertex ( transform * Vector3(size,-size*aspect,0.0F), Texcoord2(1.0F,0.0F), Color(_alpha,_alpha,_alpha,_alpha) );
		b.vertex ( transform * Vector3(size,size*aspect,0.0F), Texcoord2(1.0F,1.0F), Color(_alpha,_alpha,_alpha,_alpha) );
		b.vertex ( transform * Vector3(-size,size*aspect,0.0F), Texcoord2(0.0F,1.0F), Color(_alpha,_alpha,_alpha,_alpha) );
		b.batchEnd();
	}
	
	b.flush();
    
}

//==============================================================================
//==============================================================================

void ComponentDrawFlare::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    World *w = getOwner()->getWorld();

    w->registerForDraw(getOwner(), makeCallback(this, &type::draw));
}

void ComponentDrawFlare::removeFromOwner (void)
{
    World *w = getOwner()->getWorld();

    w->unregisterForDraw(getOwner(), makeCallback(this, &type::draw));

    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

} // DT3

