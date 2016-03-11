#ifndef DT3_COMPONENTDRAWANIMATEDMESH
#define DT3_COMPONENTDRAWANIMATEDMESH
//==============================================================================
///	
///	File: ComponentDrawAnimatedMesh.hpp
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
class AnimationPose;
class SkeletonJoint;
class Matrix4;

//==============================================================================
/// Component that can draw an animated mesh.
//==============================================================================

class ComponentDrawAnimatedMesh: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentDrawAnimatedMesh,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                    ComponentDrawAnimatedMesh	(void);	
									ComponentDrawAnimatedMesh	(const ComponentDrawAnimatedMesh &rhs);
        ComponentDrawAnimatedMesh & operator =                  (const ComponentDrawAnimatedMesh &rhs);	
        virtual                     ~ComponentDrawAnimatedMesh  (void);
    
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

		DEFINE_ACCESSORS            (getGeometryGroup, setGeometryGroup, std::shared_ptr<GeometryGroupResource>, _geometry_group);
  		DEFINE_ACCESSORS            (getMaterial, setMaterial, std::shared_ptr<MaterialResource>, _material);

    private:
		Plug<std::shared_ptr<GeometryGroupResource> >                      _geometry_group;
		Plug<std::shared_ptr<MaterialResource> >                           _material;
        Plug<std::shared_ptr<AnimationPose> >                              _animation_pose;
        
        std::vector<Matrix4>                                              _transforms;
        
        void                        calculateSkeleton   (AnimationPose *pose, const Matrix4 &parent_transform, const std::vector<SkeletonJoint>& joints);

};

//==============================================================================
//==============================================================================

} // DT3

#endif
