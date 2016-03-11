//==============================================================================
///	
///	File: ComponentGUIMoveable.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentGUIMoveable.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "GeometryGroupResource.hpp"
#include "World.hpp"
#include "System.hpp"
#include "DeviceGraphics.hpp"
#include "ConsoleStream.hpp"
#include "GUIObject.hpp"
#include "GUITouchEvent.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentGUIMoveable,"GUIBehaviour","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentGUIMoveable)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentGUIMoveable)
END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentGUIMoveable::ComponentGUIMoveable (void)
{  

}
		
ComponentGUIMoveable::ComponentGUIMoveable (const ComponentGUIMoveable &rhs)
    :   ComponentBase       (rhs)
{

}

ComponentGUIMoveable & ComponentGUIMoveable::operator = (const ComponentGUIMoveable &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
    }
    return (*this);
}
			
ComponentGUIMoveable::~ComponentGUIMoveable (void)
{

}

//==============================================================================
//==============================================================================

void ComponentGUIMoveable::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentGUIMoveable::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
        		
    archive->pop_domain ();
}

void ComponentGUIMoveable::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	
    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentGUIMoveable::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    GUIObject *gui = checkedCast<GUIObject*>(owner);
    if (gui) {
        gui->getTouchesBeganCallbacks().add(makeCallback(this, &type::touchesBegan));
        gui->getTouchesMovedCallbacks().add(makeCallback(this, &type::touchesMoved));
        gui->getTouchesEndedCallbacks().add(makeCallback(this, &type::touchesEnded));
        gui->getTouchesCancelledCallbacks().add(makeCallback(this, &type::touchesCancelled));
    }
}

void ComponentGUIMoveable::removeFromOwner (void)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (gui) {
        gui->getTouchesBeganCallbacks().remove(makeCallback(this, &type::touchesBegan));
        gui->getTouchesMovedCallbacks().remove(makeCallback(this, &type::touchesMoved));
        gui->getTouchesEndedCallbacks().remove(makeCallback(this, &type::touchesEnded));
        gui->getTouchesCancelledCallbacks().remove(makeCallback(this, &type::touchesCancelled));
    }

    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

void ComponentGUIMoveable::touchesBegan (GUITouchEvent *event)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;

    gui->setState(GUIObject::STATE_FOCUSED);
}

void ComponentGUIMoveable::touchesMoved (GUITouchEvent *event)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;
        
    Vector2 pos_previous = gui->positionToObjectCoord(event->getPreviousPosition());
    Vector2 pos = gui->positionToObjectCoord(event->getPosition());
                    
    Vector2 pan = pos - pos_previous;
    gui->setTranslationLocal( gui->getTranslationLocal() + Vector3(pan) );  
}

void ComponentGUIMoveable::touchesEnded (GUITouchEvent *event)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;
        
    gui->setState(GUIObject::STATE_NORMAL);
}

void ComponentGUIMoveable::touchesCancelled (GUITouchEvent *event)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;

    gui->setState(GUIObject::STATE_NORMAL);
}

//==============================================================================
//==============================================================================

} // DT3

