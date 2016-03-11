#ifndef DT3_COMPONENTDRAWCAMERA
#define DT3_COMPONENTDRAWCAMERA
//==============================================================================
///	
///	File: ComponentDrawCamera.hpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentBase.hpp"
#include "MaterialResource.hpp"

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class GeometryGroupResource;
class MaterialResource;
class CameraObject;

//==============================================================================
/// Component that can draw a camera wireframe. This is useful for
/// visualizing different cameras in the world.
//==============================================================================

class ComponentDrawCamera: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentDrawCamera,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                    ComponentDrawCamera	(void);	
									ComponentDrawCamera	(const ComponentDrawCamera &rhs);
        ComponentDrawCamera &		operator =			(const ComponentDrawCamera &rhs);	
        virtual                     ~ComponentDrawCamera(void);
    
        virtual void                archive_read			(Archive *archive);
        virtual void                archive_write		(Archive *archive);
		
	public:
		/// Called to initialize the object
		virtual void				initialize			(void);
        
		/// Returns the component type. This defines which slot the component is
        /// put into on the object.
		/// \return Component type
        virtual ComponentType       getComponentType    (void)  {   return COMPONENT_DRAW;  }

		/// Draw Callback for component
		/// \param camera Camera used for drawing
        void                        draw                (CameraObject* camera);
        
		/// Called when this component is added to the owner. Note that this will
        /// only be called if the owner is added to a world already. If not it 
        /// will be called when it is added to the World.
		/// \param owner Pointer to the owner
		virtual void                addToOwner          (ObjectBase *owner);

		/// Called when this component is removed from its owner.
		virtual void                removeFromOwner     (void);


		DEFINE_ACCESSORS(getColor, setColor, Color, _color);

    private:
        MaterialResource            _line_material;
        
		Plug<Color>					_color;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
