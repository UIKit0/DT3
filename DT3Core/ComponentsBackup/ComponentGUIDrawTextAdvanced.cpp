//==============================================================================
///	
///	File: ComponentGUIDrawTextAdvanced.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentGUIDrawTextAdvanced.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "MaterialResource.hpp"
#include "TextureResource.hpp"
#include "FontResource.hpp"
#include "World.hpp"
#include "GUIObject.hpp"
#include "DrawBatcherQuads.hpp"
#include "MoreMath.hpp"
#include "TextRenderer.hpp"
#include "System.hpp"
#include "SystemCallbacks.hpp"
#include "DeviceGraphics.hpp"
#include "Globals.hpp"
#include "DrawUtils.hpp"
#include "ConsoleStream.hpp"
#include "GlyphCache.hpp"
#include <cmath>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentGUIDrawTextAdvanced,"GUI","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentGUIDrawTextAdvanced)

IMPLEMENT_PLUG_INFO(_font_material)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentGUIDrawTextAdvanced)
                        
    PLUG_INIT(_font_material, "Font_Material")
		.setInput(true);
                
END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentGUIDrawTextAdvanced::ComponentGUIDrawTextAdvanced (void)
    :   _font_material      (PLUG_INFO(_font_material)),
        _bounds             (0.0F,0.0F,0.0F,0.0F),
        _needs_render       (true),
        _can_render         (true),
        _center_vertically  (false),
        _normal_color       (1.0F,1.0F,1.0F,1.0F),
        _pressed_color      (1.0F,1.0F,1.0F,1.0F),
        _text_image         (NULL)
{

}
		
ComponentGUIDrawTextAdvanced::ComponentGUIDrawTextAdvanced (const ComponentGUIDrawTextAdvanced &rhs)
    :   ComponentBase       (rhs),
        _font_material      (rhs._font_material),
        _bounds             (rhs._bounds),
        _needs_render       (true),
        _can_render         (true),
        _center_vertically  (rhs._center_vertically),
        _normal_color       (rhs._normal_color),
        _pressed_color      (rhs._pressed_color),
        _text_image         (rhs._text_image)
{

}

ComponentGUIDrawTextAdvanced & ComponentGUIDrawTextAdvanced::operator = (const ComponentGUIDrawTextAdvanced &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
                
        _font_material = rhs._font_material;
        
        _bounds = rhs._bounds;
        _needs_render = true;
        _can_render = true;
        _center_vertically = rhs._center_vertically;
        _normal_color = rhs._normal_color;
        _pressed_color = rhs._pressed_color;

        _text_image = rhs._text_image;
    }
    return (*this);
}
			
ComponentGUIDrawTextAdvanced::~ComponentGUIDrawTextAdvanced (void)
{
    SystemCallbacks::getScreenOpenedCB().remove(makeCallback(this,&type::screenOpened));
    SystemCallbacks::getScreenClosedCB().remove(makeCallback(this,&type::screenClosed));
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawTextAdvanced::initialize (void)
{
	ComponentBase::initialize();
    
    SystemCallbacks::getScreenOpenedCB().add(makeCallback(this,&type::screenOpened));
    SystemCallbacks::getScreenClosedCB().add(makeCallback(this,&type::screenClosed));
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawTextAdvanced::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
        		    
	*archive << ARCHIVE_PLUG(_font_material, DATA_PERSISTENT | DATA_SETTABLE);
    
    if (archive->getVersion() < 1381) {
        DTboolean _color;
        *archive << ARCHIVE_DATA(_color, DATA_PERSISTENT | DATA_SETTABLE);
    }
	*archive << ARCHIVE_DATA(_center_vertically, DATA_PERSISTENT | DATA_SETTABLE);
    
    if (archive->getVersion() >= 1348) {
        *archive << ARCHIVE_DATA(_normal_color, DATA_PERSISTENT | DATA_SETTABLE);
        *archive << ARCHIVE_DATA(_pressed_color, DATA_PERSISTENT | DATA_SETTABLE);
    }
    
    archive->pop_domain ();
}

void ComponentGUIDrawTextAdvanced::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	    
	*archive << ARCHIVE_PLUG(_font_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_center_vertically, DATA_PERSISTENT | DATA_SETTABLE);

    *archive << ARCHIVE_DATA(_normal_color, DATA_PERSISTENT | DATA_SETTABLE);
    *archive << ARCHIVE_DATA(_pressed_color, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawTextAdvanced::screenOpened (DTuint width, DTuint height)
{
    // If for some reason the render context is created, we have to rerender
    
    _can_render = true;
    _needs_render = true;
}
        
void ComponentGUIDrawTextAdvanced::screenClosed (void)
{
    // If for some reason the render context is lost, we have to clean up

    _can_render = false;
    _needs_render = true;
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawTextAdvanced::draw (CameraObject* camera, const Color &parent_color)
{        
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui) {
        _text_image = std::shared_ptr<TextureResource>();
        _needs_render = true;
        return;
    }
    
    MaterialResource *font_material = _font_material->get();
       
    if (gui->getColor().getA() * parent_color.getA() <= 0.0F) {
        _text_image = std::shared_ptr<TextureResource>();
        _needs_render = true;
        return;
    }
    
    Rectangle local_rect = gui->getRectangle();
    DTfloat screen_width = System::getRenderer()->getViewportWidth();
    //DTfloat screen_height = System::getRenderer()->getViewportHeight();
    
    /*// Snap to pixels
    local_rect.setMinusX( std::floor(local_rect.getMinusX() * screen_width) / screen_width);
    local_rect.setPlusX( std::floor(local_rect.getPlusX() * screen_width) / screen_width);
    local_rect.setMinusY( std::floor(local_rect.getMinusY() * screen_height) / screen_height);
    local_rect.setPlusY( std::floor(local_rect.getPlusY() * screen_height) / screen_height);*/
    
    //
    // Check screen space rectangle to see if it has changed
    //
    
    Matrix4 transform = gui->getDrawTransform();

    Vector2 p0 = transform * Vector2(local_rect.getMinusX(), local_rect.getMinusY());
    Vector2 p1 = transform * Vector2(local_rect.getPlusX(), local_rect.getMinusY());
    Vector2 p2 = transform * Vector2(local_rect.getMinusX(), local_rect.getPlusY());
    Vector2 p3 = transform * Vector2(local_rect.getPlusX(), local_rect.getPlusY());

    Rectangle bounds;
    bounds.setMinusX( min4(p0.x, p1.x, p2.x, p3.x) );
    bounds.setPlusX( max4(p0.x, p1.x, p2.x, p3.x) );
    bounds.setMinusY( min4(p0.y, p1.y, p2.y, p3.y) );
    bounds.setPlusY( max4(p0.y, p1.y, p2.y, p3.y) );
    
    if (!bounds.isTouching( Rectangle(0.0F,1.0F,0.0F,1.0F) ) ) {
        _text_image = std::shared_ptr<TextureResource>();
        _needs_render = true;
        return;
    }
    
    DTfloat new_width = bounds.getPlusX() - bounds.getMinusX();
    DTfloat new_height = bounds.getPlusY() - bounds.getMinusY();

    DTfloat width = _bounds.getPlusX() - _bounds.getMinusX();
    DTfloat height = _bounds.getPlusY() - _bounds.getMinusY();
    
    _bounds = bounds;

    const DTfloat TOLERANCE = 1.0F / screen_width;
    
#if DT3_EDITOR
    _needs_render = true;   // always render in editor
#endif

    String label = Globals::substituteGlobal(gui->getLabel());
    
    if ((   (fabsf(new_width-width) > TOLERANCE) || 
            (fabsf(new_height-height) > TOLERANCE) || 
            _label != label || _needs_render) && _can_render && font_material) {
            
        LOG_MESSAGE << "Rendering: " << gui->getLabel();
            
        _needs_render = false;
        _label = label;
    
        Vector2 scale(System::getRenderer()->getScreenWidth(), System::getRenderer()->getScreenHeight());
        Vector2 p0_screen = p0 * scale;
        Vector2 p1_screen = p1 * scale;
        Vector2 p2_screen = p2 * scale;
        Vector2 p3_screen = p3 * scale;
        
        Vector2 offset = (p0 - Vector2(bounds.getMinusX(), bounds.getMinusY()) ) * scale;

        DTint tex_width = (_bounds.getPlusX() - _bounds.getMinusX()) * System::getRenderer()->getScreenWidth();
        DTint tex_height = (_bounds.getPlusY() - _bounds.getMinusY()) * System::getRenderer()->getScreenHeight();
        
        DTint tex_width_pow2 = MoreMath::nextPower2(tex_width);
        DTint tex_height_pow2 = MoreMath::nextPower2(tex_height);
        
        DTfloat box_width = (p3_screen - p2_screen).abs();
        DTfloat box_height = (p0_screen - p2_screen).abs();
        
        
        if (_text_image.isNull() || (_text_image->getWidth() != tex_width_pow2) || (_text_image->getHeight() != tex_height_pow2) ) {
        
            if (_text_image.isNull()) {
                _text_image = std::shared_ptr<TextureResource>(TextureResource::create());
            }
                
            _text_image->allocateRGBATextels2D(tex_width_pow2, tex_height_pow2, false);
        }
                
                
        Matrix3 orientation = gui->getTransform().orientation().orthoed();

        DTfloat resolution_mul = System::getRenderer()->getScreenWidth() / 1024.0F;
    
        TextRenderer::beginRender (_text_image.get());
        
        GlyphCache cache;
        TextLines lines;

        lines.addLine( cache, Matrix4(orientation), gui->getScale(), resolution_mul, gui->getLabel() );
        
        lines.wrap(box_width, box_height, (_center_vertically ? TextLines::ALIGN_MIDDLE : TextLines::ALIGN_TOP) );   
        TextRenderer::renderLines(_text_image.get(), lines, offset);
        
        TextRenderer::endRender (_text_image.get());
        
        // Set the newly rendered image in the material
        font_material->setCurrentUnit(0);
        font_material->setTexture(_text_image);
    }
    
    if (_text_image.isValid()) {    
        DTfloat min_s = 0.0F;
        DTfloat min_t = 0.0F;
        DTfloat max_s = (_bounds.getPlusX() - _bounds.getMinusX()) * (DTfloat) System::getRenderer()->getScreenWidth() / ( (DTfloat) _text_image->getWidth() );
        DTfloat max_t = (_bounds.getPlusY() - _bounds.getMinusY()) * (DTfloat) System::getRenderer()->getScreenHeight() / ( (DTfloat) _text_image->getHeight() );

        font_material->setCurrentUnit(0);
        font_material->setTexture(_text_image);

        DrawBatcherQuads b;
        b.batchBegin(font_material, Matrix4::identity(), DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);
        
        Color cf(gui->getColor() * parent_color * (gui->getState() == GUIObject::STATE_FOCUSED ? _pressed_color : _normal_color));
        b.vertex(Vector3(_bounds.getMinusX(),_bounds.getMinusY(),0.0F), Texcoord2(min_s,min_t), cf );
        b.vertex(Vector3(_bounds.getPlusX(),_bounds.getMinusY(),0.0F), Texcoord2(max_s,min_t), cf );
        b.vertex(Vector3(_bounds.getPlusX(),_bounds.getPlusY(),0.0F), Texcoord2(max_s,max_t), cf );
        b.vertex(Vector3(_bounds.getMinusX(),_bounds.getPlusY(),0.0F), Texcoord2(min_s,max_t), cf );
        
        b.batchEnd();
        b.flush();
   
    }
    
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawTextAdvanced::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    GUIObject *gui = checkedCast<GUIObject*>(owner);
    if (gui) {
        gui->getDrawGUICallbacks().add(makeCallback(this, &type::draw));
    }
}

void ComponentGUIDrawTextAdvanced::removeFromOwner (void)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (gui) {
        gui->getDrawGUICallbacks().remove(makeCallback(this, &type::draw));
    }

    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

} // DT3

