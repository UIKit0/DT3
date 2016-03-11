#ifndef DT3_COMPONENTGUICLICKBUTTON
#define DT3_COMPONENTGUICLICKBUTTON
//==============================================================================
///	
///	File: ComponentGUIButton.hpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentBase.hpp"
#include "SoundResource.hpp"
#include "LatentCall.hpp"

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class TouchEvent;
class CameraObject;
class WorldNode;
class GUIObject;
class GUITouchEvent;

//==============================================================================
/// GUI behaviour for a button.
//==============================================================================

class ComponentGUIButton: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentGUIButton,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                    ComponentGUIButton	(void);	
									ComponentGUIButton	(const ComponentGUIButton &rhs);
        ComponentGUIButton &        operator =			(const ComponentGUIButton &rhs);	
        virtual                     ~ComponentGUIButton	(void);
    
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


        /// Defines standard accessors for the sound that is played when this button is clicked
		DEFINE_ACCESSORS (getSound, setSound, std::shared_ptr<SoundResource>, _sound);
        
        /// Defines standard accessors for the optional callback when this button is clicked
        DEFINE_ACCESSORS (getButtonPressedLatentCall,setButtonPressedLatentCall,std::shared_ptr<LatentCall>, _button_pressed_latent_call)
 
    private:
        std::shared_ptr<LatentCall>                        _button_pressed_latent_call;
    
        Plug<std::shared_ptr<SoundResource> >              _sound;

        Event                                       _clicked;

};

//==============================================================================
//==============================================================================

} // DT3

#endif
