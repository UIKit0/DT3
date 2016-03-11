//==============================================================================
///	
///	File: ComponentPhysicsSetVelocity.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentPhysicsSetVelocity.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "GeometryGroupResource.hpp"
#include "GeometryResource.hpp"
#include "MaterialResource.hpp"
#include "World.hpp"
#include "System.hpp"
#include "DrawBatcher.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentPhysicsSetVelocity,"Physics","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentPhysicsSetVelocity)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentPhysicsSetVelocity)
        
END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentPhysicsSetVelocity::ComponentPhysicsSetVelocity (void)
	:	_last_transform     (Matrix4::identity())
{  

}
		
ComponentPhysicsSetVelocity::ComponentPhysicsSetVelocity (const ComponentPhysicsSetVelocity &rhs)
    :   ComponentBase       (rhs),
		_last_transform     (rhs._last_transform)
{   

}

ComponentPhysicsSetVelocity & ComponentPhysicsSetVelocity::operator = (const ComponentPhysicsSetVelocity &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        
        _last_transform = rhs._last_transform;
    }
    return (*this);
}
			
ComponentPhysicsSetVelocity::~ComponentPhysicsSetVelocity (void)
{

}

//==============================================================================
//==============================================================================

void ComponentPhysicsSetVelocity::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentPhysicsSetVelocity::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
    archive->pop_domain ();
}

void ComponentPhysicsSetVelocity::archive_read_done (void)
{
}

void ComponentPhysicsSetVelocity::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentPhysicsSetVelocity::tick (DTfloat dt)
{
    if (dt <= 0.0F)
        return;

    PlaceableObject *placeable = checkedCast<PlaceableObject*>(getOwner());
    if (!placeable)
        return;
        
    Matrix4 current_transform = placeable->getTransform();
            
    // Velocity is easy
    placeable->setVelocity( (current_transform.translation() - _last_transform.translation()) / dt );
    
    // Angular velocity is more difficult
    // See: http://www.physicsforums.com/showthread.php?t=477556
    
    // M' = exp(A * dt) M   where
    //  M' = next orientation
    //  M  = current orientation
    //  A  = skew symmetric matrix
    //          [ 0   -Az Ay  ]
    //          | Az  0   -Ax ]
    //          [ -Ay Ax  0   ]
    // So (1/dt) * log[M'/M] = A
    // To compute the logarithm, let Y = M'/M - I where I is the identity matrix
    // Then log(M'/M) = log(I + Y) = Y - Y^2/2 + Y^3/3 - Y^4/4 + etc.

    Matrix3 Y = current_transform.orientation() * _last_transform.orientation().inversed() - Matrix3::identity();
    Matrix3 Y2 = Y*Y;
    Matrix3 Y3 = Y2*Y;
    Matrix3 Y4 = Y3*Y;
    
    Matrix3 A = (Y - Y2/2.0F + Y3/3.0F - Y4/4.0F) / dt;
    
    placeable->setAngularVelocity(Vector3(A._m32, A._m13, A._m21));
    
    // Copy current transform
    _last_transform = current_transform;
}

//==============================================================================
//==============================================================================

void ComponentPhysicsSetVelocity::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    World *w = getOwner()->getWorld();
    w->registerForTick(getOwner(), makeCallback(this, &type::tick));
    
    PlaceableObject *placeable = checkedCast<PlaceableObject*>(getOwner());
    if (!placeable)
        return;

    _last_transform = placeable->getTransform();
}

void ComponentPhysicsSetVelocity::removeFromOwner (void)
{
    World *w = getOwner()->getWorld();
    w->unregisterForTick(getOwner(), makeCallback(this, &type::tick));

    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

} // DT3

