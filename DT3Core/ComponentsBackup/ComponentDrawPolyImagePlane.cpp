//==============================================================================
///	
///	File: ComponentDrawPolyImagePlane.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentDrawPolyImagePlane.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "MaterialResource.hpp"
#include "World.hpp"
#include "PlaceableObject.hpp"
#include "DrawBatcher.hpp"
#include "ConsoleStream.hpp"
#include "ArchivePropertyReaderWriter.hpp"
#include "ShaderResource.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentDrawPolyImagePlane,"Drawing","EdManipComponentDrawPolyImagePlane")
IMPLEMENT_PLUG_NODE(ComponentDrawPolyImagePlane)
IMPLEMENT_POOL_ALLOCATOR(ComponentDrawPolyImagePlaneHull)

IMPLEMENT_PLUG_INFO(_material)
IMPLEMENT_PLUG_INFO(_color)
IMPLEMENT_PLUG_INFO(_flip_horz)
IMPLEMENT_PLUG_INFO(_flip_vert)

IMPLEMENT_PLUG_INFO(_p0)
IMPLEMENT_PLUG_INFO(_p1)
IMPLEMENT_PLUG_INFO(_p2)
IMPLEMENT_PLUG_INFO(_p3)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentDrawPolyImagePlane)
        
    PLUG_INIT(_material, "Material")
		.setInput(true);
        
    PLUG_INIT(_color, "Color")
		.setInput(true);
        
    PLUG_INIT(_flip_horz, "Flip_Horz")
		.setInput(true);
        
    PLUG_INIT(_flip_vert, "Flip_Vert")
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

ComponentDrawPolyImagePlaneHull::ComponentDrawPolyImagePlaneHull (void)
	:	_polygon_object     (NULL)
{

}
		
ComponentDrawPolyImagePlaneHull::ComponentDrawPolyImagePlaneHull (const ComponentDrawPolyImagePlaneHull &rhs)
	:	_points             (rhs._points),
		_polygon_object     (rhs._polygon_object)
{   

}

ComponentDrawPolyImagePlaneHull & ComponentDrawPolyImagePlaneHull::operator = (const ComponentDrawPolyImagePlaneHull &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		_points	= rhs._points;
		_polygon_object = rhs._polygon_object;
    }
    return (*this);
}
			
ComponentDrawPolyImagePlaneHull::~ComponentDrawPolyImagePlaneHull (void)
{

}

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentDrawPolyImagePlane::ComponentDrawPolyImagePlane (void)
    :   _material           (PLUG_INFO(_material)),
        _color              (PLUG_INFO(_color), Color(1.0F,1.0F,1.0F,1.0F)),
        _aspect             (1.0F),
        _flip_horz          (PLUG_INFO(_flip_horz), false),
        _flip_vert          (PLUG_INFO(_flip_vert), false),
        _p0                 (PLUG_INFO(_p0), 0.0F),
        _p1                 (PLUG_INFO(_p1), 0.0F),
        _p2                 (PLUG_INFO(_p2), 0.0F),
        _p3                 (PLUG_INFO(_p3), 0.0F),
        _params_pos         (-1)
{  
	_poly_points.resize(4);
	
	_poly_points[0] = ComponentDrawPolyImagePlanePoint(Vector2(-1.0F,-1.0F),Texcoord2(-1.0F,-1.0F));
	_poly_points[1] = ComponentDrawPolyImagePlanePoint(Vector2(1.0F,-1.0F),Texcoord2(-1.0F,-1.0F));
	_poly_points[2] = ComponentDrawPolyImagePlanePoint(Vector2(1.0F,1.0F),Texcoord2(-1.0F,-1.0F));
	_poly_points[3] = ComponentDrawPolyImagePlanePoint(Vector2(-1.0F,1.0F),Texcoord2(-1.0F,-1.0F));

	calcHulls();
}
		
ComponentDrawPolyImagePlane::ComponentDrawPolyImagePlane (const ComponentDrawPolyImagePlane &rhs)
    :   ComponentBase       (rhs),
        _material           (rhs._material),
        _color              (rhs._color),
        _aspect             (rhs._aspect),
        _flip_horz          (rhs._flip_horz),
        _flip_vert          (rhs._flip_vert),
        _p0                 (rhs._p0),
        _p1                 (rhs._p1),
        _p2                 (rhs._p2),
        _p3                 (rhs._p3),
		_poly_points		(rhs._poly_points),
        _params_pos         (-1)
{   
	calcHulls();

}

ComponentDrawPolyImagePlane & ComponentDrawPolyImagePlane::operator = (const ComponentDrawPolyImagePlane &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        
        _material = rhs._material;
        _aspect = rhs._aspect;
        _color = rhs._color;
        
        _flip_horz = rhs._flip_horz;
        _flip_vert = rhs._flip_vert;
        
        _p0 = rhs._p0;
        _p1 = rhs._p1;
        _p2 = rhs._p2;
        _p3 = rhs._p3;

		_poly_points = rhs._poly_points;
        _params_pos = rhs._params_pos;
        calcHulls();
    }
    return (*this);
}
			
ComponentDrawPolyImagePlane::~ComponentDrawPolyImagePlane (void)
{
	for (auto i = _hulls.begin(); i != _hulls.end(); ++i)
		RELEASE(*i);
}

//==============================================================================
//==============================================================================

void ComponentDrawPolyImagePlane::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentDrawPolyImagePlane::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
        		
    if (archive->isA(ArchivePropertyReaderWriter::kind()))
        *archive << ARCHIVE_DATA_ACCESSORS("Material", ComponentDrawPolyImagePlane::getMaterial, ComponentDrawPolyImagePlane::setMaterialProp, DATA_PERSISTENT | DATA_SETTABLE);
	else
        *archive << ARCHIVE_DATA_ACCESSORS("Material", ComponentDrawPolyImagePlane::getMaterial, ComponentDrawPolyImagePlane::setMaterial, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_PLUG(_color, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_aspect, DATA_PERSISTENT | DATA_SETTABLE);
    
    if (archive->getVersion() >= 1345) {
        *archive << ARCHIVE_PLUG(_flip_horz, DATA_PERSISTENT | DATA_SETTABLE);
        *archive << ARCHIVE_PLUG(_flip_vert, DATA_PERSISTENT | DATA_SETTABLE);
    }
        
    if (archive->getVersion() >= 1351) {
        *archive << ARCHIVE_PLUG(_p0, DATA_PERSISTENT | DATA_SETTABLE);
        *archive << ARCHIVE_PLUG(_p1, DATA_PERSISTENT | DATA_SETTABLE);
        *archive << ARCHIVE_PLUG(_p2, DATA_PERSISTENT | DATA_SETTABLE);
        *archive << ARCHIVE_PLUG(_p3, DATA_PERSISTENT | DATA_SETTABLE);
    }

	DTsize pointCount;
	*archive << ARCHIVE_DATA(pointCount,DATA_PERSISTENT);
	_poly_points.resize(pointCount);
	
	for (DTuint i = 0; i < _poly_points.size(); ++i) {
		*archive << ARCHIVE_DATA_RAW(_poly_points[i].position,DATA_PERSISTENT);
		*archive << ARCHIVE_DATA_RAW(_poly_points[i].texcoord,DATA_PERSISTENT);
	}


    archive->pop_domain ();
}

void ComponentDrawPolyImagePlane::archive_read_done   (void)
{		
	ComponentBase::archive_read_done ();
	
	calcHulls();
}

void ComponentDrawPolyImagePlane::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	
    if (archive->isA(ArchivePropertyReaderWriter::kind()))
        *archive << ARCHIVE_DATA_ACCESSORS("Material", ComponentDrawPolyImagePlane::getMaterial, ComponentDrawPolyImagePlane::setMaterialProp, DATA_PERSISTENT | DATA_SETTABLE);
	else
        *archive << ARCHIVE_DATA_ACCESSORS("Material", ComponentDrawPolyImagePlane::getMaterial, ComponentDrawPolyImagePlane::setMaterial, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_PLUG(_color, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_aspect, DATA_PERSISTENT | DATA_SETTABLE);

    *archive << ARCHIVE_PLUG(_flip_horz, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_flip_vert, DATA_PERSISTENT | DATA_SETTABLE);
    
    *archive << ARCHIVE_PLUG(_p0, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_p1, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_p2, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_p3, DATA_PERSISTENT | DATA_SETTABLE);

	DTsize pointCount = _poly_points.size();
	*archive << ARCHIVE_DATA(pointCount,DATA_PERSISTENT);
	
	for (DTuint i = 0; i < _poly_points.size(); ++i) {
		*archive << ARCHIVE_DATA_RAW(_poly_points[i].position,DATA_PERSISTENT);
		*archive << ARCHIVE_DATA_RAW(_poly_points[i].texcoord,DATA_PERSISTENT);
	}

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

std::shared_ptr<MaterialResource> ComponentDrawPolyImagePlane::getMaterial (void) const
{
    return _material;
}

void ComponentDrawPolyImagePlane::setMaterial (std::shared_ptr<MaterialResource> material)
{
    if (material.isValid()) {
        _params_pos = material->getShader()->getParameterIndex("uParams");
    } else {
        _params_pos = -1;
    }

    _material = material;
}

void ComponentDrawPolyImagePlane::setMaterialProp (std::shared_ptr<MaterialResource> material)
{
    _material = material;
    
#ifdef DT3_EDITOR

    //
    // Try to automatically set the aspect ratio
    //

    if (_material->isValid()) {
        
        // Take a stab at the aspect ratio
        (*_material)->setCurrentUnit(0);
        
        Vector3 scale = (*_material)->getScale();
        if (scale.y > 0.0F) 
            setAspect(scale.x/scale.y);
    }
#endif
}

//==============================================================================
//==============================================================================

void ComponentDrawPolyImagePlane::calcHulls (void)
{	
	_hulls.clear();
	
	ComponentDrawPolyImagePlaneHull hull;
	for (DTuint i = 0; i < _poly_points.size(); ++i) {
		DTint point;
		point = i;
		
		hull._points.pushBack(point);
	}
	
	calcHullsRecursive (hull);		
	
}

DTboolean ComponentDrawPolyImagePlane::isConvex (ComponentDrawPolyImagePlaneHull &hull)
{	
	for (DTuint j = 0; j < hull._points.size(); ++j) {
		Vector2 pa = _poly_points[hull._points[j]].position;

		for (DTuint i = 0; i < hull._points.size(); ++i) {
			DTint i_next = (i+1) % hull._points.size();
			
			Vector2 pb = _poly_points[hull._points[i]].position;
			Vector2 pc = _poly_points[hull._points[i_next]].position;
			
			DTfloat curl = Vector2::perpDot(pb - pa, pc - pa);
			if (curl < 0.0F)
				return false;
		}
	}

	return true;
}

DTboolean ComponentDrawPolyImagePlane::intersect(Vector2 &p0, Vector2 &p1, Vector2 &p2, Vector2 &p3)
{
	const DTfloat EPSILON = 0.0001F;
	const DTfloat ONE_MINUS_EPSILON = 1.0F - EPSILON;
	
	DTfloat denom = ((p3.y - p2.y)*(p1.x - p0.x)) - ((p3.x - p2.x)*(p1.y - p0.y));
	DTfloat nume_a = ((p3.x - p2.x)*(p0.y - p2.y)) - ((p3.y - p2.y)*(p0.x - p2.x));
	DTfloat nume_b = ((p1.x - p0.x)*(p0.y - p2.y)) - ((p1.y - p0.y)*(p0.x - p2.x));

	if(std::abs(denom) < EPSILON)
		return false;

	DTfloat ua = nume_a / denom;
	DTfloat ub = nume_b / denom;

	if (ua > EPSILON && ua < ONE_MINUS_EPSILON && ub > EPSILON && ub < ONE_MINUS_EPSILON)
		return true;

	return false;
}

DTboolean ComponentDrawPolyImagePlane::isEmpty (ComponentDrawPolyImagePlaneHull &hull)
{	
	DTuint i,j;
	
	for (j = 0; j < _poly_points.size(); ++j) {
		DTint j_next = (j+1) % _poly_points.size();

		Vector2 pja = _poly_points[j].position;
		Vector2 pjb = _poly_points[j_next].position;
			
		for (i = 0; i < hull._points.size(); ++i) {
			DTint i_next = (i+1) % hull._points.size();
			
			Vector2 pia = _poly_points[hull._points[i]].position;
			Vector2 pib = _poly_points[hull._points[i_next]].position;
			
			if (intersect(pja,pjb,pia,pib))
				return false;
		}
	}

	
	for (j = 0; j < _poly_points.size(); ++j) {

		for (i = 0; i < hull._points.size(); ++i) {
			DTint i_next = (i+1) % hull._points.size();
			
			Vector2 pa = _poly_points[hull._points[i]].position;
			Vector2 pb = _poly_points[hull._points[i_next]].position;
			
			DTfloat curl = Vector2::perpDot(pb - pa, _poly_points[j].position - pa);
			if (curl <= 0.0F)
				break;
		}
		
		if (i == hull._points.size())
			return false;
	}

	return true;
}

void ComponentDrawPolyImagePlane::calcHullsRecursive (ComponentDrawPolyImagePlaneHull &hull)
{
	ComponentDrawPolyImagePlaneHull inside_points;
	ComponentDrawPolyImagePlaneHull outside_points;
		
	for (DTuint i = 0; i < hull._points.size(); ++i) {
		inside_points._points.pushBack(hull._points[i]);

		// Point inside
		if (inside_points._points.size() < 2 || ( isConvex(inside_points) && isEmpty(inside_points) )) {
			// If ending outside _points
			if (outside_points._points.size() > 0) {
				outside_points._points.pushBack(hull._points[i]);
				
				if (outside_points._points.size() >= hull._points.size())
					return;

				calcHullsRecursive (outside_points);
				outside_points._points.clear();
			}
					
		// Point outside
		} else {
			inside_points._points.popBack();	// Mistaken, point was actually outside
			
			if (outside_points._points.size() == 0)
				outside_points._points.pushBack(hull._points[i-1]);	// Last inside point

			outside_points._points.pushBack(hull._points[i]);
		}
		
	}
	
	// Special case last point being outside
	if (outside_points._points.size() > 0)	{
		outside_points._points.pushBack(hull._points[0]);
		
		if (outside_points._points.size() >= hull._points.size())
			return;
		
		calcHullsRecursive (outside_points);
	}

	if (inside_points._points.size() < 3)
		return;

	inside_points._polygon_object = this;
	_hulls.pushBack(inside_points.clone());
}

//==============================================================================
//==============================================================================

void ComponentDrawPolyImagePlane::calcDefaultTexcoords (void)
{	        
	// Calculate texcoords
	for (DTuint i = 0; i < _poly_points.size(); ++i) {
		Vector2 &pt = _poly_points[i].position;
		Texcoord2 &tx = _poly_points[i].texcoord;
		
		tx.s = (pt.x + 1.0F) / 2.0F;
		tx.t = (pt.y + 1.0F) / 2.0F;
    }

}

//==============================================================================
//==============================================================================

void ComponentDrawPolyImagePlane::draw (CameraObject* camera)
{    
    if (_material->isNull())
        return;
        
    PlaceableObject *placeable = checkedCast<PlaceableObject*>(getOwner());
    if (!placeable)
        return;
    
    if (getColor().getA() <= 0)
        return;

    DTfloat width, height;
    if (_aspect > 1.0F) {
        width = 1.0F;
        height = 1.0F / _aspect;
        
    } else if (_aspect < 1.0F) {
        width = _aspect;
        height = 1.0F;

    } else {
        width = 1.0F;
        height = 1.0F;

    }
    
    if (_flip_horz) width *= -1.0F;
    if (_flip_vert) height *= -1.0F;
            
    Matrix4 transform = placeable->getTransform() * Matrix4(    width,  0.0F,   0.0F,   0.0F,
                                                                0.0F,   height, 0.0F,   0.0F,
                                                                0.0F,   0.0F,   1.0F,   0.0F,
                                                                0.0F,   0.0F,   0.0F,   1.0F);
    Color color = getColor();

    if (_params_pos >= 0)
        (*_material)->getShader()->setParameterValue(_params_pos,0, _p0,_p1,_p2,_p3);
                
	DrawBatcher b;
	b.batchBegin (_material->get(), transform, DrawBatcher::BATCH_TRI_POLY, DrawBatcher::FMT_V | DrawBatcher::FMT_T1 | DrawBatcher::FMT_C);

	for (DTuint h = 0; h < _hulls.size(); ++h) {
		ComponentDrawPolyImagePlaneHull &hull = *(_hulls[h]);
				
		for (DTint p = 1; p < hull._points.size()-1; ++p) {
			DTint p_next = p + 1;
		
			Vector3 pt0 = Vector3(_poly_points[hull._points[0]].position);			
			Vector3 pt1 = Vector3(_poly_points[hull._points[p]].position);			
			Vector3 pt2 = Vector3(_poly_points[hull._points[p_next]].position);
            
			Texcoord2 tc0 = _poly_points[hull._points[0]].texcoord;			
			Texcoord2 tc1 = _poly_points[hull._points[p]].texcoord;			
			Texcoord2 tc2 = _poly_points[hull._points[p_next]].texcoord;

            b.vertex( pt0, tc0, color );
            b.vertex( pt1, tc1, color );
            b.vertex( pt2, tc2, color );
		}
		
	}

	b.batchEnd();
	b.flush();

    
}

//==============================================================================
//==============================================================================

void ComponentDrawPolyImagePlane::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    World *w = getOwner()->getWorld();

    w->registerForDraw(getOwner(), makeCallback(this, &type::draw));
}

void ComponentDrawPolyImagePlane::removeFromOwner (void)
{
    World *w = getOwner()->getWorld();

    w->unregisterForDraw(getOwner(), makeCallback(this, &type::draw));

    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

} // DT3

