//==============================================================================
///	
///	File: ComponentDrawMesh.cpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3Core/Components/ComponentDrawMesh.hpp"
#include "DT3Core/Types/FileBuffer/ArchiveObjectQueue.hpp"
#include "DT3Core/Types/FileBuffer/ArchiveData.hpp"
#include "DT3Core/Types/FileBuffer/ArchivePropertyReaderWriter.hpp"
#include "DT3Core/Types/Node/PlugNode.hpp"
#include "DT3Core/Types/Utility/ConsoleStream.hpp"
#include "DT3Core/Types/Graphics/DrawUtils.hpp"
#include "DT3Core/System/System.hpp"
#include "DT3Core/System/Factory.hpp"
#include "DT3Core/System/SystemCallbacks.hpp"
#include "DT3Core/Objects/ObjectBase.hpp"
#include "DT3Core/Objects/PlaceableObject.hpp"
#include "DT3Core/World/World.hpp"
#include "DT3Core/Types/Graphics/DrawUtils.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentDrawMesh,"Drawing","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentDrawMesh)

IMPLEMENT_PLUG_INFO_INDEX(_material)
IMPLEMENT_PLUG_INFO_INDEX(_shader)
IMPLEMENT_PLUG_INFO_INDEX(_geometry)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentDrawMesh)
        
    PLUG_INIT(_material, "Material")
		.set_input(true);

    PLUG_INIT(_shader, "Shader")
		.set_input(true);

    PLUG_INIT(_geometry, "Geometry")
		.set_input(true);
    
END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentDrawMesh::ComponentDrawMesh (void)
    :   _material           (PLUG_INFO_INDEX(_material)),
        _shader             (PLUG_INFO_INDEX(_shader)),
        _geometry           (PLUG_INFO_INDEX(_geometry))
{

}
		
ComponentDrawMesh::ComponentDrawMesh (const ComponentDrawMesh &rhs)
    :   ComponentBase       (rhs),
        _material           (rhs._material),
        _shader             (rhs._shader),
        _geometry           (rhs._geometry)
{

}

ComponentDrawMesh & ComponentDrawMesh::operator = (const ComponentDrawMesh &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        
        _material = rhs._material;
        _shader = rhs._shader;
        _geometry = rhs._geometry;
    }
    return (*this);
}
			
ComponentDrawMesh::~ComponentDrawMesh (void)
{
    SystemCallbacks::screen_opened_cb().remove(make_callback(this, &type::screen_opened));
    SystemCallbacks::screen_closed_cb().remove(make_callback(this, &type::screen_closed));
}

//==============================================================================
//==============================================================================

void ComponentDrawMesh::initialize (void)
{
	ComponentBase::initialize();

    SystemCallbacks::screen_opened_cb().add(make_callback(this, &type::screen_opened));
    SystemCallbacks::screen_closed_cb().add(make_callback(this, &type::screen_closed));
}

//==============================================================================
//==============================================================================

void ComponentDrawMesh::screen_opened (DTuint width, DTuint height)
{
    LOG_MESSAGE << "DrawBatcher::screen_opened";
}

void ComponentDrawMesh::screen_closed (void)
{
    LOG_MESSAGE << "DrawBatcher::screen_closed";

    _mesh_cache.clear();
}

//==============================================================================
//==============================================================================

void ComponentDrawMesh::archive (const std::shared_ptr<Archive> &archive)
{
    ComponentBase::archive(archive);

    archive->push_domain (class_id ());
	
    *archive << ARCHIVE_DATA_ACCESSORS("Material", ComponentDrawMesh::material, ComponentDrawMesh::set_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_ACCESSORS("Shader", ComponentDrawMesh::shader, ComponentDrawMesh::set_shader, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_ACCESSORS("Geometry", ComponentDrawMesh::geometry, ComponentDrawMesh::set_geometry, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

const std::shared_ptr<MaterialResource>& ComponentDrawMesh::material (void) const
{
    return _material.as_ref();
}

void ComponentDrawMesh::set_material (const std::shared_ptr<MaterialResource> &material)
{
    _material = material;
}

//==============================================================================
//==============================================================================

const std::shared_ptr<ShaderResource>& ComponentDrawMesh::shader (void) const
{
    return _shader.as_ref();
}

void ComponentDrawMesh::set_shader (const std::shared_ptr<ShaderResource> &shader)
{
    _shader = shader;
}

//==============================================================================
//==============================================================================

const std::shared_ptr<GeometryResource>& ComponentDrawMesh::geometry (void) const
{
    return _geometry.as_ref();
}

void ComponentDrawMesh::set_geometry (const std::shared_ptr<GeometryResource> &geometry)
{
    _geometry = geometry;
    _mesh_cache.clear();
}

//==============================================================================
//==============================================================================

void ComponentDrawMesh::draw (const std::shared_ptr<CameraObject> &camera, const DTfloat lag)
{
    if (!_material.as_ref() || !_shader.as_ref() || !_geometry.as_ref())
        return;
    
    PlaceableObject *placeable = checked_cast<PlaceableObject*>(owner());
    if (!placeable)
        return;

    DTint a_position = (*_shader)->attrib_slot(DT3GL_ATTRIB_POSITION);
    DTint a_normal = (*_shader)->attrib_slot(DT3GL_ATTRIB_NORMAL);
    DTint a_texcoord0 = (*_shader)->attrib_slot(DT3GL_ATTRIB_TEXCOORD0);
    DTint a_texcoord1 = (*_shader)->attrib_slot(DT3GL_ATTRIB_TEXCOORD1);
    DTint a_color = (*_shader)->attrib_slot(DT3GL_ATTRIB_COLOR);
    DTint a_tangent = (*_shader)->attrib_slot(DT3GL_ATTRIB_TANGENT);

    const std::vector<std::shared_ptr<Mesh>>& meshes = (*_geometry)->meshes();
    
    //
    // Rebuild mesh cache if need be
    //

    if (_mesh_cache.size() == 0 && meshes.size() > 0) {
    
        _mesh_cache.resize(meshes.size());
    
        for (DTuint i = 0; i < meshes.size(); ++i) {
            const std::shared_ptr<Mesh> &mesh = meshes[i];
        
            if (a_position >= 0 && mesh->vertex_stream().size() > 0) {
                _mesh_cache[i]._num_verts = mesh->vertex_stream().size();
                _mesh_cache[i]._v_buffer = System::renderer()->create_buffer( (DTubyte*) &(mesh->vertex_stream()[0]), mesh->vertex_stream().size() * sizeof(Vector3), DT3GL_BUFFER_FORMAT_3_FLOAT);
            } else {
                _mesh_cache[i]._num_verts = 0;
            }

            if (a_normal >= 0 && mesh->normals_stream().size() > 0) {
                _mesh_cache[i]._n_buffer = System::renderer()->create_buffer( (DTubyte*) &(mesh->normals_stream()[0]), mesh->normals_stream().size() * sizeof(Vector3), DT3GL_BUFFER_FORMAT_3_FLOAT);
            }

            if (a_tangent >= 0 && mesh->tangents_stream().size() > 0) {
                _mesh_cache[i]._t_buffer = System::renderer()->create_buffer( (DTubyte*) &(mesh->tangents_stream()[0]), mesh->tangents_stream().size() * sizeof(Vector3), DT3GL_BUFFER_FORMAT_3_FLOAT);
            }

            if (a_texcoord0 >= 0 && mesh->uv_stream0().size() > 0) {
                _mesh_cache[i]._t0_buffer = System::renderer()->create_buffer( (DTubyte*) &(mesh->uv_stream0()[0]), mesh->uv_stream0().size() * sizeof(Vector2), DT3GL_BUFFER_FORMAT_2_FLOAT);
            }

            if (a_texcoord1 >= 0 && mesh->uv_stream1().size() > 0) {
                _mesh_cache[i]._t1_buffer = System::renderer()->create_buffer( (DTubyte*) &(mesh->uv_stream1()[0]), mesh->uv_stream1().size() * sizeof(Vector2), DT3GL_BUFFER_FORMAT_2_FLOAT);
            }

            if (a_texcoord1 >= 0 && mesh->uv_stream1().size() > 0) {
                _mesh_cache[i]._t1_buffer = System::renderer()->create_buffer( (DTubyte*) &(mesh->uv_stream1()[0]), mesh->uv_stream1().size() * sizeof(Vector2), DT3GL_BUFFER_FORMAT_2_FLOAT);
            }
            
            // Elements
            if (mesh->index_stream().size() > 0) {
                _mesh_cache[i]._num_indices = mesh->index_stream().size() * 3;
                _mesh_cache[i]._elements_buffer = System::renderer()->create_index_buffer( (DTubyte*) &(mesh->index_stream()[0]), mesh->index_stream().size() * sizeof(DTuint) * 3, DT3GL_BUFFER_FORMAT_1_UINT);
            }
        
        }
    }
    
    //
    // Draw all meshes
    //

    for (DTuint i = 0; i < _mesh_cache.size(); ++i) {
        
        if (_mesh_cache[i]._v_buffer && a_position >= 0)     (*_shader)->attach_attribute_buffer(a_position, _mesh_cache[i]._v_buffer);
        else if (a_position >= 0)                            (*_shader)->attach_attribute_buffer(a_position, NULL);
        
        if (_mesh_cache[i]._n_buffer && a_normal >= 0)       (*_shader)->attach_attribute_buffer(a_normal, _mesh_cache[i]._n_buffer);
        else if (a_normal >= 0)                              (*_shader)->attach_attribute_buffer(a_normal, NULL);

        if (_mesh_cache[i]._t_buffer && a_tangent >= 0)      (*_shader)->attach_attribute_buffer(a_tangent, _mesh_cache[i]._t_buffer);
        else if (a_tangent >= 0)                             (*_shader)->attach_attribute_buffer(a_tangent, NULL);

        if (_mesh_cache[i]._t0_buffer && a_texcoord0 >= 0)   (*_shader)->attach_attribute_buffer(a_texcoord0, _mesh_cache[i]._t0_buffer);
        else if (a_texcoord0 >= 0)                           (*_shader)->attach_attribute_buffer(a_texcoord0, NULL);

        if (_mesh_cache[i]._t1_buffer && a_texcoord1 >= 0)   (*_shader)->attach_attribute_buffer(a_texcoord1, _mesh_cache[i]._t1_buffer);
        else if (a_texcoord1 >= 0)                           (*_shader)->attach_attribute_buffer(a_texcoord1, NULL);
        
        // No color. We have to clear it because a previous object might have set it on the shader.
        if (a_color >= 0)
            (*_shader)->attach_attribute_buffer(a_color, NULL);
        
        // Setup render state
        DrawUtils::activate_state(camera, _material, _shader, placeable->transform());
        
        // Draw!!
        if (_mesh_cache[i]._elements_buffer) {
            System::renderer()->draw_indexed_arrays (_mesh_cache[i]._elements_buffer, DT3GL_PRIM_TRIS, _mesh_cache[i]._num_indices);
        } else {
            System::renderer()->draw_arrays(DT3GL_PRIM_TRIS, _mesh_cache[i]._num_verts);
        }

    }
}

//==============================================================================
//==============================================================================

void ComponentDrawMesh::add_to_owner (ObjectBase *owner)
{
    ComponentBase::add_to_owner(owner);
    
    World *w = owner->world();

    w->register_for_draw(owner, make_callback(this, &type::draw));
}

void ComponentDrawMesh::remove_from_owner (void)
{
    World *w = owner()->world();

    w->unregister_for_draw(owner(), make_callback(this, &type::draw));

    ComponentBase::remove_from_owner();
}

//==============================================================================
//==============================================================================

} // DT3

