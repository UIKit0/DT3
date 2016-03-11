//==============================================================================
///	
///	File: ComponentDrawShape.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentDrawShape.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "TextureResource.hpp"
#include "FontResource.hpp"
#include "World.hpp"
#include "PlaceableObject.hpp"
#include "ShaderResource.hpp"

#include "System.hpp"
#include "DeviceGraphics.hpp"
#include "DrawBatcher.hpp"
#include "DrawBatcherQuads.hpp"
#include "Perlin.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentDrawShape,"Drawing","EdManipComponentDrawShape")
IMPLEMENT_PLUG_NODE(ComponentDrawShape)

IMPLEMENT_PLUG_INFO(_material)
IMPLEMENT_PLUG_INFO(_edge_material)
IMPLEMENT_PLUG_INFO(_color)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentDrawShape)
                        
    PLUG_INIT(_material, "Material")
		.setInput(true);

    PLUG_INIT(_edge_material, "Edge_Material")
		.setInput(true);

    PLUG_INIT(_color, "Color")
		.setInput(true);
    
END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentDrawShape::ComponentDrawShape (void)
    :   _material               (PLUG_INFO(_material)),
        _edge_material          (PLUG_INFO(_edge_material)),
        _color                  (PLUG_INFO(_color), Color(1.0F,1.0F,1.0F,1.0F)),
        _texcoord_scale         (1.0F),
        _edge_texcoord_scale    (1.0F),
        _follow_contour         (false),
        _noise_scale            (0.0F),
        _noise_freq             (2.0F),
        _edge_thickness         (0.01F),
        _use_bezier             (true),
        _subdivisions           (25),
        _needs_recalculate      (true)
{

}
		
ComponentDrawShape::ComponentDrawShape (const ComponentDrawShape &rhs)
    :   ComponentBase           (rhs),
        _material               (rhs._material),
        _edge_material          (rhs._edge_material),
        _color                  (rhs._color),
        _texcoord_scale         (rhs._texcoord_scale),
        _edge_texcoord_scale    (rhs._edge_texcoord_scale),
        _follow_contour         (rhs._follow_contour),
        _noise_scale            (rhs._noise_scale),
        _noise_freq             (rhs._noise_freq),
        _edge_thickness         (rhs._edge_thickness),
        _use_bezier             (rhs._use_bezier),
        _subdivisions           (rhs._subdivisions),
        _vertices               (rhs._vertices),
        _needs_recalculate      (true)
{

}

ComponentDrawShape & ComponentDrawShape::operator = (const ComponentDrawShape &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
                
        _material = rhs._material;
        _edge_material = rhs._edge_material;
        _color = rhs._color;
        _texcoord_scale = rhs._texcoord_scale;
        _edge_texcoord_scale = rhs._edge_texcoord_scale;
        _follow_contour = rhs._follow_contour;
        _noise_scale = rhs._noise_scale;
        _noise_freq = rhs._noise_freq;
        _edge_thickness = rhs._edge_thickness;
        _use_bezier = rhs._use_bezier;
        _subdivisions = rhs._subdivisions;
        _vertices = rhs._vertices;
        
        _needs_recalculate = rhs._needs_recalculate;
    }
    return (*this);
}
			
ComponentDrawShape::~ComponentDrawShape (void)
{

}

//==============================================================================
//==============================================================================

void ComponentDrawShape::initialize (void)
{
	ComponentBase::initialize();
    
    _mask_material.setBlendEnable(false);
    _mask_material.setDepthEnable(false);
    _mask_material.setCullMode(DT3GL_CULL_NONE);
    _mask_material.setRenderTargetWriteMaskR(false);
    _mask_material.setRenderTargetWriteMaskG(false);
    _mask_material.setRenderTargetWriteMaskB(false);
    _mask_material.setRenderTargetWriteMaskA(false);
    _mask_material.setStencilEnable(true);
    _mask_material.setStencilReadMask(0xFFFFFFFF);
    _mask_material.setStencilWriteMask(0xFFFFFFFF);
    _mask_material.setFrontFaceStencilFailOp(DT3GL_STENCILOP_INVERT);
    _mask_material.setFrontFaceStencilDepthFailOp(DT3GL_STENCILOP_INVERT);
    _mask_material.setFrontFaceStencilPassOp(DT3GL_STENCILOP_INVERT);
    _mask_material.setFrontFaceStencilFunc(DT3GL_COMPARE_ALWAYS);
    _mask_material.setBackFaceStencilFailOp(DT3GL_STENCILOP_INVERT);
    _mask_material.setBackFaceStencilDepthFailOp(DT3GL_STENCILOP_INVERT);
    _mask_material.setBackFaceStencilPassOp(DT3GL_STENCILOP_INVERT);
    _mask_material.setBackFaceStencilFunc(DT3GL_COMPARE_ALWAYS);
	_mask_material.setShader(ShaderResource::getShader(FilePath("{SYS_MASK_SHADER}")));
    
    if (_vertices.size() < 3) {
        setNumVertices(3);
        
        setVertexPoint (0, Vector2(0.0F,0.0F));
        setVertexPointTangent (0, Vector2(1.0F,0.0F));

        setVertexPoint (1, Vector2(1.0F,0.0F));
        setVertexPointTangent (1, Vector2(1.0F,0.0F));

        setVertexPoint (2, Vector2(1.0F,1.0F));
        setVertexPointTangent (2, Vector2(1.0F,0.0F));
    }
}

//==============================================================================
//==============================================================================

void ComponentDrawShape::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
        		    
	*archive << ARCHIVE_PLUG(_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_color, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_texcoord_scale, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_follow_contour, DATA_PERSISTENT | DATA_SETTABLE);
    
	*archive << ARCHIVE_PLUG(_edge_material, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_DATA(_edge_thickness, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_edge_texcoord_scale, DATA_PERSISTENT | DATA_SETTABLE);
    
	*archive << ARCHIVE_DATA(_noise_scale, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_noise_freq, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_use_bezier, DATA_PERSISTENT | DATA_SETTABLE);
    
	*archive << ARCHIVE_DATA_ACCESSORS("Num_Vertices", ComponentDrawShape::getNumVertices, ComponentDrawShape::setNumVertices, DATA_PERSISTENT | DATA_SETTABLE);

    for (DTsize i = 0; i < _vertices.size(); ++i) {
        *archive << ARCHIVE_DATA_RAW(_vertices[i].point, DATA_PERSISTENT);
        *archive << ARCHIVE_DATA_RAW(_vertices[i].tangent, DATA_PERSISTENT);
    }

    archive->pop_domain ();
    
    _needs_recalculate = true;
}

void ComponentDrawShape::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	    
	*archive << ARCHIVE_PLUG(_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_color, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_texcoord_scale, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_follow_contour, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_PLUG(_edge_material, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_DATA(_edge_thickness, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_edge_texcoord_scale, DATA_PERSISTENT | DATA_SETTABLE);
    
	*archive << ARCHIVE_DATA(_noise_scale, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_noise_freq, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_use_bezier, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA_ACCESSORS("Num_Vertices", ComponentDrawShape::getNumVertices, ComponentDrawShape::setNumVertices, DATA_PERSISTENT | DATA_SETTABLE);

    for (DTsize i = 0; i < _vertices.size(); ++i) {
        *archive << ARCHIVE_DATA_RAW(_vertices[i].point, DATA_PERSISTENT);
        *archive << ARCHIVE_DATA_RAW(_vertices[i].tangent, DATA_PERSISTENT);
    }

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentDrawShape::calculateCurve (void)
{
    _min_x = std::numeric_limits<DTfloat>::infinity();
    _max_x = -std::numeric_limits<DTfloat>::infinity();
    _min_y = std::numeric_limits<DTfloat>::infinity();
    _max_y = -std::numeric_limits<DTfloat>::infinity();
    
    //
    // Edge points
    //
        
    _curve.resize(_subdivisions * getNumVertices());
    
    // Calculate curves
    DTint num = 0;
    
    for (DTint i = 0; i < getNumVertices(); ++i) {
        DTint i_plus_1 = MoreMath::wrapMod(i+1, (DTint) getNumVertices() );
                    
        for (DTint j = 0; j < _subdivisions; ++j) {
            DTfloat t = (DTfloat) j / (DTfloat) _subdivisions;
            
            Vector2 p0;
            
            if (_use_bezier) {
            
                p0 = MoreMath::spline(  getVertexPoint(i),
                                        getVertexPointTangent(i),
                                        getVertexPoint(i_plus_1),
                                        getVertexPointTangent(i_plus_1),
                                        t);
            } else {
                p0 = (getVertexPoint(i_plus_1) - getVertexPoint(i)) * t + getVertexPoint(i);
            }
            
            DTfloat p0_dx = Perlin::noise2D (p0.x * _noise_freq, p0.y * _noise_freq);
            DTfloat p0_dy = Perlin::noise2D (p0.y * _noise_freq, p0.x * _noise_freq);
            
            p0 += Vector2(p0_dx,p0_dy) * _noise_scale;
            
            _curve[num++].point = p0;

            // Build a bounding box
            _min_x = min2(p0.x, _min_x);
            _max_x = max2(p0.x, _max_x);
            _min_y = min2(p0.y, _min_y);
            _max_y = max2(p0.y, _max_y);
            
        }
        
    }
    
    // Sum perimeter and get perps
    _perimeter = 0.0F;
    
    for (DTint i = 0; i < _curve.size(); ++i) {
    
        DTint i_plus_1 = MoreMath::wrapMod(i+1, (DTint) _curve.size());
        DTint i_minus_1 = MoreMath::wrapMod(i-1, (DTint) _curve.size());
        
        Vector2 diff = _curve[i_plus_1].point - _curve[i_minus_1].point;
        DTfloat dist = diff.abs();
        
        _perimeter += dist * _edge_texcoord_scale;
        
        _curve[i].perp = diff.normalized().perped() * _edge_thickness;
        _curve[i].dist = dist * _edge_texcoord_scale;
    }


    //
    // Use regression analysis to build a polynomial that fits the points
    // we'll use it for some neat effects later.
    //

    // Build an array of data to pass to regression routine
    std::vector<Vector2> data;
    FOR_EACH(i,_curve) {
        data.pushBack(i->point);
    }
        
    MoreMath::regression (data,_a,_b,_c,_d);
}

//==============================================================================
//==============================================================================

void ComponentDrawShape::getPolynomialCoeffs (DTfloat &a, DTfloat &b, DTfloat &c, DTfloat &d)
{
    a = _a;
    b = _b;
    c = _c;
    d = _d;
}

//==============================================================================
//==============================================================================

void ComponentDrawShape::draw (CameraObject* camera)
{
    if (_needs_recalculate) {
        calculateCurve();
        _needs_recalculate = false;
    }

    if (_material->isNull())
        return;
        
    if (getColor().getA() <= 0)
        return;
        
    PlaceableObject *placeable = checkedCast<PlaceableObject*>(getOwner());
    if (!placeable)
        return;
    

    //
    // Draw poly mask
    //

    System::getRenderer()->clearStencilValue(0);
    System::getRenderer()->clearViewport(false, false, true);
    
    // Draw curves
    for (DTint i = 0; i < _curve.size(); ++i) {
        DTint i_plus_1 = MoreMath::wrapMod(i+1, (DTint) _curve.size());
            
        DrawBatcher b;
        b.batchBegin(&_mask_material, placeable->getTransform(), DrawBatcher::BATCH_TRI_POLY, DrawBatcher::FMT_V);
            
        b.vertex(Vector3(0.0F,0.0F,0.0F));
        b.vertex(Vector3(_curve[i].point));
        b.vertex(Vector3(_curve[i_plus_1].point));
        
        b.batchEnd();
        b.flush();

    }
    
    //
    // Draw Color
    //
    System::getRenderer()->setStencilRef(0);

    if (_follow_contour) {
        
        const DTfloat STEP = (_max_x - _min_x) / 100.0F;
        const DTfloat MAX_HEIGHT = _max_x - _min_x;
        
        DrawBatcherQuads b;
        b.batchBegin(_material->get(), placeable->getTransform(), DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);

        Color c(_color);

        for (DTfloat x = _min_x; x < _max_x; x += STEP) {
            DTfloat x0 = x;
            DTfloat x1 = x + STEP;
            
            DTfloat y0 = _a + _b*x0 + _c*x0*x0 + _d*x0*x0*x0;
            DTfloat y1 = _a + _b*x1 + _c*x1*x1 + _d*x1*x1*x1;
            
            b.vertex(Vector3(x0,y0-MAX_HEIGHT,0.0F), Texcoord2(x0 * _texcoord_scale,0.5F - _texcoord_scale), c);
            b.vertex(Vector3(x1,y1-MAX_HEIGHT,0.0F), Texcoord2(x1 * _texcoord_scale,0.5F - _texcoord_scale), c);
            b.vertex(Vector3(x1,y1+MAX_HEIGHT,0.0F), Texcoord2(x1 * _texcoord_scale,0.5F + _texcoord_scale), c);
            b.vertex(Vector3(x0,y0+MAX_HEIGHT,0.0F), Texcoord2(x0 * _texcoord_scale,0.5F + _texcoord_scale), c);
        }
        
        b.batchEnd();

    
    } else {
        
        // Simply draw a quad over the masked area
        DrawBatcherQuads b;
        b.batchBegin(_material->get(), placeable->getTransform(), DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);

        Color c(_color);
        
        b.vertex(Vector3(_min_x,_min_y,0.0F), Texcoord2(_min_x * _texcoord_scale,_min_y * _texcoord_scale), c);
        b.vertex(Vector3(_max_x,_min_y,0.0F), Texcoord2(_max_x * _texcoord_scale,_min_y * _texcoord_scale), c);
        b.vertex(Vector3(_max_x,_max_y,0.0F), Texcoord2(_max_x * _texcoord_scale,_max_y * _texcoord_scale), c);
        b.vertex(Vector3(_min_x,_max_y,0.0F), Texcoord2(_min_x * _texcoord_scale,_max_y * _texcoord_scale), c);
        
        b.batchEnd();
    }
    
    
    
    
    //
    //  Draw Edge
    //

    if (_edge_material->isValid()) {

        // Calculate a correction factor so that the texcoords end up lining up
        DTfloat correction = _perimeter / std::floor(_perimeter);

        // Draw
        DrawBatcherQuads b;
        b.batchBegin(_edge_material->get(), placeable->getTransform(), DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1);
                
        for (DTint i = 0; i < _curve.size(); ++i) {
            DTint i_plus_1 = MoreMath::wrapMod(i+1, (DTint) _curve.size());

            b.vertex(Vector3(_curve[i].point - _curve[i].perp),                Texcoord2(correction * _curve[i].dist,         0.0F));
            b.vertex(Vector3(_curve[i_plus_1].point - _curve[i_plus_1].perp),  Texcoord2(correction * _curve[i_plus_1].dist,  0.0F));
            b.vertex(Vector3(_curve[i_plus_1].point + _curve[i_plus_1].perp),  Texcoord2(correction * _curve[i_plus_1].dist,  1.0F));
            b.vertex(Vector3(_curve[i].point + _curve[i].perp),                Texcoord2(correction * _curve[i].dist,         1.0F));
            
        }
        
        b.batchEnd();

    }    

}

//==============================================================================
//==============================================================================

void ComponentDrawShape::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    World *w = getOwner()->getWorld();
    w->registerForDraw(getOwner(), makeCallback(this, &type::draw));
}

void ComponentDrawShape::removeFromOwner (void)
{
    World *w = getOwner()->getWorld();
    w->unregisterForDraw(getOwner(), makeCallback(this, &type::draw));

    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

} // DT3

