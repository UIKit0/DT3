//==============================================================================
///	
///	File: ComponentGUIEatEvent.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentGUIEatEvent.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "GeometryGroupResource.hpp"
#include "World.hpp"
#include "System.hpp"
#include "DeviceGraphics.hpp"
#include "GUIObject.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION(ComponentGUIEatEvent)
IMPLEMENT_PLUG_NODE(ComponentGUIEatEvent)

IMPLEMENT_EVENT_INFO(_clicked)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentGUIEatEvent)

END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentGUIEatEvent::ComponentGUIEatEvent (void)
{  

}
		
ComponentGUIEatEvent::ComponentGUIEatEvent (const ComponentGUIEatEvent &rhs)
    :   ComponentBase       (rhs)
{   

}

ComponentGUIEatEvent & ComponentGUIEatEvent::operator = (const ComponentGUIEatEvent &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        
    }
    return (*this);
}
			
ComponentGUIEatEvent::~ComponentGUIEatEvent (void)
{

}

//==============================================================================
//==============================================================================

void ComponentGUIEatEvent::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentGUIEatEvent::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
        		
    archive->pop_domain ();
}

void ComponentGUIEatEvent::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	
    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentGUIEatEvent::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
}

void ComponentGUIEatEvent::removeFromOwner (void)
{
    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

} // DT3

