#ifndef DT3_COMPONENTDRAWSKY
#define DT3_COMPONENTDRAWSKY
//==============================================================================
///	
///	File: ComponentDrawSky.hpp
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

class GeometryGroupResource;
class MaterialResource;
class CameraObject;

//==============================================================================
/// Component that can draw a sky box.
//==============================================================================

class ComponentDrawSky: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentDrawSky,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                    ComponentDrawSky	(void);	
									ComponentDrawSky	(const ComponentDrawSky &rhs);
        ComponentDrawSky &			operator =			(const ComponentDrawSky &rhs);	
        virtual                     ~ComponentDrawSky	(void);
    
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

    private:
        DTboolean                                   _center_on_camera;
    
		Plug<std::shared_ptr<MaterialResource> >			_material_front;
		Plug<std::shared_ptr<MaterialResource> >			_material_back;
		Plug<std::shared_ptr<MaterialResource> >			_material_left;
		Plug<std::shared_ptr<MaterialResource> >			_material_right;
		Plug<std::shared_ptr<MaterialResource> >			_material_up;
		Plug<std::shared_ptr<MaterialResource> >			_material_down;

		Plug<Color>                                 _color;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
