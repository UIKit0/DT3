//==============================================================================
///	
///	File: ComponentDrawAnimatedMesh.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentDrawAnimatedMesh.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "GeometryGroupResource.hpp"
#include "GeometryResource.hpp"
#include "MaterialResource.hpp"
#include "World.hpp"
#include "System.hpp"
#include "AnimationPose.hpp"
#include "ConsoleStream.hpp"
#include "DrawUtils.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentDrawAnimatedMesh,"Drawing","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentDrawAnimatedMesh)

IMPLEMENT_PLUG_INFO(_geometry_group)
IMPLEMENT_PLUG_INFO(_material)
IMPLEMENT_PLUG_INFO(_animation_pose)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentDrawAnimatedMesh)

    PLUG_INIT(_geometry_group, "Geometry_Group")
		.setInput(true);
        
    PLUG_INIT(_material, "Material")
		.setInput(true);
        
	PLUG_INIT(_animation_pose,"Pose")
		.setInput(true);
        
END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentDrawAnimatedMesh::ComponentDrawAnimatedMesh (void)
    :   _geometry_group     (PLUG_INFO(_geometry_group)),
        _material           (PLUG_INFO(_material)),
		_animation_pose     (PLUG_INFO(_animation_pose))
{

}
		
ComponentDrawAnimatedMesh::ComponentDrawAnimatedMesh (const ComponentDrawAnimatedMesh &rhs)
    :   ComponentBase       (rhs),
        _geometry_group     (rhs._geometry_group),
        _material           (rhs._material),
		_animation_pose     (rhs._animation_pose)
{

}

ComponentDrawAnimatedMesh & ComponentDrawAnimatedMesh::operator = (const ComponentDrawAnimatedMesh &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        
        _geometry_group = rhs._geometry_group;
        _material = rhs._material;
		_animation_pose = rhs._animation_pose;	// Plug takes care of refcounts
    }
    return (*this);
}
			
ComponentDrawAnimatedMesh::~ComponentDrawAnimatedMesh (void)
{

}

//==============================================================================
//==============================================================================

void ComponentDrawAnimatedMesh::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentDrawAnimatedMesh::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
        		
	*archive << ARCHIVE_PLUG(_geometry_group, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_material, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

void ComponentDrawAnimatedMesh::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	
	*archive << ARCHIVE_PLUG(_geometry_group, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_material, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentDrawAnimatedMesh::calculateSkeleton (AnimationPose *pose, const Matrix4 &parent_transform, const std::vector<SkeletonJoint>& joints)
{

	// Calculate every sub joint
	for (DTuint i = 0; i < joints.size(); ++i) {
		const SkeletonJoint &joint = joints[i];
		
		// Lookup and calculate transform in the pose
		DTuint name_hash = joint.getNameHash();
		
		Matrix4 joint_transform;
		Matrix4 transform;
       
		// Store transform for vertex program
		DTuint index = joint.getJointIndex();
		
		if (pose->getJointTransform(name_hash, joint_transform)) {
			transform = parent_transform * joint_transform;
		} else {
			transform = parent_transform * joint.getLocalTransform();
		}
                                
        if(index < _transforms.size()) {
            _transforms[index] = transform * joint.getWorldTransformInverse();
        }
             
		// Calculate sub bones
		calculateSkeleton (pose, transform, joint.getChildren());
	}
}

//==============================================================================
//==============================================================================

void ComponentDrawAnimatedMesh::draw (CameraObject* camera)
{
    if (_geometry_group->isNull() || _material->isNull())
        return;
        
    PlaceableObject *placeable = checkedCast<PlaceableObject*>(getOwner());
    if (!placeable)
        return;
        
    std::shared_ptr<GeometryResource> geometry = (**_geometry_group).getBestGeometry(placeable->getTranslation(), camera);
    if (geometry.isNull())
        return;

    const Skeleton &skeleton = geometry->getSkeleton();

    if (skeleton.getSkeletonSize() != _transforms.size()) {
        _transforms.resize(skeleton.getSkeletonSize(), Matrix4::identity());
    }

    if (_animation_pose->isValid()) {
        calculateSkeleton (_animation_pose->get(), Matrix4::identity(), skeleton.getSkeleton());
    }

    // Draw geometry
    DrawUtils::drawBatch(   placeable->getTransform(),
                            geometry.get(),
                            _material->get(),
                            &_transforms);
}

//==============================================================================
//==============================================================================

void ComponentDrawAnimatedMesh::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    World *w = getOwner()->getWorld();

    w->registerForDraw(getOwner(), makeCallback(this, &type::draw));
}

void ComponentDrawAnimatedMesh::removeFromOwner (void)
{
    World *w = getOwner()->getWorld();

    w->unregisterForDraw(getOwner(), makeCallback(this, &type::draw));

    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

} // DT3

