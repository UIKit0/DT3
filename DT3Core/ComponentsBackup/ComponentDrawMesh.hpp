#ifndef DT3_COMPONENTDRAWMESH
#define DT3_COMPONENTDRAWMESH
//==============================================================================
///	
///	File: ComponentDrawMesh.hpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentBase.hpp"
#include "GeometryGroupResource.hpp"

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class MaterialResource;
class CameraObject;

//==============================================================================
/// Component that can draw a mesh that is not animated.
//==============================================================================

class ComponentDrawMesh: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentDrawMesh,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                    ComponentDrawMesh	(void);	
									ComponentDrawMesh	(const ComponentDrawMesh &rhs);
        ComponentDrawMesh &			operator =			(const ComponentDrawMesh &rhs);	
        virtual                     ~ComponentDrawMesh	(void);
    
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

        /// Defines standard accessors for the geometry group
		DEFINE_ACCESSORS            (getGeometryGroup, setGeometryGroup, std::shared_ptr<GeometryGroupResource>, _geometry_group);

		/// Returns the material for the Image Plane
		/// \return The material for the image plane
        std::shared_ptr<MaterialResource>  getMaterial         (void) const;
        
		/// Sets the material for the Image Plane
        /// \param material Pointer to new material
        void                        setMaterial         (std::shared_ptr<MaterialResource> material);

        /// Defines standard accessors for user parameters
  		DEFINE_ACCESSORS            (getP1, setP1, DTfloat, _p0);
  		DEFINE_ACCESSORS            (getP2, setP2, DTfloat, _p1);
  		DEFINE_ACCESSORS            (getP3, setP3, DTfloat, _p2);
  		DEFINE_ACCESSORS            (getP4, setP4, DTfloat, _p3);

    private:
		Plug<std::shared_ptr<GeometryGroupResource> >	_geometry_group;
		Plug<std::shared_ptr<MaterialResource> >       _material;

		Plug<DTfloat>                           _p0;
		Plug<DTfloat>                           _p1;
		Plug<DTfloat>                           _p2;
		Plug<DTfloat>                           _p3;

        DTint                                   _params_pos;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
