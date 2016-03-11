//==============================================================================
///	
///	File: ComponentDrawMesh.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentDrawMesh.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "GeometryGroupResource.hpp"
#include "GeometryResource.hpp"
#include "MaterialResource.hpp"
#include "ShaderResource.hpp"
#include "World.hpp"
#include "System.hpp"
#include "DrawUtils.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentDrawMesh,"Drawing","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentDrawMesh)

IMPLEMENT_PLUG_INFO(_geometry_group)
IMPLEMENT_PLUG_INFO(_material)

IMPLEMENT_PLUG_INFO(_p0)
IMPLEMENT_PLUG_INFO(_p1)
IMPLEMENT_PLUG_INFO(_p2)
IMPLEMENT_PLUG_INFO(_p3)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentDrawMesh)

    PLUG_INIT(_geometry_group, "Geometry_Group")
		.setInput(true);
        
    PLUG_INIT(_material, "Material")
		.setInput(true);
    
    PLUG_INIT(_p0, "Param0")
		.setInput(true);

    PLUG_INIT(_p1, "Param1")
		.setInput(true);

    PLUG_INIT(_p2, "Param2")
		.setInput(true);

    PLUG_INIT(_p3, "Param3")
		.setInput(true);

END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentDrawMesh::ComponentDrawMesh (void)
    :   _geometry_group     (PLUG_INFO(_geometry_group)),
        _material           (PLUG_INFO(_material)),
        _p0                 (PLUG_INFO(_p0), 0.0F),
        _p1                 (PLUG_INFO(_p1), 0.0F),
        _p2                 (PLUG_INFO(_p2), 0.0F),
        _p3                 (PLUG_INFO(_p3), 0.0F),
        _params_pos         (-1)
{

}
		
ComponentDrawMesh::ComponentDrawMesh (const ComponentDrawMesh &rhs)
    :   ComponentBase       (rhs),
        _geometry_group     (rhs._geometry_group),
        _material           (rhs._material),
        _p0                 (rhs._p0),
        _p1                 (rhs._p1),
        _p2                 (rhs._p2),
        _p3                 (rhs._p3),
        _params_pos         (rhs._params_pos)
{

}

ComponentDrawMesh & ComponentDrawMesh::operator = (const ComponentDrawMesh &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        
        _geometry_group = rhs._geometry_group;
        _material = rhs._material;
        
        _p0 = rhs._p0;
        _p1 = rhs._p1;
        _p2 = rhs._p2;
        _p3 = rhs._p3;
    }
    return (*this);
}
			
ComponentDrawMesh::~ComponentDrawMesh (void)
{

}

//==============================================================================
//==============================================================================

void ComponentDrawMesh::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentDrawMesh::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
        		
	*archive << ARCHIVE_PLUG(_geometry_group, DATA_PERSISTENT | DATA_SETTABLE);

    if (archive->getVersion() >= 1372)
        *archive << ARCHIVE_DATA_ACCESSORS("Material", ComponentDrawMesh::getMaterial, ComponentDrawMesh::setMaterial, DATA_PERSISTENT | DATA_SETTABLE);
    else
        *archive << ARCHIVE_PLUG(_material, DATA_PERSISTENT | DATA_SETTABLE);

    if (archive->getVersion() >= 1372) {
        *archive << ARCHIVE_PLUG(_p0, DATA_PERSISTENT | DATA_SETTABLE);
        *archive << ARCHIVE_PLUG(_p1, DATA_PERSISTENT | DATA_SETTABLE);
        *archive << ARCHIVE_PLUG(_p2, DATA_PERSISTENT | DATA_SETTABLE);
        *archive << ARCHIVE_PLUG(_p3, DATA_PERSISTENT | DATA_SETTABLE);
    }

    archive->pop_domain ();
}

void ComponentDrawMesh::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	
	*archive << ARCHIVE_PLUG(_geometry_group, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_DATA_ACCESSORS("Material", ComponentDrawMesh::getMaterial, ComponentDrawMesh::setMaterial, DATA_PERSISTENT | DATA_SETTABLE);

    *archive << ARCHIVE_PLUG(_p0, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_p1, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_p2, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_p3, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

std::shared_ptr<MaterialResource> ComponentDrawMesh::getMaterial (void) const
{
    return _material;
}

void ComponentDrawMesh::setMaterial (std::shared_ptr<MaterialResource> material)
{
    if (material.isValid()) {
        _params_pos = material->getShader()->getParameterIndex("uParams");
    } else {
        _params_pos = -1;
    }

    _material = material;
}

//==============================================================================
//==============================================================================

void ComponentDrawMesh::draw (CameraObject* camera)
{
    if (_geometry_group->isNull() || _material->isNull())
        return;
        
    PlaceableObject *placeable = checkedCast<PlaceableObject*>(getOwner());
    if (!placeable)
        return;
        
    std::shared_ptr<GeometryResource> geometry = (**_geometry_group).getBestGeometry(placeable->getTranslation(), camera);
    if (geometry.isNull())
        return;
    
    if (_params_pos >= 0)
        (*_material)->getShader()->setParameterValue(_params_pos,0, _p0,_p1,_p2,_p3);

    // Draw geometry
    DrawUtils::drawBatch(   placeable->getTransform(),
                            geometry.get(),
                            _material->get());
}

//==============================================================================
//==============================================================================

void ComponentDrawMesh::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    World *w = getOwner()->getWorld();

    w->registerForDraw(getOwner(), makeCallback(this, &type::draw));
}

void ComponentDrawMesh::removeFromOwner (void)
{
    World *w = getOwner()->getWorld();

    w->unregisterForDraw(getOwner(), makeCallback(this, &type::draw));

    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

} // DT3

