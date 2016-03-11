//==============================================================================
///	
///	File: ComponentDrawFillImagePlane.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentDrawFillImagePlane.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "MaterialResource.hpp"
#include "World.hpp"
#include "PlaceableObject.hpp"
#include "DrawBatcher.hpp"
#include "ArchivePropertyReaderWriter.hpp"
#include "ConsoleStream.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentDrawFillImagePlane,"Drawing","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentDrawFillImagePlane)

IMPLEMENT_PLUG_INFO(_material)
IMPLEMENT_PLUG_INFO(_color)
IMPLEMENT_PLUG_INFO(_fill)
IMPLEMENT_PLUG_INFO(_angle)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentDrawFillImagePlane)
        
    PLUG_INIT(_material, "Material")
		.setInput(true);
        
    PLUG_INIT(_color, "Color")
		.setInput(true);
        
    PLUG_INIT(_fill, "Fill")
		.setInput(true);
        
    PLUG_INIT(_angle, "Angle")
		.setInput(true);
        
END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentDrawFillImagePlane::ComponentDrawFillImagePlane (void)
    :   _material           (PLUG_INFO(_material)),
        _color              (PLUG_INFO(_color), Color(1.0F,1.0F,1.0F,1.0F)),
        _fill               (PLUG_INFO(_fill), 0.5F),
        _angle              (PLUG_INFO(_angle), 0.0F),
        _aspect             (1.0F)
{

}
		
ComponentDrawFillImagePlane::ComponentDrawFillImagePlane (const ComponentDrawFillImagePlane &rhs)
    :   ComponentBase       (rhs),
        _material           (rhs._material),
        _color              (rhs._color),
        _aspect             (rhs._aspect),
        _fill               (rhs._fill),
        _angle              (rhs._angle)
{

}

ComponentDrawFillImagePlane & ComponentDrawFillImagePlane::operator = (const ComponentDrawFillImagePlane &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        
        _material = rhs._material;
        _aspect = rhs._aspect;
        _color = rhs._color;
        _fill = rhs._fill;
        _angle = rhs._angle;
    }
    return (*this);
}
			
ComponentDrawFillImagePlane::~ComponentDrawFillImagePlane (void)
{

}

//==============================================================================
//==============================================================================

void ComponentDrawFillImagePlane::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentDrawFillImagePlane::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
        		
    if (archive->isA(ArchivePropertyReaderWriter::kind()))
        *archive << ARCHIVE_DATA_ACCESSORS("Material", ComponentDrawFillImagePlane::getMaterial, ComponentDrawFillImagePlane::setMaterialProp, DATA_PERSISTENT | DATA_SETTABLE);
	else
        *archive << ARCHIVE_DATA_ACCESSORS("Material", ComponentDrawFillImagePlane::getMaterial, ComponentDrawFillImagePlane::setMaterial, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_PLUG(_color, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_fill, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_angle, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_aspect, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

void ComponentDrawFillImagePlane::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	
    if (archive->isA(ArchivePropertyReaderWriter::kind()))
        *archive << ARCHIVE_DATA_ACCESSORS("Material", ComponentDrawFillImagePlane::getMaterial, ComponentDrawFillImagePlane::setMaterialProp, DATA_PERSISTENT | DATA_SETTABLE);
	else
        *archive << ARCHIVE_DATA_ACCESSORS("Material", ComponentDrawFillImagePlane::getMaterial, ComponentDrawFillImagePlane::setMaterial, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_PLUG(_color, DATA_PERSISTENT | DATA_SETTABLE);	
    *archive << ARCHIVE_PLUG(_fill, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_angle, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_aspect, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

std::shared_ptr<MaterialResource> ComponentDrawFillImagePlane::getMaterial (void) const
{
    return _material;
}

void ComponentDrawFillImagePlane::setMaterial (std::shared_ptr<MaterialResource> material)
{
    _material = material;
}

void ComponentDrawFillImagePlane::setMaterialProp (std::shared_ptr<MaterialResource> material)
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

void ComponentDrawFillImagePlane::draw (CameraObject* camera)
{
    if (_material->isNull())
        return;
        
    PlaceableObject *placeable = checkedCast<PlaceableObject*>(getOwner());
    if (!placeable)
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
    
    DTfloat length = ( (_fill * 1.0F) + ((1.0F - _fill) * -1.0F) );
    Vector2 axis( std::cos(_angle), std::sin(_angle) );
    
    Vector2 orig[8] = {
        Vector2(-1.0F*width,1.0F*height),
        Vector2(-1.0F*width,-1.0F*height),
        Vector2(-1.0F*width,-1.0F*height),
        Vector2(1.0F*width,-1.0F*height),
        Vector2(1.0F*width,-1.0F*height),
        Vector2(1.0F*width,1.0F*height),
        Vector2(1.0F*width,1.0F*height),
        Vector2(-1.0F*width,1.0F*height)
    };

    Texcoord2 orig_tc[8] = {
        Texcoord2(0.0F,1.0F),
        Texcoord2(0.0F,0.0F),
        Texcoord2(0.0F,0.0F),
        Texcoord2(1.0F,0.0F),
        Texcoord2(1.0F,0.0F),
        Texcoord2(1.0F,1.0F),
        Texcoord2(1.0F,1.0F),
        Texcoord2(0.0F,1.0F)
    };
    
    DTboolean active[8] = { true, true, true, true, true, true, true, true };
    
    for (DTuint i = 0; i < 8; i += 2) {
    
        Vector2 &pa = orig[i];
        Vector2 &pb = orig[i+1];
        
        Texcoord2 &ta = orig_tc[i];
        Texcoord2 &tb = orig_tc[i+1];
        
        DTboolean &pa_on = active[i];
        DTboolean &pb_on = active[i+1];
    
        DTfloat da,db;
        
        da = Vector2::dot(axis, pa);
        db = Vector2::dot(axis, pb);
        
        DTfloat la = da - length;
        DTfloat lb = db - length;
        
        pa_on = (la < 0.0F);
        pb_on = (lb < 0.0F);
                
        if (pa_on != pb_on) {
            DTfloat t = (length - da) / (db - da);
                        
            if (t > 0.0F && t < 1.0F) {
                Vector2 pp = (pb - pa) * t + pa;
                Texcoord2 tp = (tb - ta) * t + ta;
                
                if (la > 0.0)   {   pa = pp;     ta = tp;     pa_on = true;  }
                else            {   pb = pp;     tb = tp;     pb_on = true;  }
            }
            
        }
    
    }
    
    std::vector<Vector2>    p;
    std::vector<Texcoord2>  t;

    for (DTuint i = 0; i < 8; ++i) {
        if (active[i]) {
            p.pushBack(orig[i]);
            t.pushBack(orig_tc[i]);
        }
    }
    
    DrawBatcher b;
    b.batchBegin(_material->get(), placeable->getTransform(), DrawBatcher::BATCH_TRI_POLY, DrawBatcher::FMT_V | DrawBatcher::FMT_T1 | DrawBatcher::FMT_C);

    Color c(_color);
    
    if (p.size() > 0) {
        for (DTuint i = 1; i < p.size() - 1; ++i) {
            b.vertex(Vector3(p[0]), Texcoord2(t[0]), c);
            b.vertex(Vector3(p[i]), Texcoord2(t[i]), c);
            b.vertex(Vector3(p[i+1]), Texcoord2(t[i+1]), c);
        }
    }
    
    b.batchEnd();
    
}

//==============================================================================
//==============================================================================

void ComponentDrawFillImagePlane::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    World *w = getOwner()->getWorld();

    w->registerForDraw(getOwner(), makeCallback(this, &type::draw));
}

void ComponentDrawFillImagePlane::removeFromOwner (void)
{
    World *w = getOwner()->getWorld();

    w->unregisterForDraw(getOwner(), makeCallback(this, &type::draw));

    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

} // DT3

