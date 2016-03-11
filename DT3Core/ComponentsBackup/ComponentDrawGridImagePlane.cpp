//==============================================================================
///	
///	File: ComponentDrawGridImagePlane.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentDrawGridImagePlane.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "MaterialResource.hpp"
#include "World.hpp"
#include "PlaceableObject.hpp"
#include "DrawBatcher.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentDrawGridImagePlane,"Drawing","EdManipComponentDrawGridImagePlane")
IMPLEMENT_PLUG_NODE(ComponentDrawGridImagePlane)

IMPLEMENT_PLUG_INFO(_material)
IMPLEMENT_PLUG_INFO(_color)
IMPLEMENT_PLUG_INFO(_grid)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentDrawGridImagePlane)
        
    PLUG_INIT(_material, "Material")
		.setInput(true);
        
    PLUG_INIT(_color, "Color")
		.setInput(true);
        
    PLUG_INIT(_grid, "Grid")
		.setInput(true);
        
END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentDrawGridImagePlane::ComponentDrawGridImagePlane (void)
    :   _material           (PLUG_INFO(_material)),
        _color              (PLUG_INFO(_color), Color(1.0F,1.0F,1.0F,1.0F)),
        _grid               (PLUG_INFO(_grid)),
        _aspect             (1.0F)
{

}
		
ComponentDrawGridImagePlane::ComponentDrawGridImagePlane (const ComponentDrawGridImagePlane &rhs)
    :   ComponentBase       (rhs),
        _material           (rhs._material),
        _color              (rhs._color),
        _grid               (rhs._grid),
        _aspect             (rhs._aspect)
{

}

ComponentDrawGridImagePlane & ComponentDrawGridImagePlane::operator = (const ComponentDrawGridImagePlane &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        
        _material = rhs._material;
        _aspect = rhs._aspect;
        _color = rhs._color;
        _grid = rhs._grid;
    }
    return (*this);
}
			
ComponentDrawGridImagePlane::~ComponentDrawGridImagePlane (void)
{

}

//==============================================================================
//==============================================================================

void ComponentDrawGridImagePlane::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentDrawGridImagePlane::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
        		
	*archive << ARCHIVE_PLUG(_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_color, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_aspect, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_grid, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA_ACCESSORS("Num_X", ComponentDrawGridImagePlane::getNumX, ComponentDrawGridImagePlane::setNumX, DATA_SETTABLE);
	*archive << ARCHIVE_DATA_ACCESSORS("Num_Y", ComponentDrawGridImagePlane::getNumY, ComponentDrawGridImagePlane::setNumY, DATA_SETTABLE);

    archive->pop_domain ();
}

void ComponentDrawGridImagePlane::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	
	*archive << ARCHIVE_PLUG(_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_color, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_aspect, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_grid, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA_ACCESSORS("Num_X", ComponentDrawGridImagePlane::getNumX, ComponentDrawGridImagePlane::setNumX, DATA_SETTABLE);
	*archive << ARCHIVE_DATA_ACCESSORS("Num_Y", ComponentDrawGridImagePlane::getNumY, ComponentDrawGridImagePlane::setNumY, DATA_SETTABLE);

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentDrawGridImagePlane::setNumX (const DTuint num_x)
{
    _grid->setNumX(num_x);
}

const DTuint ComponentDrawGridImagePlane::getNumX (void) const
{
    return _grid->getNumX();
}

void ComponentDrawGridImagePlane::setNumY (const DTuint num_y)
{
    _grid->setNumY(num_y);
}

const DTuint ComponentDrawGridImagePlane::getNumY (void) const
{
    return _grid->getNumY();
}

//==============================================================================
//==============================================================================

void ComponentDrawGridImagePlane::draw (CameraObject* camera)
{
    if (_material->isNull())
        return;
        
    if (getColor().getA() <= 0)
        return;
        
    PlaceableObject *placeable = checkedCast<PlaceableObject*>(getOwner());
    if (!placeable)
        return;
        
    DTfloat width, height;
    if (getAspect() > 1.0F) {
        width = 1.0F;
        height = 1.0F / getAspect();
        
    } else if (getAspect() < 1.0F) {
        width = getAspect();
        height = 1.0F;

    } else {
        width = 1.0F;
        height = 1.0F;
    }
    
    DTuint num_x = _grid->getNumX();
    DTuint num_y = _grid->getNumY();
    
    if (num_x <= 0 || num_y <= 0)
        return;

                
    DrawBatcher b;
    
    for (DTuint x = 0; x < (num_x-1); ++x) {
     	b.batchBegin (_material->get(), placeable->getTransform(), DrawBatcher::BATCH_TRI_STRIP, DrawBatcher::FMT_V | DrawBatcher::FMT_T1 | DrawBatcher::FMT_C);

        DTfloat x0 = x / (DTfloat)(num_x-1);
        DTfloat x1 = (x+1) / (DTfloat)(num_x-1);
        
        for (DTuint y = 0; y < num_y; ++y) {
            Vector2 p0 = _grid->getPoint(x,y);
            Vector2 p1 = _grid->getPoint(x+1,y);
            
            p0.x *= width;
            p0.y *= height;
            p1.x *= width;
            p1.y *= height;
            
            DTfloat y0 = y / (DTfloat)(num_y-1);
            
            b.vertex ( Vector3(p1), Texcoord2(x1, y0), getColor() );
            b.vertex ( Vector3(p0), Texcoord2(x0, y0), getColor() );
        }

        b.batchEnd();
        b.flush();
    }
    
}

//==============================================================================
//==============================================================================

void ComponentDrawGridImagePlane::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    World *w = getOwner()->getWorld();

    w->registerForDraw(getOwner(), makeCallback(this, &type::draw));
}

void ComponentDrawGridImagePlane::removeFromOwner (void)
{
    World *w = getOwner()->getWorld();

    w->unregisterForDraw(getOwner(), makeCallback(this, &type::draw));

    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

} // DT3

