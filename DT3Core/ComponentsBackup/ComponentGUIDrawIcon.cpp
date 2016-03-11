//==============================================================================
///	
///	File: ComponentGUIDrawIcon.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentGUIDrawIcon.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "MaterialResource.hpp"
#include "World.hpp"
#include "GUIObject.hpp"
#include "DrawBatcherQuads.hpp"
#include "ConsoleStream.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentGUIDrawIcon,"GUI","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentGUIDrawIcon)

IMPLEMENT_PLUG_INFO(_material)
IMPLEMENT_PLUG_INFO(_pressed_material)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentGUIDrawIcon)
        
    PLUG_INIT(_material, "Material")
		.setInput(true);
        
    PLUG_INIT(_pressed_material, "Pressed_Material")
		.setInput(true);

END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentGUIDrawIcon::ComponentGUIDrawIcon (void)
    :   _material           (PLUG_INFO(_material)),
        _pressed_material   (PLUG_INFO(_pressed_material))
{

}
		
ComponentGUIDrawIcon::ComponentGUIDrawIcon (const ComponentGUIDrawIcon &rhs)
    :   ComponentBase       (rhs),
        _material           (rhs._material),
        _pressed_material   (rhs._pressed_material)
{

}

ComponentGUIDrawIcon & ComponentGUIDrawIcon::operator = (const ComponentGUIDrawIcon &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        
        _material = rhs._material;
        _pressed_material = rhs._pressed_material;
    }
    return (*this);
}
			
ComponentGUIDrawIcon::~ComponentGUIDrawIcon (void)
{

}

//==============================================================================
//==============================================================================

void ComponentGUIDrawIcon::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawIcon::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
        		
	*archive << ARCHIVE_PLUG(_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_pressed_material, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

void ComponentGUIDrawIcon::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	
	*archive << ARCHIVE_PLUG(_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_pressed_material, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawIcon::draw (CameraObject* camera, const Color &parent_color)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;
    
    MaterialResource *material = _material->get();
    MaterialResource *pressed_material = _pressed_material->get();

    if (!material)
        return;
       
    if (gui->getColor().getA() * parent_color.getA() <= 0.0F)
        return;
    
    DrawBatcherQuads b;
    
    // Get Alternate materials
    Color c = gui->getColor() * parent_color;
    MaterialResource *m = material;

    if (_pressed_material->isValid()) {
        if (gui->getState() == GUIObject::STATE_FOCUSED) 
            m = pressed_material;
    } else {
        if (gui->getState() == GUIObject::STATE_FOCUSED) 
            c = gui->getColor() * 0.5F;
    }

    b.batchBegin(m, gui->getDrawTransform(), DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);
    
    Rectangle rect = gui->getRectangle();

    b.vertex(Vector3(rect.getMinusX(),rect.getMinusY(),0.0F), Texcoord2(0.0F,0.0F), c);
    b.vertex(Vector3(rect.getPlusX(),rect.getMinusY(),0.0F), Texcoord2(1.0F,0.0F), c);
    b.vertex(Vector3(rect.getPlusX(),rect.getPlusY(),0.0F), Texcoord2(1.0F,1.0F), c);
    b.vertex(Vector3(rect.getMinusX(),rect.getPlusY(),0.0F), Texcoord2(0.0F,1.0F), c);
    
    b.batchEnd();
        
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawIcon::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    GUIObject *gui = checkedCast<GUIObject*>(owner);
    if (gui) {
        gui->getDrawGUICallbacks().add(makeCallback(this, &type::draw));
    }
}

void ComponentGUIDrawIcon::removeFromOwner (void)
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

