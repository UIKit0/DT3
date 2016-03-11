//==============================================================================
///	
///	File: ComponentGUIScroller.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentGUIScroller.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "GeometryGroupResource.hpp"
#include "World.hpp"
#include "System.hpp"
#include "DeviceGraphics.hpp"
#include "GUIObject.hpp"
#include "ConsoleStream.hpp"
#include "DrawBatcherQuads.hpp"
#include "GUIController.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
//==============================================================================

const DTfloat ComponentGUIScroller::VELOCITY_DECAY = 0.85F;
const DTfloat ComponentGUIScroller::BORDER_BOUNCE = 0.8F;
const DTfloat ComponentGUIScroller::REARRANGE_TIME_THRESH = 1.0F;
const DTfloat ComponentGUIScroller::REARRANGE_TIME_THRESH2 = 0.5F;
const DTfloat ComponentGUIScroller::DELETE_SIZE = 24.0F / 1024.0F;

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentGUIScroller,"GUIBehaviour","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentGUIScroller)

IMPLEMENT_EVENT_INFO(_clicked)

IMPLEMENT_PLUG_INFO(_material)
IMPLEMENT_PLUG_INFO(_delete_material)
IMPLEMENT_PLUG_INFO(_horz_scroll_percentage_fill)
IMPLEMENT_PLUG_INFO(_horz_scroll_position)
IMPLEMENT_PLUG_INFO(_vert_scroll_percentage_fill)
IMPLEMENT_PLUG_INFO(_vert_scroll_position)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentGUIScroller)

    PLUG_INIT(_material, "Material")
		.setInput(true);

    PLUG_INIT(_delete_material, "Delete_Material")
		.setInput(true);

    PLUG_INIT(_horz_scroll_percentage_fill, "Horz_Percentage")
		.setOutput(true);

    PLUG_INIT(_horz_scroll_position, "Horz_Position")
		.setOutput(true);

    PLUG_INIT(_vert_scroll_percentage_fill, "Vert_Percentage")
		.setOutput(true);

    PLUG_INIT(_vert_scroll_position, "Vert_Position")
		.setOutput(true);

END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentGUIScroller::ComponentGUIScroller (void)
    :   _material                   (PLUG_INFO(_material)),
        _delete_material            (PLUG_INFO(_delete_material)),
        _horz_scroll_percentage_fill(PLUG_INFO(_horz_scroll_percentage_fill), 0.0F),
        _horz_scroll_position       (PLUG_INFO(_horz_scroll_position), 0.0F),
        _vert_scroll_percentage_fill(PLUG_INFO(_vert_scroll_percentage_fill), 0.0F),
        _vert_scroll_position       (PLUG_INFO(_vert_scroll_position), 0.0F),
        _scroll_horz                (true),
        _scroll_vert                (true),
        _auto_center_horz           (true),
        _auto_center_vert           (true),
        _vel_x                      (0.0F),
        _vel_y                      (0.0F),
        _pad_horz                   (0.0F),
        _pad_vert                   (0.0F),
        _scroll_to_top              (false),
        _scroll_to_bottom           (false),
        _scroll_to_left             (false),
        _scroll_to_right            (false),
        _velocity_decay             (VELOCITY_DECAY),
        _focused                    (NULL),
        _press_timer                (0.0F),
        _can_rearrage_items         (false),
        _can_remove_items           (false),
        _mode                       (MODE_NORMAL),
        _rearranging_timer          (0.0F),
        _contents                   (0.0F,0.0F,0.0F,0.0F)
{  

}
		
ComponentGUIScroller::ComponentGUIScroller (const ComponentGUIScroller &rhs)
    :   ComponentBase               (rhs),
        _material                   (rhs._material),
        _delete_material            (rhs._delete_material),
        _horz_scroll_percentage_fill(rhs._horz_scroll_percentage_fill),
        _horz_scroll_position       (rhs._horz_scroll_position),
        _vert_scroll_percentage_fill(rhs._vert_scroll_percentage_fill),
        _vert_scroll_position       (rhs._vert_scroll_position),
        _scroll_horz                (rhs._scroll_horz),
        _scroll_vert                (rhs._scroll_vert),
        _auto_center_horz           (rhs._auto_center_horz),
        _auto_center_vert           (rhs._auto_center_vert),
        _vel_x                      (rhs._vel_x),
        _vel_y                      (rhs._vel_y),
        _pad_horz                   (rhs._pad_horz),
        _pad_vert                   (rhs._pad_vert),
        _scroll_to_top              (rhs._scroll_to_top),
        _scroll_to_bottom           (rhs._scroll_to_bottom),
        _scroll_to_left             (rhs._scroll_to_left),
        _scroll_to_right            (rhs._scroll_to_right),
        _velocity_decay             (rhs._velocity_decay),
        _focused                    (NULL),
        _press_timer                (rhs._press_timer),
        _can_rearrage_items         (rhs._can_rearrage_items),
        _can_remove_items           (rhs._can_remove_items),
        _mode                       (rhs._mode),
        _rearranging_timer          (rhs._rearranging_timer),
        _contents                   (rhs._contents)
{   
    SAFE_ASSIGN(_focused, rhs._focused);
}

ComponentGUIScroller & ComponentGUIScroller::operator = (const ComponentGUIScroller &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        
        _material = rhs._material;
        _delete_material = rhs._delete_material;
                
        _scroll_horz = rhs._scroll_horz;
        _scroll_vert = rhs._scroll_vert;

        _auto_center_horz = rhs._auto_center_horz;
        _auto_center_vert = rhs._auto_center_vert;
        
        _horz_scroll_percentage_fill = rhs._horz_scroll_percentage_fill;
        _horz_scroll_position = rhs._horz_scroll_position;

        _vert_scroll_percentage_fill = rhs._vert_scroll_percentage_fill;
        _vert_scroll_position = rhs._vert_scroll_position;

        _vel_x = rhs._vel_x;
        _vel_y = rhs._vel_y;
        
        _pad_horz = rhs._pad_horz;
        _pad_vert = rhs._pad_vert;

        _scroll_to_top = rhs._scroll_to_top;
        _scroll_to_bottom = rhs._scroll_to_bottom;
        _scroll_to_left = rhs._scroll_to_left;
        _scroll_to_right = rhs._scroll_to_right;

        _velocity_decay = rhs._velocity_decay;

        SAFE_ASSIGN(_focused, rhs._focused);
        
        _press_timer = rhs._press_timer;
        _can_rearrage_items = rhs._can_rearrage_items;
        _can_remove_items = rhs._can_remove_items;
        
        _mode = rhs._mode;
        _rearranging_timer = rhs._rearranging_timer;
        
        _contents = rhs._contents;
    }
    return (*this);
}
			
ComponentGUIScroller::~ComponentGUIScroller (void)
{
    RELEASE(_focused);
}

//==============================================================================
//==============================================================================

void ComponentGUIScroller::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentGUIScroller::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
    
	*archive << ARCHIVE_PLUG(_material, DATA_PERSISTENT | DATA_SETTABLE);
    if (archive->getVersion() >= 1354) {
        *archive << ARCHIVE_PLUG(_delete_material, DATA_PERSISTENT | DATA_SETTABLE);
    }
    
	*archive << ARCHIVE_DATA(_scroll_horz, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_scroll_vert, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA(_auto_center_horz, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_auto_center_vert, DATA_PERSISTENT | DATA_SETTABLE);
    
    if (archive->getVersion() >= 1335) {
        *archive << ARCHIVE_DATA(_pad_horz, DATA_PERSISTENT | DATA_SETTABLE);
        *archive << ARCHIVE_DATA(_pad_vert, DATA_PERSISTENT | DATA_SETTABLE);
    }

    if (archive->getVersion() >= 1354) {
        *archive << ARCHIVE_DATA(_can_rearrage_items, DATA_PERSISTENT | DATA_SETTABLE);
        *archive << ARCHIVE_DATA(_can_remove_items, DATA_PERSISTENT | DATA_SETTABLE);
    }

	*archive << ARCHIVE_DATA(_velocity_decay, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

void ComponentGUIScroller::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	
	*archive << ARCHIVE_PLUG(_material, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_PLUG(_delete_material, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA(_scroll_horz, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_scroll_vert, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA(_auto_center_horz, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_auto_center_vert, DATA_PERSISTENT | DATA_SETTABLE);

    *archive << ARCHIVE_DATA(_pad_horz, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_DATA(_pad_vert, DATA_PERSISTENT | DATA_SETTABLE);

    *archive << ARCHIVE_DATA(_can_rearrage_items, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_DATA(_can_remove_items, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA(_velocity_decay, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentGUIScroller::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    GUIObject *gui = checkedCast<GUIObject*>(owner);
    if (gui) {
        
        gui->getHitObjectCallbacks().add(makeCallback(this, &ComponentGUIScroller::hitTest));

        gui->getTouchesBeganCallbacks().add(makeCallback(this, &type::touchesBegan));
        gui->getTouchesMovedCallbacks().add(makeCallback(this, &type::touchesMoved));
        gui->getTouchesEndedCallbacks().add(makeCallback(this, &type::touchesEnded));
        gui->getTouchesCancelledCallbacks().add(makeCallback(this, &type::touchesCancelled));

        gui->getPostDrawGUICallbacks().add(makeCallback(this, &ComponentGUIScroller::draw));
    }
    
    World *w = getOwner()->getWorld();    
    w->registerForTick(getOwner(), makeCallback(this, &ComponentGUIScroller::tick));
}

void ComponentGUIScroller::removeFromOwner (void)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (gui) {
        gui->getHitObjectCallbacks().remove(makeCallback(this, &ComponentGUIScroller::hitTest));

        gui->getTouchesBeganCallbacks().remove(makeCallback(this, &type::touchesBegan));
        gui->getTouchesMovedCallbacks().remove(makeCallback(this, &type::touchesMoved));
        gui->getTouchesEndedCallbacks().remove(makeCallback(this, &type::touchesEnded));
        gui->getTouchesCancelledCallbacks().remove(makeCallback(this, &type::touchesCancelled));

        gui->getPostDrawGUICallbacks().remove(makeCallback(this, &ComponentGUIScroller::draw));
    }

    World *w = getOwner()->getWorld();
    w->unregisterForTick(getOwner(), makeCallback(this, &type::tick));

    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

void ComponentGUIScroller::startWiggle (void)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;

    // Make the items wiggly
    const std::list<PlaceableObject*> &children = gui->getChildren();
    
    for (auto i : children) {
        GUIObject *child = checkedCast<GUIObject*>(i);
        if (!child)
            continue;
            
        startWiggleItem(child);
    }
}

void ComponentGUIScroller::stopWiggle (void)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;

    // Make the items wiggly
    const std::list<PlaceableObject*> &children = gui->getChildren();
    
    for (auto i : children) {
        GUIObject *child = checkedCast<GUIObject*>(i);
        if (!child)
            continue;
            
        stopWiggleItem(child);
    }
}

void ComponentGUIScroller::startWiggleItem (GUIObject *item)
{
    item->addAnimKey()
        .setDuration(0.1F)
        .setRepeat()
        .setOrientation(Matrix3::setRotationZ(-0.02));

    item->addAnimKey()
        .setDuration(0.1F)
        .setRepeat()
        .setOrientation(Matrix3::setRotationZ(0.02));
}

void ComponentGUIScroller::stopWiggleItem (GUIObject *item)
{
    item->clearAnims();
    item->setOrientation(Matrix3::identity());
}

//==============================================================================
//==============================================================================

void ComponentGUIScroller::calculateContectRect(void)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    _contents = gui->getChildrenContentRectangle();
}

//==============================================================================
//==============================================================================

void ComponentGUIScroller::tick (DTfloat dt)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;
        
    if (_mode != MODE_NORMAL) {
        _rearranging_timer += dt*2.0F;
        if (_rearranging_timer > 1.0F)  
            _rearranging_timer = 1.0F;
    } else {                     
        _rearranging_timer -= dt*2.0F;
        if (_rearranging_timer < 0.0F)  
            _rearranging_timer = 0.0F;
    }
        
    // Update press timer
    if (_focused && _can_rearrage_items) {
        _press_timer += dt;
        
        if (_press_timer > REARRANGE_TIME_THRESH && (_mode == MODE_NORMAL) ) {
            _mode = MODE_REARRANGING_DRAGGING;
            
            _focused->touchesCancelled(NULL);
            startWiggle();
        } else if (_press_timer > REARRANGE_TIME_THRESH2 && (_mode == MODE_REARRANGING) ) {
            _mode = MODE_REARRANGING_DRAGGING;
            
            _focused->touchesCancelled(NULL);
            startWiggle();
        }
        
    }
        
    // Ramp velocity
    if (_vel_x != 0.0F || _vel_y != 0.0F) {
    
        gui->scrollContents (_vel_x * dt, _vel_y * dt);
        _contents.offset(Vector2(_vel_x * dt, _vel_y * dt));

        _vel_x *= _velocity_decay;
        _vel_y *= _velocity_decay;
        
    }
        
    // Limit scroll bounds
    Rectangle rect = gui->getRectangle();
        
    if (_scroll_vert) {
        if (_contents.getHeight() > rect.getHeight()) {
        
            if (_contents.getPlusY() < (rect.getPlusY() - _pad_vert)) {
            
                DTfloat delta = (rect.getPlusY() - _pad_vert) - _contents.getPlusY();
                gui->scrollContents (0, delta * BORDER_BOUNCE);
                _contents.offset(Vector2(0, delta * BORDER_BOUNCE));
             
                //LOG_MESSAGE << "Top Bound hit " << contents.getPlusY() << " " << rect.getPlusY();
                
            } else if (_contents.getMinusY() > (rect.getMinusY() + _pad_vert)) {
                
                DTfloat delta = (rect.getMinusY() + _pad_vert) - _contents.getMinusY();
                gui->scrollContents (0, delta * BORDER_BOUNCE);
                _contents.offset(Vector2(0, delta * BORDER_BOUNCE));
            
                //LOG_MESSAGE << "Bottom Bound hit " << contents.getMinusY() << " " << rect.getMinusY();

            } 

            if (_scroll_to_top) {
                DTfloat delta = rect.getPlusY() - _contents.getPlusY();  
                gui->scrollContents (0, delta);
                _contents.offset(Vector2(0, delta));
            }
            if (_scroll_to_bottom) {  
                DTfloat delta = rect.getMinusY() - _contents.getMinusY();
                gui->scrollContents (0, delta);
                _contents.offset(Vector2(0, delta));
            }
                        
        } else {
        
            if (_auto_center_vert) {
                DTfloat delta = ( (rect.getPlusY() + rect.getMinusY())*0.5F - (_contents.getPlusY() + _contents.getMinusY())*0.5F );
                gui->scrollContents (0, delta * BORDER_BOUNCE);
                _contents.offset(Vector2(0, delta * BORDER_BOUNCE));
            } else {
                DTfloat delta = rect.getPlusY() - _contents.getPlusY();
                gui->scrollContents (0, delta * BORDER_BOUNCE);
                _contents.offset(Vector2(0, delta * BORDER_BOUNCE));
            }
            
        }
        
        _vert_scroll_percentage_fill = (rect.getPlusY() - rect.getMinusY()) / (_contents.getPlusY() - _contents.getMinusY());
        if (_vert_scroll_percentage_fill > 1.0) _vert_scroll_percentage_fill = 1.0F;
        
    }

    if (_scroll_horz) {
        if (_contents.getWidth() > rect.getWidth()) {
            if ( _contents.getPlusX() < (rect.getPlusX() - _pad_horz)) {
            
                DTfloat delta = (rect.getPlusX() - _pad_horz) - _contents.getPlusX();
                gui->scrollContents (delta * BORDER_BOUNCE,0);
                _contents.offset(Vector2(delta * BORDER_BOUNCE,0));
            
                //LOG_MESSAGE << "Right Bound hit " << contents.getPlusX() << " " << rect.getPlusX();
                
            } else if ( _contents.getMinusX() > (rect.getMinusX() + _pad_horz) ) {
                
                DTfloat delta = (rect.getMinusX() + _pad_horz) -  _contents.getMinusX();
                gui->scrollContents (delta * BORDER_BOUNCE,0);
                _contents.offset(Vector2(delta * BORDER_BOUNCE,0));
            
                //LOG_MESSAGE << "Left Bound hit " << contents.getMinusX() << " " << rect.getMinusX();

            }
            
            if (_scroll_to_left) {
                DTfloat delta = rect.getMinusX() - _contents.getMinusX();
                gui->scrollContents (delta,0);
                _contents.offset(Vector2(delta,0));
            }
            if (_scroll_to_right) {  
                DTfloat delta = rect.getPlusX() - _contents.getPlusX();  
                gui->scrollContents (delta,0);
                _contents.offset(Vector2(delta,0));
            }

        } else {
        
            if (_auto_center_horz) {
                DTfloat delta = ( (rect.getPlusX() + rect.getMinusX())*0.5F - (_contents.getPlusX() + _contents.getMinusX())*0.5F );
                gui->scrollContents (delta * BORDER_BOUNCE, 0);
                _contents.offset(Vector2(delta * BORDER_BOUNCE,0));
            } else {
                DTfloat delta = rect.getMinusX() - _contents.getMinusX();
                gui->scrollContents (delta * BORDER_BOUNCE, 0);
                _contents.offset(Vector2(delta * BORDER_BOUNCE,0));
            }
            
        }
    }
    
    // If animating, keep flags on
    if (!gui->hasAnimKey()) {
        _scroll_to_top = false;
        _scroll_to_bottom = false;
        _scroll_to_left = false;
        _scroll_to_right = false;
    }
    
}

//==============================================================================
//==============================================================================

Rectangle ComponentGUIScroller::calcDeleteButtonRectangle (const GUIObject *object)
{
    DTfloat aspect = System::getRenderer()->getScreenAspect();

    Vector3 center = object->getTranslationLocal() + Vector3(object->getWidth() * 0.5F, object->getHeight() * 0.5F, 0.0F);
    
    return Rectangle(   center.x - DELETE_SIZE*_rearranging_timer, 
                        center.x + DELETE_SIZE*_rearranging_timer, 
                        center.y - DELETE_SIZE*_rearranging_timer*aspect, 
                        center.y + DELETE_SIZE*_rearranging_timer*aspect);
}

//==============================================================================
//==============================================================================

void ComponentGUIScroller::draw (CameraObject* camera, const Color &parent_color)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;

    MaterialResource *material = _material->get();
       
    if (gui->getColor().getA() * parent_color.getA() <= 0.0F)
        return;
            
    //
    // Scroll bars
    //

    Color c = gui->getColor() * parent_color;

    if (_material->isValid()) {
        const DTfloat H_SIZE = 4.0F/1024.0F;
        const DTfloat V_SIZE = H_SIZE / System::getRenderer()->getScreenAspect();
                    
        // Limit scroll bounds
        Rectangle rect = gui->getRectangle();
            
        if (_scroll_vert && (_contents.getPlusY() > rect.getPlusY() || _contents.getMinusY() < rect.getMinusY())) {
            
            DTfloat top_gap = 1.0F - ( _contents.getPlusY() - rect.getPlusY() ) / _contents.getHeight();
            DTfloat bottom_gap = ( rect.getMinusY() - _contents.getMinusY() ) / _contents.getHeight();
            
            if (top_gap > 1.0F)     top_gap = 1.0F;
            if (bottom_gap < 0.0F)  bottom_gap = 0.0F;
                    
            DrawBatcherQuads b;
            b.batchBegin(material, gui->getDrawTransform(), DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);
            
            b.vertex(Vector3(rect.getPlusX() - H_SIZE,  rect.getMinusY() + rect.getHeight() * bottom_gap,0.0F), Texcoord2(0.0F,0.0F), c);
            b.vertex(Vector3(rect.getPlusX(),           rect.getMinusY() + rect.getHeight() * bottom_gap,0.0F), Texcoord2(1.0F,0.0F), c);
            b.vertex(Vector3(rect.getPlusX(),           rect.getMinusY() + rect.getHeight() * bottom_gap + V_SIZE,0.0F), Texcoord2(1.0F,0.5F), c);
            b.vertex(Vector3(rect.getPlusX() - H_SIZE,  rect.getMinusY() + rect.getHeight() * bottom_gap + V_SIZE,0.0F), Texcoord2(0.0F,0.5F), c);

            b.vertex(Vector3(rect.getPlusX() - H_SIZE,  rect.getMinusY() + rect.getHeight() * bottom_gap + V_SIZE,0.0F), Texcoord2(0.0F,0.5F), c);
            b.vertex(Vector3(rect.getPlusX(),           rect.getMinusY() + rect.getHeight() * bottom_gap + V_SIZE,0.0F), Texcoord2(1.0F,0.5F), c);
            b.vertex(Vector3(rect.getPlusX(),           rect.getMinusY() + rect.getHeight() * top_gap - V_SIZE,0.0F), Texcoord2(1.0F,0.5F), c);
            b.vertex(Vector3(rect.getPlusX() - H_SIZE,  rect.getMinusY() + rect.getHeight() * top_gap - V_SIZE,0.0F), Texcoord2(0.0F,0.5F), c);

            b.vertex(Vector3(rect.getPlusX() - H_SIZE,  rect.getMinusY() + rect.getHeight() * top_gap - V_SIZE,0.0F), Texcoord2(0.0F,0.5F), c);
            b.vertex(Vector3(rect.getPlusX(),           rect.getMinusY() + rect.getHeight() * top_gap - V_SIZE,0.0F), Texcoord2(1.0F,0.5F), c);
            b.vertex(Vector3(rect.getPlusX(),           rect.getMinusY() + rect.getHeight() * top_gap,0.0F), Texcoord2(1.0F,1.0F), c);
            b.vertex(Vector3(rect.getPlusX() - H_SIZE,  rect.getMinusY() + rect.getHeight() * top_gap,0.0F), Texcoord2(0.0F,1.0F), c);
            
            b.batchEnd();
        }

        if (_scroll_horz && (_contents.getPlusX() > rect.getPlusX() || _contents.getMinusX() < rect.getMinusX())) {
            
            DTfloat right_gap = 1.0F - ( _contents.getPlusX() - rect.getPlusX() ) / _contents.getWidth();
            DTfloat left_gap = ( rect.getMinusX() - _contents.getMinusX() ) / _contents.getWidth();
            
            if (right_gap > 1.0F)   right_gap = 1.0F;
            if (left_gap < 0.0F)    left_gap = 0.0F;
            
            
            DrawBatcherQuads b;
            b.batchBegin(material, gui->getDrawTransform(), DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);
            
            b.vertex(Vector3(rect.getMinusX() + rect.getWidth() * left_gap,            rect.getMinusY() - V_SIZE,   0.0F), Texcoord2(0.0F,0.0F), c);
            b.vertex(Vector3(rect.getMinusX() + rect.getWidth() * left_gap + H_SIZE,   rect.getMinusY() - V_SIZE,   0.0F), Texcoord2(0.5F,0.0F), c);
            b.vertex(Vector3(rect.getMinusX() + rect.getWidth() * left_gap + H_SIZE,   rect.getMinusY(),            0.0F), Texcoord2(0.5F,1.0F), c);
            b.vertex(Vector3(rect.getMinusX() + rect.getWidth() * left_gap,            rect.getMinusY(),            0.0F), Texcoord2(0.0F,1.0F), c);

            b.vertex(Vector3(rect.getMinusX() + rect.getWidth() * left_gap + H_SIZE,   rect.getMinusY() - V_SIZE,   0.0F), Texcoord2(0.5F,0.0F), c);
            b.vertex(Vector3(rect.getMinusX() + rect.getWidth() * right_gap - H_SIZE,  rect.getMinusY() - V_SIZE,   0.0F), Texcoord2(0.5F,0.0F), c);
            b.vertex(Vector3(rect.getMinusX() + rect.getWidth() * right_gap - H_SIZE,  rect.getMinusY(),            0.0F), Texcoord2(0.5F,1.0F), c);
            b.vertex(Vector3(rect.getMinusX() + rect.getWidth() * left_gap + H_SIZE,   rect.getMinusY(),            0.0F), Texcoord2(0.5F,1.0F), c);

            b.vertex(Vector3(rect.getMinusX() + rect.getWidth() * right_gap - H_SIZE,  rect.getMinusY() - V_SIZE,   0.0F), Texcoord2(0.5F,0.0F), c);
            b.vertex(Vector3(rect.getMinusX() + rect.getWidth() * right_gap,           rect.getMinusY() - V_SIZE,   0.0F), Texcoord2(1.0F,0.0F), c);
            b.vertex(Vector3(rect.getMinusX() + rect.getWidth() * right_gap,           rect.getMinusY(),            0.0F), Texcoord2(1.0F,1.0F), c);
            b.vertex(Vector3(rect.getMinusX() + rect.getWidth() * right_gap - H_SIZE,  rect.getMinusY(),            0.0F), Texcoord2(0.5F,1.0F), c);
            
            b.batchEnd();
        }
    }
        
    //
    // Delete boxes
    //
    
    if (_delete_material->isValid() && _can_remove_items && _mode != MODE_NORMAL) {
        std::list<PlaceableObject*> children = gui->getChildren();
        
        for (auto i : children) {
            GUIObject *icon = checkedCast<GUIObject*>(i);
            if (!icon)
                continue;
                
            Rectangle rect = calcDeleteButtonRectangle(icon);
            
            DrawBatcherQuads b;
            b.batchBegin(_delete_material->get(), gui->getTransform(), DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);
            
            b.vertex(Vector3(rect.getMinusX(), rect.getMinusY(), 0.0F), Texcoord2(0.0F,0.0F), c);
            b.vertex(Vector3(rect.getPlusX(), rect.getMinusY(), 0.0F), Texcoord2(1.0F,0.0F), c);
            b.vertex(Vector3(rect.getPlusX(), rect.getPlusY(), 0.0F), Texcoord2(1.0F,1.0F), c);
            b.vertex(Vector3(rect.getMinusX(), rect.getPlusY(), 0.0F), Texcoord2(0.0F,1.0F), c);
            
            b.batchEnd();
        }  
    }
}

//==============================================================================
//==============================================================================

void ComponentGUIScroller::hitTest (GUITouchEvent *event, GUIObject* &hit_object, const Color &parent_color)
{   
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;
        
    Color c = parent_color * gui->getColor();

    if (c.getA() == 0)
        return;

    Vector2 object_pos = gui->positionToObjectCoord (event->getPosition());
    if (gui->getRectangle().isTouching(object_pos)) {
        
        hit_object = gui;

        std::list<PlaceableObject*> children = gui->getChildren();
        
        for (auto i : children) {
            GUIObject *gui = checkedCast<GUIObject*>(i);
            if (!gui)
                continue;
                
            gui->hitTest(event, _focused, c);
            if (_focused) {
                RETAIN(_focused);
                break;
            }
        }   

    }
}

void ComponentGUIScroller::touchesBegan (GUITouchEvent *event)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;
        
    _press_timer = 0.0F;

    if (_focused && _mode == MODE_NORMAL)
        _focused->touchesBegan(event);
    
    // Do scroll
    if (event->getFocused() == gui) {
        _vel_x = 0.0F;
        _vel_y = 0.0F;
    }
    
}

void ComponentGUIScroller::touchesMoved (GUITouchEvent *event)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;
        
    if (event->getPosition() == event->getPreviousPosition())
        return;
        
    _press_timer = 0.0F;
        
    // If the touch is associated with another gui object
    if (_focused && _mode == MODE_NORMAL) {
        
        if ( (event->getPosition() - event->getInitialPosition()).abs() > 10.0F ) {
            event->setFocused(gui); // Scroller steals focus
            
            // If the scroller was forwarding touch events to another widget
            _focused->touchesCancelled(event);
            RELEASE(_focused);
        }
        
    }
    
    // If dragging to rearrange
    if (_focused && _mode == MODE_REARRANGING_DRAGGING) {
    
        // Do Move
        if (event->getFocused() == gui) {
            // Transform touches into widget coordinates
            Vector2 delta = gui->velocityToObjectCoord(event->getPosition() - event->getPreviousPosition());

            _focused->setTranslation( _focused->getTranslation() + Vector3(delta) );
            
            draggingItem(_focused);
        }

    } else if (!_focused || (_focused && (_mode == MODE_REARRANGING || _mode == MODE_REARRANGING_SCROLLING))) {
    
        if (_mode == MODE_REARRANGING)
            _mode = MODE_REARRANGING_SCROLLING;
    
        // Do scroll
        if (event->getFocused() == gui) {
            // Handle scrolling
            _vel_x = 0.0F;
            _vel_y = 0.0F;

            // Transform touches into widget coordinates
            Vector2 delta = gui->velocityToObjectCoord(event->getPosition() - event->getPreviousPosition());
            gui->scrollContents (delta.x * _scroll_horz, delta.y * _scroll_vert);
            _contents.offset(Vector2(delta.x * _scroll_horz, delta.y * _scroll_vert));
            
            RELEASE(_focused);
        }
        
        
    }

}

void ComponentGUIScroller::touchesEnded (GUITouchEvent *event)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;
        
    if (_focused && _mode == MODE_NORMAL) {
        _focused->touchesEnded(event);
        RELEASE(_focused);
    }
    
    // Check delete
    if (event->getFocused() == gui && _can_remove_items && _mode != MODE_NORMAL) {
        Vector2 pos0 = gui->positionToObjectCoord(event->getPosition());
        Vector2 pos1 = gui->positionToObjectCoord(event->getPosition());
            
        std::list<PlaceableObject*> children = gui->getChildren();
        
        for (auto i : children) {
            GUIObject *icon = checkedCast<GUIObject*>(i);
            if (!icon)
                continue;
                
            Rectangle rect = calcDeleteButtonRectangle(icon);
            
            if (rect.isTouching(pos0) && rect.isTouching(pos1)) {
                deleteItem(icon);
                return;
            }
        }  
    
    }

    
    // Do scroll
    if (event->getFocused() == gui && _mode != MODE_REARRANGING_DRAGGING) {
        Vector2 vel = gui->velocityToObjectCoord(event->getVelocity());
                    
        // Transform touches into widget coordinates
        _vel_x = vel.x * _scroll_horz;
        _vel_y = vel.y * _scroll_vert;
    }
    

    if (_mode == MODE_REARRANGING) {
        _mode = MODE_NORMAL;
        
        stopWiggle();
        
        RELEASE(_focused);
    }
    
    if (_mode == MODE_REARRANGING_SCROLLING) {
        _mode = MODE_REARRANGING;
    }
           
    if (_mode == MODE_REARRANGING_DRAGGING) {
        _mode = MODE_REARRANGING;

        finishedDraggingItem(_focused);
        
        RELEASE(_focused);
    }



}

void ComponentGUIScroller::touchesCancelled (GUITouchEvent *event)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;

}

//==============================================================================
//==============================================================================

void ComponentGUIScroller::deleteItem (GUIObject *item)  
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;
        
    RELEASE(_focused);
        
    gui->unparentChild(item);
    gui->getWorld()->removeNodeSafely(item);
}

//==============================================================================
//==============================================================================

} // DT3

