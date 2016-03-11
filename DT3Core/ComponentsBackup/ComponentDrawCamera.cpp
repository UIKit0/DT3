//==============================================================================
///	
///	File: ComponentDrawCamera.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentDrawCamera.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "GeometryGroupResource.hpp"
#include "GeometryResource.hpp"
#include "MaterialResource.hpp"
#include "World.hpp"
#include "DrawBatcher.hpp"
#include "System.hpp"
#include "ShaderResource.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
//==============================================================================

namespace {

    const DTfloat THICKNESS = 0.214613F;
    const DTfloat SIDE_THICKNESS = 0.145276;
    const DTfloat LENS_LENGTH = 0.4F;
    const DTfloat LENS_THICKNESS = 0.2F;

    Vector2 box[] = {
        Vector2(0.497588F,0.0F),
        Vector2(0.497588F,1.275792F),
        Vector2(-0.347154F,1.275792F),
        Vector2(-0.347154F,0.0F),
        Vector2(0.497588F,0.0F)
    };

    Vector2 can[] = {
        Vector2(0.497588F,0.286402F),
        Vector2(0.560251F,0.279191F),
        Vector2(0.685578F,0.264767F),
        Vector2(0.891234F,0.338227F),
        Vector2(1.026228F,0.482607F),
        Vector2(1.113767F,0.664798F),
        Vector2(1.114635F,0.867833F),
        Vector2(1.023624F,1.053824F),
        Vector2(0.900785F,1.183003F),
        Vector2(0.649981F,1.27875F),
        //Vector2(0.630428F,1.183169F),
        Vector2(0.61229F,1.60861F),
        Vector2(0.496101F,1.738196F),
        Vector2(0.319402F,1.870589F),
        Vector2(0.100924F,1.905739F),
        Vector2(-0.0982205F,1.841039F),
        Vector2(-0.263489F,1.68282F),
        Vector2(-0.340588F,1.51251F),
        Vector2(-0.325679F,1.354698F),
        Vector2(-0.318225F,1.275792F) 
    };

    Vector2 side[] = {
        Vector2(-0.342071F,0.25014F),
        Vector2(0.403644F,0.25014F),
        Vector2(0.403644F,1.103254F),
        Vector2(-0.342071F,1.190836F),
        Vector2(-0.342071F,0.25014F)
    };

    Vector2 lens[] = {
        Vector2(LENS_THICKNESS,0.0F),
        Vector2(LENS_THICKNESS,-LENS_LENGTH),
        Vector2(-LENS_THICKNESS,-LENS_LENGTH),
        Vector2(-LENS_THICKNESS,0.0F),
        Vector2(LENS_THICKNESS,0.0F)
    };
}

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentDrawCamera,"Drawing","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentDrawCamera)

IMPLEMENT_PLUG_INFO(_geometry_group)
IMPLEMENT_PLUG_INFO(_material)
IMPLEMENT_PLUG_INFO(_color)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentDrawCamera)

	PLUG_INIT(_color,"Color")
		.setInput(true)
		.setOutput(true);
      
END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentDrawCamera::ComponentDrawCamera (void)
    :   _color              (PLUG_INFO(_color), Color(1.0F,0.0F,0.0F,1.0F))
{  

}
		
ComponentDrawCamera::ComponentDrawCamera (const ComponentDrawCamera &rhs)
    :   ComponentBase       (rhs),
		_color              (rhs._color)
{   

}

ComponentDrawCamera & ComponentDrawCamera::operator = (const ComponentDrawCamera &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        _color = rhs._color;
    }
    return (*this);
}
			
ComponentDrawCamera::~ComponentDrawCamera (void)
{

}

//==============================================================================
//==============================================================================

void ComponentDrawCamera::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentDrawCamera::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
	*archive << ARCHIVE_DATA_ACCESSORS("Color", ComponentDrawCamera::getColor, ComponentDrawCamera::setColor, DATA_PERSISTENT | DATA_SETTABLE);
    archive->pop_domain ();
}

void ComponentDrawCamera::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	*archive << ARCHIVE_DATA_ACCESSORS("Color", ComponentDrawCamera::getColor, ComponentDrawCamera::setColor, DATA_PERSISTENT | DATA_SETTABLE);
    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentDrawCamera::draw (CameraObject* camera)
{
    CameraObject *placeable = checkedCast<CameraObject*>(getOwner());
    if (!placeable)
        return;
        
    _line_material.setBlendEnable(false);
    _line_material.setDepthEnable(true);
    _line_material.setCullMode(DT3GL_CULL_NONE);
    _line_material.setColor(_color);
	_line_material.setShader(ShaderResource::getShader(FilePath("{editorline.shdr}")));


    DrawBatcher b;
    b.batchBegin(&_line_material, placeable->getTransform(), DrawBatcher::BATCH_LINES, DrawBatcher::FMT_V);

    // Can
    for (DTuint i = 0; i < ARRAY_SIZE(can); ++i) {        
        b.vertex( Vector3(THICKNESS, can[i].x, can[i].y) );
        b.vertex( Vector3(-THICKNESS, can[i].x, can[i].y) );
    }

    for (DTuint i = 0; i < ARRAY_SIZE(can)-1; ++i) {        
        b.vertex( Vector3(THICKNESS, can[i].x, can[i].y) );
        b.vertex( Vector3(THICKNESS, can[i+1].x, can[i+1].y) );
        
        b.vertex( Vector3(-THICKNESS, can[i].x, can[i].y) );
        b.vertex( Vector3(-THICKNESS, can[i+1].x, can[i+1].y) );
    }
    
    // Box
    for (DTuint i = 0; i < ARRAY_SIZE(box); ++i) {        
        b.vertex( Vector3(THICKNESS, box[i].x, box[i].y) );
        b.vertex( Vector3(-THICKNESS, box[i].x, box[i].y) );
    }

    for (DTuint i = 0; i < ARRAY_SIZE(box)-1; ++i) {        
        b.vertex( Vector3(THICKNESS, box[i].x, box[i].y) );
        b.vertex( Vector3(THICKNESS, box[i+1].x, box[i+1].y) );
        
        b.vertex( Vector3(-THICKNESS, box[i].x, box[i].y) );
        b.vertex( Vector3(-THICKNESS, box[i+1].x, box[i+1].y) );
    }

    // Side
    for (DTuint i = 0; i < ARRAY_SIZE(side); ++i) {        
        b.vertex( Vector3(THICKNESS, side[i].x, side[i].y) );
        b.vertex( Vector3(SIDE_THICKNESS+THICKNESS, side[i].x, side[i].y) );
    }

    for (DTuint i = 0; i < ARRAY_SIZE(side)-1; ++i) {        
        b.vertex( Vector3(THICKNESS, side[i].x, side[i].y) );
        b.vertex( Vector3(THICKNESS, side[i+1].x, side[i+1].y) );
        
        b.vertex( Vector3(SIDE_THICKNESS+THICKNESS, side[i].x, side[i].y) );
        b.vertex( Vector3(SIDE_THICKNESS+THICKNESS, side[i+1].x, side[i+1].y) );
    }
    
    // Lens
    for (DTuint i = 0; i < ARRAY_SIZE(lens); ++i) {        
        b.vertex( Vector3(LENS_THICKNESS, lens[i].x, lens[i].y) );
        b.vertex( Vector3(-LENS_THICKNESS, lens[i].x, lens[i].y) );
    }

    for (DTuint i = 0; i < ARRAY_SIZE(lens)-1; ++i) {        
        b.vertex( Vector3(LENS_THICKNESS, lens[i].x, lens[i].y) );
        b.vertex( Vector3(LENS_THICKNESS, lens[i+1].x, lens[i+1].y) );
        
        b.vertex( Vector3(-LENS_THICKNESS, lens[i].x, lens[i].y) );
        b.vertex( Vector3(-LENS_THICKNESS, lens[i+1].x, lens[i+1].y) );
    }
    
    b.batchEnd();
	b.flush();

    // Frustum
    
	placeable->calculateFrustum();
	Matrix4 projection_inv = placeable->getProjection().inversed();
	
	Vector3 near_p0, near_p1, near_p2, near_p3;
	Vector3 far_p0, far_p1, far_p2, far_p3;
	
	MATTransform4H(projection_inv, Vector3(-1.0F,-1.0F,-1.0F), near_p0);
	MATTransform4H(projection_inv, Vector3(1.0F,-1.0F,-1.0F), near_p1);
	MATTransform4H(projection_inv, Vector3(1.0F,1.0F,-1.0F), near_p2);
	MATTransform4H(projection_inv, Vector3(-1.0F,1.0F,-1.0F), near_p3);
	
	MATTransform4H(projection_inv, Vector3(-1.0F,-1.0F,1.0F), far_p0);
	MATTransform4H(projection_inv, Vector3(1.0F,-1.0F,1.0F), far_p1);
	MATTransform4H(projection_inv, Vector3(1.0F,1.0F,1.0F), far_p2);
	MATTransform4H(projection_inv, Vector3(-1.0F,1.0F,1.0F), far_p3);

	b.batchBegin (&_line_material, placeable->getTransform(), DrawBatcher::BATCH_LINE_LOOP, DrawBatcher::FMT_V);
	b.vertex ( near_p0);
	b.vertex ( near_p1);
	b.vertex ( near_p2);
	b.vertex ( near_p3);
	b.batchEnd();
	b.flush();
	
	b.batchBegin (&_line_material, placeable->getTransform(), DrawBatcher::BATCH_LINE_LOOP, DrawBatcher::FMT_V);
	b.vertex ( far_p0);
	b.vertex ( far_p1);
	b.vertex ( far_p2);
	b.vertex ( far_p3);
	b.batchEnd();
	b.flush();
	
	b.batchBegin (&_line_material, placeable->getTransform(), DrawBatcher::BATCH_LINE_LOOP, DrawBatcher::FMT_V);
	b.vertex ( near_p0);
	b.vertex ( near_p1);
	b.vertex ( far_p1);
	b.vertex ( far_p0);
	b.batchEnd();
	b.flush();
	
	b.batchBegin (&_line_material, placeable->getTransform(), DrawBatcher::BATCH_LINE_LOOP, DrawBatcher::FMT_V);
	b.vertex ( near_p2);
	b.vertex ( near_p3);
	b.vertex ( far_p3);
	b.vertex ( far_p2);
	b.batchEnd();	
	b.flush();

    

}

//==============================================================================
//==============================================================================

void ComponentDrawCamera::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    World *w = getOwner()->getWorld();

    w->registerForDraw(getOwner(), makeCallback(this, &type::draw));
}

void ComponentDrawCamera::removeFromOwner (void)
{
    World *w = getOwner()->getWorld();

    w->unregisterForDraw(getOwner(), makeCallback(this, &type::draw));

    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

} // DT3

