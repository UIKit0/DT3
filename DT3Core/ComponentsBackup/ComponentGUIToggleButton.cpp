//==============================================================================
///	
///	File: ComponentGUIToggleButton.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentGUIToggleButton.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "World.hpp"
#include "System.hpp"
#include "DeviceGraphics.hpp"
#include "ConsoleStream.hpp"
#include "DeviceAudio.hpp"
#include "GUIObject.hpp"
#include "GUIController.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentGUIToggleButton,"GUIBehaviour","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentGUIToggleButton)

IMPLEMENT_EVENT_INFO(_clicked_on)
IMPLEMENT_EVENT_INFO(_clicked_off)
IMPLEMENT_EVENT_INFO(_toggled)
IMPLEMENT_EVENT_INFO(_force_click_on)
IMPLEMENT_EVENT_INFO(_force_click_off)

IMPLEMENT_PLUG_INFO(_is_on)
IMPLEMENT_PLUG_INFO(_sound_on)
IMPLEMENT_PLUG_INFO(_sound_off)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentGUIToggleButton)

    PLUG_INIT(_sound_on, "Sound_On")
		.setInput(true);

    PLUG_INIT(_sound_off, "Sound_Off")
		.setInput(true);

    PLUG_INIT(_is_on, "Is_On")
		.setOutput(true);

	EVENT_INIT(_clicked_on,"Clicked_On")
        .setOutput(true);

	EVENT_INIT(_clicked_off,"Clicked_Off")
        .setOutput(true);

	EVENT_INIT(_toggled,"Toggled")
        .setOutput(true);

	EVENT_INIT(_force_click_on,"Force_Click_On")
        .setInput(true)
        .setEvent(EventBindCreator(&ComponentGUIToggleButton::forceClickOn));

	EVENT_INIT(_force_click_off,"Force_Click_Off")
        .setInput(true)
        .setEvent(EventBindCreator(&ComponentGUIToggleButton::forceClickOff));

END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentGUIToggleButton::ComponentGUIToggleButton (void)
    :   _sound_on           (PLUG_INFO(_sound_on)),
        _sound_off          (PLUG_INFO(_sound_off)),
        _is_on              (PLUG_INFO(_is_on), false),
        _clicked_on         (EVENT_INFO(_clicked_on)),
        _clicked_off        (EVENT_INFO(_clicked_off)),
        _toggled            (EVENT_INFO(_toggled)),
        _force_click_on     (EVENT_INFO(_force_click_on)),
        _force_click_off    (EVENT_INFO(_force_click_off))
{

}
		
ComponentGUIToggleButton::ComponentGUIToggleButton (const ComponentGUIToggleButton &rhs)
    :   ComponentBase       (rhs),
        _sound_on           (rhs._sound_on),
        _sound_off          (rhs._sound_off),
        _is_on              (rhs._is_on),
        _clicked_on         (EVENT_INFO(_clicked_on)),
        _clicked_off        (EVENT_INFO(_clicked_off)),
        _toggled            (EVENT_INFO(_toggled)),
        _force_click_on     (EVENT_INFO(_force_click_on)),
        _force_click_off    (EVENT_INFO(_force_click_off))
{

}

ComponentGUIToggleButton & ComponentGUIToggleButton::operator = (const ComponentGUIToggleButton &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        
        _sound_on = rhs._sound_on;
        _sound_off = rhs._sound_off;
        _is_on = rhs._is_on;

        _clicked_on = rhs._clicked_on;
        _clicked_off = rhs._clicked_off;
        _toggled = rhs._toggled;
        _force_click_on = rhs._force_click_on;
        _force_click_off = rhs._force_click_off;
    }
    return (*this);
}
			
ComponentGUIToggleButton::~ComponentGUIToggleButton (void)
{

}

//==============================================================================
//==============================================================================

void ComponentGUIToggleButton::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentGUIToggleButton::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
        		
    if (archive->getVersion() >= 109) {
        *archive << ARCHIVE_PLUG(_sound_on, DATA_PERSISTENT | DATA_SETTABLE);
        *archive << ARCHIVE_PLUG(_sound_off, DATA_PERSISTENT | DATA_SETTABLE);
    }

    archive->pop_domain ();
}

void ComponentGUIToggleButton::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	
    *archive << ARCHIVE_PLUG(_sound_on, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_sound_off, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentGUIToggleButton::addToOwner (ObjectBase *owner)
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

void ComponentGUIToggleButton::removeFromOwner (void)
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

void ComponentGUIToggleButton::forceClickOn (PlugNode *sender)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;

    if (gui->getState() == GUIObject::STATE_NORMAL) {
        gui->setState(GUIObject::STATE_FOCUSED);
        
        _is_on = true;
        _clicked_on.send(gui);      // GUIObject is the originator of the event
        _toggled.send(gui);
    }
}

void ComponentGUIToggleButton::forceClickOff (PlugNode *sender)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;

    if (gui->getState() == GUIObject::STATE_FOCUSED) {
        gui->setState(GUIObject::STATE_NORMAL);
        
        _is_on = false;
        _clicked_off.send(gui);     // GUIObject is the originator of the event
        _toggled.send(gui);
    }
}

//==============================================================================
//==============================================================================

void ComponentGUIToggleButton::touchesBegan (GUITouchEvent *event)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;

}

void ComponentGUIToggleButton::touchesMoved (GUITouchEvent *event)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;

}

void ComponentGUIToggleButton::touchesEnded (GUITouchEvent *event)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;
        
    //
    // Check if still within bounds
    //
    
    // Transform touches into widget coordinates
    Vector2 pos = gui->positionToObjectCoord(event->getPosition());

    if (gui->getRectangle().isTouching(pos)) {        

        if (gui->getState() == GUIObject::STATE_FOCUSED) {
        
            if (_sound_off->isValid())
                System::getAudioRenderer()->playQuick(_sound_off->get(), getOwner()->getWorld());
            gui->setState(GUIObject::STATE_NORMAL);
            _is_on = false;

            _clicked_off.send(gui);     // GUIObject is the originator of the event
            _toggled.send(gui);
            
        } else {
        
            if (_sound_on->isValid())
                System::getAudioRenderer()->playQuick(_sound_on->get(), getOwner()->getWorld());
            gui->setState(GUIObject::STATE_FOCUSED);
            _is_on = true;

            _clicked_on.send(gui);      // GUIObject is the originator of the event
            _toggled.send(gui);
           
        }

    }
        
}

void ComponentGUIToggleButton::touchesCancelled (GUITouchEvent *event)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;

}

//==============================================================================
//==============================================================================

} // DT3

