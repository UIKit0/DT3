#ifndef DT3_COMPONENTGUIEATEVENT
#define DT3_COMPONENTGUIEATEVENT
//==============================================================================
///	
///	File: ComponentGUIEatEvent.hpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================
// TODO: DEPRICATED, DELETE THIS CLASS
//==============================================================================

#include "ComponentBase.hpp"

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class GeometryGroupResource;
class TouchEvent;
class CameraObject;
class WorldNode;

//==============================================================================
/// GUI behaviour for an object that eats all events sent to it.
//==============================================================================

class ComponentGUIEatEvent: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentGUIEatEvent,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                    ComponentGUIEatEvent	(void);	
									ComponentGUIEatEvent	(const ComponentGUIEatEvent &rhs);
        ComponentGUIEatEvent &      operator =              (const ComponentGUIEatEvent &rhs);	
        virtual                     ~ComponentGUIEatEvent	(void);
    
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
};

//==============================================================================
//==============================================================================

} // DT3

#endif
