#ifndef DT3_COMPONENTPHYSICSSETVELOCITY
#define DT3_COMPONENTPHYSICSSETVELOCITY
//==============================================================================
///	
///	File: ComponentPhysicsSetVelocity.hpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentBase.hpp"
#include "Matrix.hpp"

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class GeometryGroupResource;
class MaterialResource;
class CameraObject;

//==============================================================================
/// Component that updates the velocity (linear and rotational) of a
/// placeable object when it is moved manually.
//==============================================================================

class ComponentPhysicsSetVelocity: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentPhysicsSetVelocity,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                        ComponentPhysicsSetVelocity	(void);	
                                        ComponentPhysicsSetVelocity	(const ComponentPhysicsSetVelocity &rhs);
        ComponentPhysicsSetVelocity &   operator =                  (const ComponentPhysicsSetVelocity &rhs);	
        virtual                         ~ComponentPhysicsSetVelocity(void);
    
        virtual void                archive_read			(Archive *archive);
        virtual void                archive_read_done     (void);
        virtual void                archive_write		(Archive *archive);
		
	public:
		/// Called to initialize the object
		virtual void				initialize			(void);
        
		/// Returns the component type. This defines which slot the component is
        /// put into on the object.
		/// \return Component type
        virtual ComponentType       getComponentType    (void)  {   return COMPONENT_PHYSICS;  }

		/// Callback called when the component is getting a tick
		/// \param dt delta time
        void                        tick                (DTfloat dt);
        
		/// Called when this component is added to the owner. Note that this will
        /// only be called if the owner is added to a world already. If not it 
        /// will be called when it is added to the World.
		/// \param owner Pointer to the owner
		virtual void                addToOwner          (ObjectBase *owner);

		/// Called when this component is removed from its owner.
		virtual void                removeFromOwner     (void);

    private:
        Matrix4                     _last_transform;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
