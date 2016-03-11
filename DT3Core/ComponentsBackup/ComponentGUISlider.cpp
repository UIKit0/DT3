//==============================================================================
///	
///	File: ComponentGUISlider.cpp
///	Author:			Tod Baudais
///					Copyright (C) 2000-2007. All rights reserved.
///	
///	Date Created:	1/31/2001
///	Changes:		-none-
///	
//==============================================================================

#include "ComponentGUISlider.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "GeometryGroupResource.hpp"
#include "World.hpp"
#include "System.hpp"
#include "DeviceGraphics.hpp"
#include "GUIObject.hpp"
#include "DrawBatcherQuads.hpp"
#include "GUIController.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentGUISlider,"GUIBehaviour","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentGUISlider)

IMPLEMENT_PLUG_INFO(_material)
IMPLEMENT_PLUG_INFO(_thumb_material)
IMPLEMENT_PLUG_INFO(_min_value)
IMPLEMENT_PLUG_INFO(_max_value)
IMPLEMENT_PLUG_INFO(_value)

IMPLEMENT_EVENT_INFO(_value_changed)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentGUISlider)

    PLUG_INIT(_material, "Material")
		.setInput(true);

    PLUG_INIT(_thumb_material, "Thumb_Material")
		.setInput(true);

    PLUG_INIT(_min_value, "Min_Value")
		.setInput(true);

    PLUG_INIT(_max_value, "Max_Value")
		.setInput(true);

    PLUG_INIT(_value, "Value")
		.setOutput(true);

    EVENT_INIT(_value_changed, "Value_Changed")
        .setOutput(true);

END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentGUISlider::ComponentGUISlider (void)
    :   _material                   (PLUG_INFO(_material)),
        _thumb_material             (PLUG_INFO(_thumb_material)),
        _min_value                  (PLUG_INFO(_min_value), 0),
        _max_value                  (PLUG_INFO(_max_value), 100),
        _value                      (PLUG_INFO(_value), 50),
        _value_changed              (EVENT_INFO(_value_changed)),
        _slider_cap_width           (0.004F),
        _slider_height              (0.015F),
        _thumb_width                (0.02F),
        _thumb_height               (0.02F)
{

}
		
ComponentGUISlider::ComponentGUISlider (const ComponentGUISlider &rhs)
    :   ComponentBase               (rhs),
        _material                   (rhs._material),
        _thumb_material             (rhs._thumb_material),
        _min_value                  (rhs._min_value),
        _max_value                  (rhs._max_value),
        _value                      (rhs._value),
        _value_changed              (rhs._value_changed),
        _slider_cap_width           (rhs._slider_cap_width),
        _slider_height              (rhs._slider_height),
        _thumb_width                (rhs._thumb_width),
        _thumb_height               (rhs._thumb_height)
{   

}

ComponentGUISlider & ComponentGUISlider::operator = (const ComponentGUISlider &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        
        _material = rhs._material;
        _thumb_material = rhs._thumb_material;
        
        _min_value = rhs._min_value;
        _max_value = rhs._max_value;
        _value = rhs._value;
        
        _slider_cap_width = rhs._slider_cap_width;
        _slider_height = rhs._slider_height;
        _thumb_width = rhs._thumb_width;
        _thumb_height = rhs._thumb_height;

    }
    return (*this);
}
			
ComponentGUISlider::~ComponentGUISlider (void)
{

}

//==============================================================================
//==============================================================================

void ComponentGUISlider::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentGUISlider::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
    
	*archive << ARCHIVE_PLUG(_material, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_thumb_material, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_min_value, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_max_value, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_value, DATA_PERSISTENT | DATA_SETTABLE);
    
    *archive << ARCHIVE_DATA_ACCESSORS("Cap_Width", ComponentGUISlider::getCapWidth, ComponentGUISlider::setCapWidth, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_DATA_ACCESSORS("Slider_Height", ComponentGUISlider::getSliderHeight, ComponentGUISlider::setSliderHeight, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_DATA_ACCESSORS("Thumb_Width", ComponentGUISlider::getThumbWidth, ComponentGUISlider::setThumbWidth, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_DATA_ACCESSORS("Thumb_Height", ComponentGUISlider::getThumbHeight, ComponentGUISlider::setThumbHeight, DATA_PERSISTENT | DATA_SETTABLE);
    
    archive->pop_domain ();
}

void ComponentGUISlider::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	
	*archive << ARCHIVE_PLUG(_material, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_thumb_material, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_min_value, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_max_value, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_value, DATA_PERSISTENT | DATA_SETTABLE);

    *archive << ARCHIVE_DATA_ACCESSORS("Cap_Width", ComponentGUISlider::getCapWidth, ComponentGUISlider::setCapWidth, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_DATA_ACCESSORS("Slider_Height", ComponentGUISlider::getSliderHeight, ComponentGUISlider::setSliderHeight, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_DATA_ACCESSORS("Thumb_Width", ComponentGUISlider::getThumbWidth, ComponentGUISlider::setThumbWidth, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_DATA_ACCESSORS("Thumb_Height", ComponentGUISlider::getThumbHeight, ComponentGUISlider::setThumbHeight, DATA_PERSISTENT | DATA_SETTABLE);
    
    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentGUISlider::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    GUIObject *gui = checkedCast<GUIObject*>(owner);
    if (gui) {
        gui->getTouchesBeganCallbacks().add(makeCallback(this, &type::touchesBegan));
        gui->getTouchesMovedCallbacks().add(makeCallback(this, &type::touchesMoved));
        gui->getTouchesEndedCallbacks().add(makeCallback(this, &type::touchesEnded));
        gui->getTouchesCancelledCallbacks().add(makeCallback(this, &type::touchesCancelled));

        gui->getPostDrawGUICallbacks().add(makeCallback(this, &type::draw));
    }
}

void ComponentGUISlider::removeFromOwner (void)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (gui) {
        gui->getTouchesBeganCallbacks().remove(makeCallback(this, &type::touchesBegan));
        gui->getTouchesMovedCallbacks().remove(makeCallback(this, &type::touchesMoved));
        gui->getTouchesEndedCallbacks().remove(makeCallback(this, &type::touchesEnded));
        gui->getTouchesCancelledCallbacks().remove(makeCallback(this, &type::touchesCancelled));

        gui->getPostDrawGUICallbacks().remove(makeCallback(this, &type::draw));
    }

    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

void ComponentGUISlider::draw (CameraObject* camera, const Color &parent_color)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;

    MaterialResource *material = _material->get();
    MaterialResource *thumb = _thumb_material->get();
    
    if (gui->getColor().getA() * parent_color.getA() <= 0.0F)
        return;
    
    Matrix4 transform = gui->getDrawTransform();
    Rectangle local_rect = gui->getRectangle();
    
    DTfloat middle_y = (local_rect.getPlusY() + local_rect.getMinusY()) * 0.5F;
    DTfloat aspect = System::getRenderer()->getScreenAspect();
    
    Color c = gui->getColor() * parent_color;
    
    DTfloat thumb_width = getThumbWidth() / aspect;
    DTfloat cap_width = getCapWidth() / aspect;

    // Slider part
    if (material) {
        Rectangle slider_rect;
        
        slider_rect.setMinusX( local_rect.getMinusX() + thumb_width * 0.5F);
        slider_rect.setPlusX( local_rect.getPlusX() - thumb_width * 0.5F);
        slider_rect.setMinusY(middle_y - getSliderHeight() * 0.5F);
        slider_rect.setPlusY(middle_y + getSliderHeight() * 0.5F);
        
        DrawBatcherQuads b;
        b.batchBegin(material, transform, DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);
        
        b.vertex(Vector3(slider_rect.getMinusX(),slider_rect.getMinusY(), 0.0F),                    Texcoord2(0.0F,0.0F),       c);
        b.vertex(Vector3(slider_rect.getMinusX() + cap_width,slider_rect.getMinusY(), 0.0F),    Texcoord2(1.0F/3.0F,0.0F),  c);
        b.vertex(Vector3(slider_rect.getMinusX() + cap_width,slider_rect.getPlusY(), 0.0F),     Texcoord2(1.0F/3.0F,1.0F),  c);
        b.vertex(Vector3(slider_rect.getMinusX(),slider_rect.getPlusY(), 0.0F),                     Texcoord2(0.0F,1.0F),       c);

        b.vertex(Vector3(slider_rect.getMinusX() + cap_width,slider_rect.getMinusY(), 0.0F),    Texcoord2(1.0F/3.0F,0.0F),  c);
        b.vertex(Vector3(slider_rect.getPlusX() - cap_width,slider_rect.getMinusY(), 0.0F),     Texcoord2(2.0F/3.0F,0.0F),  c);
        b.vertex(Vector3(slider_rect.getPlusX() - cap_width,slider_rect.getPlusY(), 0.0F),      Texcoord2(2.0F/3.0F,1.0F),  c);
        b.vertex(Vector3(slider_rect.getMinusX() + cap_width,slider_rect.getPlusY(), 0.0F),     Texcoord2(1.0F/3.0F,1.0F),  c);

        b.vertex(Vector3(slider_rect.getPlusX() - cap_width,slider_rect.getMinusY(), 0.0F),     Texcoord2(2.0F/3.0F,0.0F),  c);
        b.vertex(Vector3(slider_rect.getPlusX(),slider_rect.getMinusY(), 0.0F),                     Texcoord2(1.0F,0.0F),       c);
        b.vertex(Vector3(slider_rect.getPlusX(),slider_rect.getPlusY(), 0.0F),                      Texcoord2(1.0F,1.0F),       c);
        b.vertex(Vector3(slider_rect.getPlusX() - cap_width,slider_rect.getPlusY(), 0.0F),      Texcoord2(2.0F/3.0F,1.0F),  c);

        b.batchEnd();
    }

    if (thumb) {
        Rectangle thumb_rect;
        
        DTfloat t;
        if (_max_value <= _min_value)   t = 0.0F;
        else                            t = (DTfloat) (_value - _min_value) / (DTfloat) (_max_value - _min_value);
        
        DTfloat pos_max = local_rect.getPlusX() - thumb_width * 0.5F;
        DTfloat pos_min = local_rect.getMinusX() + thumb_width * 0.5F;
        
        DTfloat pos = t * (pos_max - pos_min) + pos_min;
        
        thumb_rect.setMinusX( pos - thumb_width * 0.5F );
        thumb_rect.setPlusX( pos + thumb_width * 0.5F );
        thumb_rect.setMinusY(middle_y - getThumbHeight() * 0.5F);
        thumb_rect.setPlusY(middle_y + getThumbHeight() * 0.5F);
        
        DrawBatcherQuads b;
        b.batchBegin(thumb, transform, DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);
        
        b.vertex(Vector3(thumb_rect.getMinusX(),thumb_rect.getMinusY(), 0.0F),    Texcoord2(0.0F,0.0F),  c);
        b.vertex(Vector3(thumb_rect.getPlusX(),thumb_rect.getMinusY(), 0.0F),     Texcoord2(1.0F,0.0F),  c);
        b.vertex(Vector3(thumb_rect.getPlusX(),thumb_rect.getPlusY(), 0.0F),      Texcoord2(1.0F,1.0F),  c);
        b.vertex(Vector3(thumb_rect.getMinusX(),thumb_rect.getPlusY(), 0.0F),     Texcoord2(0.0F,1.0F),  c);

        b.batchEnd();
    }
    
}

//==============================================================================
//==============================================================================

void ComponentGUISlider::touchToValue (const Vector2 &p)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());

    Vector2     pos = gui->positionToObjectCoord(p);
    Rectangle   r = gui->getRectangle();
    DTfloat thumb_width = getThumbWidth() / System::getRenderer()->getScreenAspect();
    
    DTfloat pos_max = r.getPlusX() - thumb_width * 0.5F;
    DTfloat pos_min = r.getMinusX() + thumb_width * 0.5F;

    DTfloat t = (pos.x - pos_min) / (pos_max - pos_min);
    _value = _min_value + (_max_value - _min_value) * t;
    
    if (_value > _max_value)    _value = _max_value;
    if (_value < _min_value)    _value = _min_value;
    
    _value_changed.send();
}

//==============================================================================
//==============================================================================

void ComponentGUISlider::touchesBegan (GUITouchEvent *event)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;
    
    touchToValue(event->getPosition());
}

void ComponentGUISlider::touchesMoved (GUITouchEvent *event)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;
        
    touchToValue(event->getPosition());
}

void ComponentGUISlider::touchesEnded (GUITouchEvent *event)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;

    touchToValue(event->getPosition());
}

void ComponentGUISlider::touchesCancelled (GUITouchEvent *event)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;

}

//==============================================================================
//==============================================================================

} // DT3

