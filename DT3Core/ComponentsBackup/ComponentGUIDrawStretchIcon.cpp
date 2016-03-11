//==============================================================================
///	
///	File: ComponentGUIDrawStretchIcon.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentGUIDrawStretchIcon.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "MaterialResource.hpp"
#include "World.hpp"
#include "GUIObject.hpp"
#include "DrawBatcherQuads.hpp"
#include "ConsoleStream.hpp"
#include "DrawUtils.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentGUIDrawStretchIcon,"GUI","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentGUIDrawStretchIcon)

IMPLEMENT_PLUG_INFO(_material)
IMPLEMENT_PLUG_INFO(_pressed_material)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentGUIDrawStretchIcon)
        
    PLUG_INIT(_material, "Material")
		.setInput(true);
        
    PLUG_INIT(_pressed_material, "Pressed_Material")
		.setInput(true);

END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentGUIDrawStretchIcon::ComponentGUIDrawStretchIcon (void)
    :   _material           (PLUG_INFO(_material)),
        _pressed_material   (PLUG_INFO(_pressed_material)),
        _corner_width       (0.0F),
        _corner_height      (0.0F)
{  

}
		
ComponentGUIDrawStretchIcon::ComponentGUIDrawStretchIcon (const ComponentGUIDrawStretchIcon &rhs)
    :   ComponentBase       (rhs),
        _material           (rhs._material),
        _pressed_material   (rhs._pressed_material),
        _corner_width       (rhs._corner_width),
        _corner_height      (rhs._corner_height)
{   

}

ComponentGUIDrawStretchIcon & ComponentGUIDrawStretchIcon::operator = (const ComponentGUIDrawStretchIcon &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        
        _material = rhs._material;
        _pressed_material = rhs._pressed_material;

        _corner_width = rhs._corner_width;
        _corner_height = rhs._corner_height;
    }
    return (*this);
}
			
ComponentGUIDrawStretchIcon::~ComponentGUIDrawStretchIcon (void)
{

}

//==============================================================================
//==============================================================================

void ComponentGUIDrawStretchIcon::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawStretchIcon::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
        		
	*archive << ARCHIVE_PLUG(_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_pressed_material, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA(_corner_width, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_corner_height, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

void ComponentGUIDrawStretchIcon::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	
	*archive << ARCHIVE_PLUG(_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_pressed_material, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA(_corner_width, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_corner_height, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawStretchIcon::draw (CameraObject* camera, const Color &parent_color)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;
    
    MaterialResource *material = _material->get();
    MaterialResource *pressed_material = _pressed_material->get();
    DTfloat corner_width = _corner_width;
    DTfloat corner_height = _corner_height;

    if (!material)
        return;
               
    if (gui->getColor().getA() * parent_color.getA() <= 0.0F)
        return;
    
    DrawBatcherQuads b;
    
    // Get Alternate materials
    Color c = gui->getColor() * parent_color;
    MaterialResource *m = material;

    if (pressed_material) {
        if (gui->getState() == GUIObject::STATE_FOCUSED) 
            m = pressed_material;
        
    } else {
        if (gui->getState() == GUIObject::STATE_FOCUSED) 
            c = gui->getColor() * 0.5F;
    }
    
    Rectangle local_rect = gui->getRectangle();
    Matrix4 transform = gui->getDrawTransform();

    // Draw background    
    if (corner_width > 0.0F || corner_height > 0.0F) {
        DrawUtils::drawQuadStretchCenter (
            b, m, c, 
            transform, 
            local_rect.getMinusX(), local_rect.getMinusY(), 
            local_rect.getWidth(), local_rect.getHeight(), 
            corner_width, corner_height, 
            false);
    } else {
        DrawUtils::drawQuad (
            b, m, c, 
            transform, 
            local_rect.getMinusX(), local_rect.getMinusY(), 
            local_rect.getWidth(), local_rect.getHeight(), 
            false);
    }
    
    b.flush();
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawStretchIcon::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    GUIObject *gui = checkedCast<GUIObject*>(owner);
    if (gui) {
        gui->getDrawGUICallbacks().add(makeCallback(this, &type::draw));
    }
}

void ComponentGUIDrawStretchIcon::removeFromOwner (void)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (gui) {
        gui->getDrawGUICallbacks().remove(makeCallback(this, &type::draw));
    }

    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

} // DT3

