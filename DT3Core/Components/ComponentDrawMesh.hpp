#ifndef DT3_COMPONENTDRAWMESH
#define DT3_COMPONENTDRAWMESH
//==============================================================================
///	
///	File: ComponentDrawMesh.hpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3Core/Components/ComponentBase.hpp"
#include "DT3Core/Types/Node/Plug.hpp"
#include "DT3Core/Resources/ResourceTypes/MaterialResource.hpp"
#include "DT3Core/Resources/ResourceTypes/ShaderResource.hpp"
#include "DT3Core/Resources/ResourceTypes/GeometryResource.hpp"
#include "DT3Core/Devices/DeviceGraphics.hpp"

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class CameraObject;

//==============================================================================
/// Component that can draw a rectangular image.
//==============================================================================

class ComponentDrawMesh: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentDrawMesh,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                            ComponentDrawMesh   (void);
                                            ComponentDrawMesh   (const ComponentDrawMesh &rhs);
        ComponentDrawMesh &                 operator =          (const ComponentDrawMesh &rhs);
        virtual                             ~ComponentDrawMesh  (void);
    
        virtual void                        archive             (const std::shared_ptr<Archive> &archive);
		
	public:
		/// Called to initialize the object
		virtual void                        initialize          (void);
        
		/// Returns the component type. This defines which slot the component is
        /// put into on the object.
		/// \return Component type
        virtual ComponentType               component_type      (void)  {   return COMPONENT_DRAW;  }

		/// Draw Callback for component
		/// \param camera Camera used for drawing
        /// \param lag frame lag
        void                                draw                (const std::shared_ptr<CameraObject> &camera, const DTfloat lag);
        
		/// Called when this component is added to the owner. Note that this will
        /// only be called if the owner is added to a world already. If not it 
        /// will be called when it is added to the World.
		/// \param owner Pointer to the owner
		virtual void                        add_to_owner        (ObjectBase *owner);

		/// Called when this component is removed from its owner.
		virtual void                        remove_from_owner   (void);
    
		/// Returns the material for the Image Plane
		/// \return The material for the image plane
        const std::shared_ptr<MaterialResource>&    material    (void) const;
        
		/// Sets the material for the Image Plane
        /// \param material Pointer to new material
        void                                set_material        (const std::shared_ptr<MaterialResource> &material);

		/// Returns the material for the Image Plane
		/// \return The material for the image plane
        const std::shared_ptr<ShaderResource>&      shader      (void) const;
        
		/// Sets the material for the Image Plane
        /// \param material Pointer to new material
        void                                set_shader          (const std::shared_ptr<ShaderResource> &shader);

		/// Returns the material for the Image Plane
		/// \return The material for the image plane
        const std::shared_ptr<GeometryResource>&    geometry      (void) const;
        
		/// Sets the material for the Image Plane
        /// \param material Pointer to new material
        void                                set_geometry          (const std::shared_ptr<GeometryResource> &geometry);

    private:
        void                                screen_opened       (DTuint width, DTuint height);
        void                                screen_closed       (void);

		Plug<std::shared_ptr<GeometryResource> >        _geometry;
		Plug<std::shared_ptr<MaterialResource> >        _material;
		Plug<std::shared_ptr<ShaderResource> >          _shader;

        struct MeshCache {
            DTuint                                      _num_verts;
            DTuint                                      _num_indices;
        
            std::shared_ptr<DT3GLAttribBufferResource>  _v_buffer;
            std::shared_ptr<DT3GLAttribBufferResource>  _n_buffer;
            std::shared_ptr<DT3GLAttribBufferResource>  _t_buffer;
            std::shared_ptr<DT3GLAttribBufferResource>  _t0_buffer;
            std::shared_ptr<DT3GLAttribBufferResource>  _t1_buffer;
            std::shared_ptr<DT3GLElementBufferResource> _elements_buffer;
        };
        std::vector<MeshCache>                          _mesh_cache;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
