#ifndef DT3_COMPONENTGUITOGGLEBUTTON
#define DT3_COMPONENTGUITOGGLEBUTTON
//==============================================================================
///	
///	File: ComponentGUIToggleButton.hpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentBase.hpp"
#include "SoundResource.hpp"

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class TouchEvent;
class GUITouchEvent;
class CameraObject;
class WorldNode;

//==============================================================================
/// GUI behaviour for a toggle button.
//==============================================================================

class ComponentGUIToggleButton: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentGUIToggleButton,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                    ComponentGUIToggleButton	(void);	
									ComponentGUIToggleButton	(const ComponentGUIToggleButton &rhs);
        ComponentGUIToggleButton &  operator =                  (const ComponentGUIToggleButton &rhs);	
        virtual                     ~ComponentGUIToggleButton	(void);
    
        virtual void                archive_read			(Archive *archive);
        virtual void                archive_write		(Archive *archive);
		
	public:
		/// Called to initialize the object
		virtual void				initialize			(void);
        
		/// Returns the component type. This defines which slot the component is
        /// put into on the object.
		/// \return Component type
        virtual ComponentType       getComponentType    (void)  {   return COMPONENT_TOUCH;  }

		/// Called when this component is added to the owner. Note that this will
        /// only be called if the owner is added to a world already. If not it 
        /// will be called when it is added to the World.
		/// \param owner Pointer to the owner
		virtual void                addToOwner          (ObjectBase *owner);

		/// Called when this component is removed from its owner.
		virtual void                removeFromOwner     (void);


		/// Callback called when the component is getting a touch begin event
		/// \param event Touch events
        void                        touchesBegan        (GUITouchEvent *event);

		/// Callback called when the component is getting a touch move event
		/// \param event Touch events
        void                        touchesMoved        (GUITouchEvent *event);

		/// Callback called when the component is getting a touch end event
		/// \param event Touch events
        void                        touchesEnded        (GUITouchEvent *event);

		/// Callback called when the component is getting a touch cancelled event
		/// \param event Touch events
        void                        touchesCancelled    (GUITouchEvent *event);


		/// Forces the Toggle button on
		/// \param sender sender of the event
        void                        forceClickOn        (PlugNode *sender);

		/// Forces the Toggle button off
		/// \param sender sender of the event
        void                        forceClickOff       (PlugNode *sender);
        
        /// Defines standard accessors for the sound that is played when clicked on
		DEFINE_ACCESSORS		(getSoundOn, setSoundOn, std::shared_ptr<SoundResource>, _sound_on);

        /// Defines standard accessors for the sound that is played when clicked off
		DEFINE_ACCESSORS		(getSoundOff, setSoundOff, std::shared_ptr<SoundResource>, _sound_off);


    private:
        Plug<std::shared_ptr<SoundResource> >  _sound_on;
        Plug<std::shared_ptr<SoundResource> >  _sound_off;

        Plug<DTboolean>                 _is_on;

        Event                       _clicked_on;
        Event                       _clicked_off;
        Event                       _toggled;

        Event                       _force_click_on;
        Event                       _force_click_off;

};

//==============================================================================
//==============================================================================

} // DT3

#endif
