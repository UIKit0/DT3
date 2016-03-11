#ifndef DT3_COMPONENTGUIMOVEABLE
#define DT3_COMPONENTGUIMOVEABLE
//==============================================================================
///	
///	File: ComponentGUIMoveable.hpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentBase.hpp"

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class GUITouchEvent;
class TouchEvent;
class CameraObject;
class WorldNode;

//==============================================================================
/// GUI behaviour for a moveable widget (i.e. a widget that can be dragged)
//==============================================================================

class ComponentGUIMoveable: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentGUIMoveable,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                    ComponentGUIMoveable	(void);	
									ComponentGUIMoveable	(const ComponentGUIMoveable &rhs);
        ComponentGUIMoveable &        operator =			(const ComponentGUIMoveable &rhs);	
        virtual                     ~ComponentGUIMoveable	(void);
    
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

    private:
};

//==============================================================================
//==============================================================================

} // DT3

#endif
