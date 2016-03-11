//==============================================================================
///	
///	File: ComponentDrawStretchImagePlane.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentDrawStretchImagePlane.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "MaterialResource.hpp"
#include "World.hpp"
#include "PlaceableObject.hpp"
#include "DrawBatcherQuads.hpp"
#include "ArchivePropertyReaderWriter.hpp"
#include "DrawUtils.hpp"
#include "DrawBatcherQuads.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentDrawStretchImagePlane,"Drawing","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentDrawStretchImagePlane)

IMPLEMENT_PLUG_INFO(_material)
IMPLEMENT_PLUG_INFO(_color)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentDrawStretchImagePlane)
        
    PLUG_INIT(_material, "Material")
		.setInput(true);
        
    PLUG_INIT(_color, "Color")
		.setInput(true);
        
END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentDrawStretchImagePlane::ComponentDrawStretchImagePlane (void)
    :   _material           (PLUG_INFO(_material)),
        _color              (PLUG_INFO(_color), Color(1.0F,1.0F,1.0F,1.0F)),
        _aspect             (1.0F),
        _corner_width       (0.05F),
        _corner_height      (0.05F)

{  

}
		
ComponentDrawStretchImagePlane::ComponentDrawStretchImagePlane (const ComponentDrawStretchImagePlane &rhs)
    :   ComponentBase       (rhs),
        _material           (rhs._material),
        _color              (rhs._color),
        _aspect             (rhs._aspect),
        _corner_width       (rhs._corner_width),
        _corner_height      (rhs._corner_height)

{   

}

ComponentDrawStretchImagePlane & ComponentDrawStretchImagePlane::operator = (const ComponentDrawStretchImagePlane &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        
        _material = rhs._material;
        _aspect = rhs._aspect;
        _color = rhs._color;
                
        _corner_width = rhs._corner_width;
        _corner_height = rhs._corner_height;
    }
    return (*this);
}
			
ComponentDrawStretchImagePlane::~ComponentDrawStretchImagePlane (void)
{

}

//==============================================================================
//==============================================================================

void ComponentDrawStretchImagePlane::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentDrawStretchImagePlane::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
        		
    if (archive->isA(ArchivePropertyReaderWriter::kind()))
        *archive << ARCHIVE_DATA_ACCESSORS("Material", ComponentDrawStretchImagePlane::getMaterial, ComponentDrawStretchImagePlane::setMaterialProp, DATA_PERSISTENT | DATA_SETTABLE);
	else
        *archive << ARCHIVE_DATA_ACCESSORS("Material", ComponentDrawStretchImagePlane::getMaterial, ComponentDrawStretchImagePlane::setMaterial, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_PLUG(_color, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_aspect, DATA_PERSISTENT | DATA_SETTABLE);
    
	*archive << ARCHIVE_DATA(_corner_width, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_corner_height, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

void ComponentDrawStretchImagePlane::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	
    if (archive->isA(ArchivePropertyReaderWriter::kind()))
        *archive << ARCHIVE_DATA_ACCESSORS("Material", ComponentDrawStretchImagePlane::getMaterial, ComponentDrawStretchImagePlane::setMaterialProp, DATA_PERSISTENT | DATA_SETTABLE);
	else
        *archive << ARCHIVE_DATA_ACCESSORS("Material", ComponentDrawStretchImagePlane::getMaterial, ComponentDrawStretchImagePlane::setMaterial, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_PLUG(_color, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_aspect, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA(_corner_width, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_corner_height, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

std::shared_ptr<MaterialResource> ComponentDrawStretchImagePlane::getMaterial (void) const
{
    return _material;
}

void ComponentDrawStretchImagePlane::setMaterial (std::shared_ptr<MaterialResource> material)
{
    _material = material;
}

void ComponentDrawStretchImagePlane::setMaterialProp (std::shared_ptr<MaterialResource> material)
{
    _material = material;
    
#ifdef DT3_EDITOR

    //
    // Try to automatically set the aspect ratio
    //

    if (_material->isValid()) {
        
        // Take a stab at the aspect ratio
        (*_material)->setCurrentUnit(0);
        
        Vector3 scale = (*_material)->getScale();
        if (scale.y > 0.0F) 
            setAspect(scale.x/scale.y);
    }
#endif
}

//==============================================================================
//==============================================================================

void ComponentDrawStretchImagePlane::draw (CameraObject* camera)
{
    if (_material->isNull())
        return;
        
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
        
    DrawBatcherQuads b;
    
    // Draw background    
    DrawUtils::drawQuadStretchCenter (
        b, _material->get(), _color,
        placeable->getTransform(), 
        -width, -height, 
        -width*2.0F, height*2.0F, 
        _corner_width, _corner_height, 
        false);

    
}

//==============================================================================
//==============================================================================

void ComponentDrawStretchImagePlane::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    World *w = getOwner()->getWorld();

    w->registerForDraw(getOwner(), makeCallback(this, &type::draw));
}

void ComponentDrawStretchImagePlane::removeFromOwner (void)
{
    World *w = getOwner()->getWorld();

    w->unregisterForDraw(getOwner(), makeCallback(this, &type::draw));

    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

} // DT3

