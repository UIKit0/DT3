//==============================================================================
///	
///	File: ComponentGUIDrawButton.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentGUIDrawButton.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "MaterialResource.hpp"
#include "TextureResource.hpp"
#include "FontResource.hpp"
#include "World.hpp"
#include "GUIObject.hpp"
#include "DrawBatcher.hpp"
#include "DrawBatcherQuads.hpp"
#include "MoreMath.hpp"
#include "TextRenderer.hpp"
#include "System.hpp"
#include "SystemCallbacks.hpp"
#include "DeviceGraphics.hpp"
#include "Globals.hpp"
#include "DrawUtils.hpp"
#include "GlyphCache.hpp"
#include <cmath>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentGUIDrawButton,"GUI","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentGUIDrawButton)

IMPLEMENT_PLUG_INFO(_material)
IMPLEMENT_PLUG_INFO(_pressed_material)
IMPLEMENT_PLUG_INFO(_color)
IMPLEMENT_PLUG_INFO(_font_material)
IMPLEMENT_PLUG_INFO(_font)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentGUIDrawButton)
        
    PLUG_INIT(_material, "Material")
		.setInput(true);
                
    PLUG_INIT(_pressed_material, "Pressed_Material")
		.setInput(true);
                
    PLUG_INIT(_font_material, "Font_Material")
		.setInput(true);
        
    PLUG_INIT(_font, "Font")
		.setInput(true);
        
END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentGUIDrawButton::ComponentGUIDrawButton (void)
    :   _material           (PLUG_INFO(_material)),
        _pressed_material   (PLUG_INFO(_pressed_material)),
        _font_material      (PLUG_INFO(_font_material)),
        _font               (PLUG_INFO(_font)),
        _font_size          (0.0F),
        _font_color         (1.0F,1.0F,1.0F,1.0F),
        _corner_width       (0.0F),
        _corner_height      (0.0F),
        _offset_x           (0.0F),
        _offset_y           (0.0F),
        _bounds             (0.0F,0.0F,0.0F,0.0F),
        _needs_render       (true),
        _can_render         (true)
{

}
		
ComponentGUIDrawButton::ComponentGUIDrawButton (const ComponentGUIDrawButton &rhs)
    :   ComponentBase       (rhs),
        _material           (rhs._material),
        _pressed_material   (rhs._pressed_material),
        _font_material      (rhs._font_material),
        _font               (rhs._font),
        _font_size          (rhs._font_size),
        _font_color         (rhs._font_color),
        _corner_width       (rhs._corner_width),
        _corner_height      (rhs._corner_height),
        _offset_x           (rhs._offset_x),
        _offset_y           (rhs._offset_y),
        _bounds             (rhs._bounds),
        _needs_render       (true),
        _can_render         (true),
        _text_image         (rhs._text_image)
{

}

ComponentGUIDrawButton & ComponentGUIDrawButton::operator = (const ComponentGUIDrawButton &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        
        _material = rhs._material;
        _pressed_material = rhs._pressed_material;
        
        _font_material = rhs._font_material;
        _font = rhs._font;
        _font_size = rhs._font_size;
        _font_color = rhs._font_color;
        
        _corner_width = rhs._corner_width;
        _corner_height = rhs._corner_height;

        _offset_x = rhs._offset_x;
        _offset_y = rhs._offset_y;

        _bounds = rhs._bounds;
        _needs_render = true;
        _can_render = true;
        
        _text_image = rhs._text_image;
    }
    return (*this);
}
			
ComponentGUIDrawButton::~ComponentGUIDrawButton (void)
{
    SystemCallbacks::getScreenOpenedCB().remove(makeCallback(this,&type::screenOpened));
    SystemCallbacks::getScreenClosedCB().remove(makeCallback(this,&type::screenClosed));
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawButton::initialize (void)
{
	ComponentBase::initialize();
    
    SystemCallbacks::getScreenOpenedCB().add(makeCallback(this,&type::screenOpened));
    SystemCallbacks::getScreenClosedCB().add(makeCallback(this,&type::screenClosed));
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawButton::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
        		
	*archive << ARCHIVE_PLUG(_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_pressed_material, DATA_PERSISTENT | DATA_SETTABLE);
    
	*archive << ARCHIVE_PLUG(_font_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_font, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_font_size, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_font_color, DATA_PERSISTENT | DATA_SETTABLE);
    
	*archive << ARCHIVE_DATA(_corner_width, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_corner_height, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA(_offset_x, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_offset_y, DATA_PERSISTENT | DATA_SETTABLE);
    
    archive->pop_domain ();
}

void ComponentGUIDrawButton::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	
	*archive << ARCHIVE_PLUG(_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_pressed_material, DATA_PERSISTENT | DATA_SETTABLE);
    
	*archive << ARCHIVE_PLUG(_font_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_font, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_font_size, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_font_color, DATA_PERSISTENT | DATA_SETTABLE);
    
	*archive << ARCHIVE_DATA(_corner_width, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_corner_height, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA(_offset_x, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_offset_y, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawButton::screenOpened (DTuint width, DTuint height)
{
    // If for some reason the render context is created, we have to rerender
    
    _can_render = true;
    _needs_render = true;
}
        
void ComponentGUIDrawButton::screenClosed (void)
{
    // If for some reason the render context is lost, we have to clean up

    _can_render = false;
    _needs_render = true;
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawButton::render (void)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;
        
    FontResource *font = _font->get();
    DTfloat font_size = _font_size;
    Color font_color = _font_color;
    
    DTfloat offset_x = _offset_x;
    DTfloat offset_y = _offset_y;

    DTint width = (_bounds.getPlusX() - _bounds.getMinusX()) * System::getRenderer()->getScreenWidth();
    DTint height = (_bounds.getPlusY() - _bounds.getMinusY()) * System::getRenderer()->getScreenHeight();
    
    DTint width_pow2 = MoreMath::nextPower2(width);
    DTint height_pow2 = MoreMath::nextPower2(height);
    
    if (_text_image.isNull() || (_text_image->getWidth() != width_pow2) || (_text_image->getHeight() != height_pow2) ) {
    
        if (_text_image.isNull()) {
            _text_image = std::shared_ptr<TextureResource>(TextureResource::create());
        }
            
        _text_image->allocateRGBATextels2D (width_pow2, height_pow2, false);
    }
    
    // Build local transform for _bounds rectangle
    Matrix4 transform = gui->getTransform();
    transform._m14 = offset_x;
    transform._m24 = offset_y;
    
    String label = Globals::substituteGlobal(gui->getLabel());
    DTfloat resolution_mul = System::getRenderer()->getScreenWidth() / 1024.0F;

    TextRenderer::beginRender (_text_image.get());

    GlyphCache cache;
    TextLines lines;
    lines.addLine( cache, Matrix4(transform), gui->getScale(), resolution_mul, gui->getLabel(), font, font_size, font_color, TextCharacter::JUSTIFY_CENTER);
    
    lines.wrap(width, height, TextLines::ALIGN_MIDDLE);
    TextRenderer::renderLines(_text_image.get(), lines);

    TextRenderer::endRender (_text_image.get());
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawButton::draw (CameraObject* camera, const Color &parent_color)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;
    
    MaterialResource *material = _material->get();
    MaterialResource *pressed_material = _pressed_material->get();
    FontResource *font = _font->get();
    MaterialResource *font_material = _font_material->get();
    Color font_color = _font_color;
    DTfloat corner_width = _corner_width;
    DTfloat corner_height = _corner_height;

    if (!material || !font_material || !font)
        return;
               
    if (gui->getColor().getA() * parent_color.getA() <= 0.0F)
        return;
       
    Rectangle local_rect = gui->getRectangle();
    DTfloat screen_width = System::getRenderer()->getViewportWidth();
    //DTfloat screen_height = System::getRenderer()->getViewportHeight();
        
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
    
    DTfloat new_width = bounds.getPlusX() - bounds.getMinusX();
    DTfloat new_height = bounds.getPlusY() - bounds.getMinusY();

    DTfloat width = _bounds.getPlusX() - _bounds.getMinusX();
    DTfloat height = _bounds.getPlusY() - _bounds.getMinusY();
    
    _bounds = bounds;

    const DTfloat TOLERANCE = 1.0F / screen_width;
    String full_label = Globals::substituteGlobal(gui->getLabel());
    
    if ((   (fabsf(new_width-width) > TOLERANCE) || 
            (fabsf(new_height-height) > TOLERANCE) || 
            _label != full_label || _needs_render) && _can_render && font_material) {

        _needs_render = false;
        _label = full_label;
    
        render();

        // Set the newly rendered image in the material
        font_material->setCurrentUnit(0);
        font_material->setTexture(_text_image);
    }
        
    DrawBatcherQuads b;
    
    // Get Alternate materials
    Color c = gui->getColor() * parent_color;
    MaterialResource *m = material;

    if (_pressed_material->isValid()) {
        if (gui->getState() == GUIObject::STATE_FOCUSED) 
            m = pressed_material;
        
    } else {
        if (gui->getState() == GUIObject::STATE_FOCUSED) 
            c = c * Color(0.7F,0.7F,0.7F,1.0F);
    }


    // Draw background    
    if (corner_width > 0.0F || corner_height > 0.0F) {
        DrawUtils::drawQuadStretchCenter (
            b, m, c, 
            transform, 
            local_rect.getMinusX(), local_rect.getMinusY(), 
            local_rect.getWidth(), local_rect.getHeight(), 
            corner_width, corner_height, 
            false);
    } else {
        DrawUtils::drawQuad (
            b, m, c, 
            transform, 
            local_rect.getMinusX(), local_rect.getMinusY(), 
            local_rect.getWidth(), local_rect.getHeight(), 
            false);
    }

    b.flush();

    
    if (_text_image.isValid()) {
    
        DTfloat min_s = 0.0F;
        DTfloat min_t = 0.0F;
        DTfloat max_s = (_bounds.getPlusX() - _bounds.getMinusX()) / ( (DTfloat) _text_image->getWidth() / (DTfloat) System::getRenderer()->getScreenWidth());
        DTfloat max_t = (_bounds.getPlusY() - _bounds.getMinusY()) / ( (DTfloat) _text_image->getHeight() / (DTfloat) System::getRenderer()->getScreenHeight());

        font_material->setCurrentUnit(0);
        font_material->setTexture(_text_image);

        b.batchBegin(font_material, Matrix4::identity(), DrawBatcher::FMT_V | DrawBatcher::FMT_T1 | DrawBatcher::FMT_C);
        
        Color cf(font_color * gui->getColor() * parent_color);
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

void ComponentGUIDrawButton::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    GUIObject *gui = checkedCast<GUIObject*>(owner);
    if (gui) {
        gui->getDrawGUICallbacks().add(makeCallback(this, &ComponentGUIDrawButton::draw));
    }
}

void ComponentGUIDrawButton::removeFromOwner (void)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (gui) {
        gui->getDrawGUICallbacks().remove(makeCallback(this, &ComponentGUIDrawButton::draw));
    }

    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

} // DT3

