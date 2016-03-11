//==============================================================================
///	
///	File: ComponentGUIButton.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentGUIButton.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "World.hpp"
#include "System.hpp"
#include "DeviceGraphics.hpp"
#include "DeviceAudio.hpp"
#include "GUIObject.hpp"
#include "GUIController.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentGUIButton,"GUIBehaviour","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentGUIButton)

IMPLEMENT_EVENT_INFO(_clicked)
IMPLEMENT_PLUG_INFO(_sound)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentGUIButton)

    PLUG_INIT(_sound, "Sound")
		.setInput(true);

	EVENT_INIT(_clicked,"Clicked")
        .setOutput(true);

END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentGUIButton::ComponentGUIButton (void)
    :   _sound                      (PLUG_INFO(_sound)),
        _clicked                    (EVENT_INFO(_clicked))
{

}
		
ComponentGUIButton::ComponentGUIButton (const ComponentGUIButton &rhs)
    :   ComponentBase               (rhs),
        _button_pressed_latent_call (rhs._button_pressed_latent_call),
        _sound                      (rhs._sound),
        _clicked                    (EVENT_INFO(_clicked))
{

}

ComponentGUIButton & ComponentGUIButton::operator = (const ComponentGUIButton &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        
        _button_pressed_latent_call = rhs._button_pressed_latent_call;
        _clicked = rhs._clicked;
        _sound = rhs._sound;
    }
    return (*this);
}
			
ComponentGUIButton::~ComponentGUIButton (void)
{

}

//==============================================================================
//==============================================================================

void ComponentGUIButton::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentGUIButton::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
        	
    if (archive->getVersion() >= 108)
        *archive << ARCHIVE_PLUG(_sound, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

void ComponentGUIButton::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	
	*archive << ARCHIVE_PLUG(_sound, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentGUIButton::addToOwner (ObjectBase *owner)
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

void ComponentGUIButton::removeFromOwner (void)
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

void ComponentGUIButton::touchesBegan (GUITouchEvent *event)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;

    gui->setState(GUIObject::STATE_FOCUSED);
}

void ComponentGUIButton::touchesMoved (GUITouchEvent *event)
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
        gui->setState(GUIObject::STATE_FOCUSED);
    } else {
        gui->setState(GUIObject::STATE_NORMAL);
    }


}

void ComponentGUIButton::touchesEnded (GUITouchEvent *event)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;
        
    if (gui->getState() == GUIObject::STATE_FOCUSED) {
    
        if (_sound->isValid())
            System::getAudioRenderer()->playQuick(_sound->get(), getOwner()->getWorld());
        
        gui->setState(GUIObject::STATE_NORMAL);
     
        _clicked.send(gui);    // GUIObject is the originator of the event
        
        // Call callback too
        if (_button_pressed_latent_call.isValid()) {
            _button_pressed_latent_call->fire();
        }

    }
}

void ComponentGUIButton::touchesCancelled (GUITouchEvent *event)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;

    gui->setState(GUIObject::STATE_NORMAL);
}

//==============================================================================
//==============================================================================

} // DT3

