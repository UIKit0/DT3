//==============================================================================
///	
///	File: ComponentGUIDrawText.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentGUIDrawText.hpp"
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
#include "GlyphCache.hpp"
#include <cmath>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentGUIDrawText,"GUI","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentGUIDrawText)

IMPLEMENT_PLUG_INFO(_font_material)
IMPLEMENT_PLUG_INFO(_font)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentGUIDrawText)
                        
    PLUG_INIT(_font_material, "Font_Material")
		.setInput(true);
        
    PLUG_INIT(_font, "Font")
		.setInput(true);
        
END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentGUIDrawText::ComponentGUIDrawText (void)
    :   _font_material      (PLUG_INFO(_font_material)),
        _font               (PLUG_INFO(_font)),
        _font_size          (10.0F),
        _font_color         (1.0F,1.0F,1.0F,1.0F),
        _justification      (TextCharacter::JUSTIFY_LEFT),
        _offset_x           (0.0F),
        _offset_y           (0.0F),
        _bounds             (0.0F,0.0F,0.0F,0.0F),
        _needs_render       (true),
        _can_render         (true),
        _text_image         (NULL)
{

}
		
ComponentGUIDrawText::ComponentGUIDrawText (const ComponentGUIDrawText &rhs)
    :   ComponentBase       (rhs),
        _font_material      (rhs._font_material),
        _font               (rhs._font),
        _font_size          (rhs._font_size),
        _font_color         (rhs._font_color),
        _justification      (rhs._justification),
        _offset_x           (rhs._offset_x),
        _offset_y           (rhs._offset_y),
        _bounds             (rhs._bounds),
        _needs_render       (true),
        _can_render         (true),
        _text_image         (rhs._text_image)
{

}

ComponentGUIDrawText & ComponentGUIDrawText::operator = (const ComponentGUIDrawText &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
                
        _font_material = rhs._font_material;
        _font = rhs._font;
        _font_size = rhs._font_size;
        _font_color = rhs._font_color;
        
        _justification = rhs._justification;
        _offset_x = rhs._offset_x;
        _offset_y = rhs._offset_y;

        _bounds = rhs._bounds;
        _needs_render = true;
        _can_render = true;
        
        _text_image = rhs._text_image;
    }
    return (*this);
}
			
ComponentGUIDrawText::~ComponentGUIDrawText (void)
{
    SystemCallbacks::getScreenOpenedCB().remove(makeCallback(this,&type::screenOpened));
    SystemCallbacks::getScreenClosedCB().remove(makeCallback(this,&type::screenClosed));
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawText::initialize (void)
{
	ComponentBase::initialize();
    
    SystemCallbacks::getScreenOpenedCB().add(makeCallback(this,&type::screenOpened));
    SystemCallbacks::getScreenClosedCB().add(makeCallback(this,&type::screenClosed));
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawText::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
        		    
	*archive << ARCHIVE_PLUG(_font_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_font, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_font_size, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_font_color, DATA_PERSISTENT | DATA_SETTABLE);

    if (archive->getVersion() >= 125)
        *archive << ARCHIVE_DATA(_justification, DATA_PERSISTENT | DATA_SETTABLE);    
    archive->pop_domain ();
}

void ComponentGUIDrawText::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	    
	*archive << ARCHIVE_PLUG(_font_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_font, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_font_size, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_font_color, DATA_PERSISTENT | DATA_SETTABLE);

    *archive << ARCHIVE_DATA(_justification, DATA_PERSISTENT | DATA_SETTABLE)
        .addEnum("Left")
        .addEnum("Right")
        .addEnum("Center")
        .addEnum("Full");    

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawText::screenOpened (DTuint width, DTuint height)
{
    // If for some reason the render context is created, we have to rerender
    
    _can_render = true;
    _needs_render = true;
}
        
void ComponentGUIDrawText::screenClosed (void)
{
    // If for some reason the render context is lost, we have to clean up

    _can_render = false;
    _needs_render = true;
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawText::render (void)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;

    FontResource *font = _font->get();
    DTfloat font_size = _font_size;
    Color font_color = _font_color;

    DTint width = (_bounds.getPlusX() - _bounds.getMinusX()) * System::getRenderer()->getScreenWidth();
    DTint height = (_bounds.getPlusY() - _bounds.getMinusY()) * System::getRenderer()->getScreenHeight();
    
    DTint width_pow2 = MoreMath::nextPower2(width);
    DTint height_pow2 = MoreMath::nextPower2(height);
    
    if (_text_image.isNull() || (_text_image->getWidth() != width_pow2) || (_text_image->getHeight() != height_pow2) ) {
    
        if (_text_image.isNull()) {
            _text_image = std::shared_ptr<TextureResource>(TextureResource::create());
        }
            
        _text_image->allocateRGBATextels2D(width_pow2, height_pow2, false);
    }
    
    // Build local transform for _bounds rectangle
    Matrix4 transform = gui->getTransform();
    
    DTfloat resolution_mul = System::getRenderer()->getScreenWidth() / 1024.0F;
    
    TextRenderer::beginRender (_text_image.get());
    
    GlyphCache cache;
    TextLines lines;
    lines.addLine( cache, Matrix4(transform), gui->getScale(), resolution_mul, gui->getLabel(), font, font_size, font_color, (TextCharacter::Justification)_justification);
    
    lines.wrap(width, height, TextLines::ALIGN_MIDDLE);
    TextRenderer::renderLines(_text_image.get(), lines);

    TextRenderer::endRender (_text_image.get());
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawText::draw (CameraObject* camera, const Color &parent_color)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;
    
    MaterialResource *font_material = _font_material->get();
    FontResource *font = _font->get();
    Color font_color = _font_color;

    if (!font_material || !font)
        return;
               
    if (gui->getColor().getA() * parent_color.getA() <= 0.0F)
        return;
       
    Rectangle local_rect = gui->getRectangle();
    DTfloat screen_width = System::getRenderer()->getViewportWidth();
    DTfloat screen_height = System::getRenderer()->getViewportHeight();
    
    // Snap to pixels
    local_rect.setMinusX( std::floor(local_rect.getMinusX() * screen_width) / screen_width);
    local_rect.setPlusX( std::floor(local_rect.getPlusX() * screen_width) / screen_width);
    local_rect.setMinusY( std::floor(local_rect.getMinusY() * screen_height) / screen_height);
    local_rect.setPlusY( std::floor(local_rect.getPlusY() * screen_height) / screen_height);
    
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
    
    if (bounds.getPlusX() < 0.0F)       return;
    if (bounds.getMinusX() > 1.0F)      return;
    if (bounds.getPlusY() < 0.0F)       return;
    if (bounds.getMinusY() > 1.0F)      return;
    
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
            
        _needs_render = false;
        _label = label;
    
        render();

        // Set the newly rendered image in the material
        font_material->setCurrentUnit(0);
        font_material->setTexture(_text_image);
    }
    
    if (_text_image.isValid()) {    
        DTfloat min_s = 0.0F;
        DTfloat min_t = 0.0F;
        DTfloat max_s = (_bounds.getPlusX() - _bounds.getMinusX()) / ( (DTfloat) _text_image->getWidth() / (DTfloat) System::getRenderer()->getScreenWidth());
        DTfloat max_t = (_bounds.getPlusY() - _bounds.getMinusY()) / ( (DTfloat) _text_image->getHeight() / (DTfloat) System::getRenderer()->getScreenHeight());

        font_material->setCurrentUnit(0);
        font_material->setTexture(_text_image);

        DrawBatcherQuads b;
        b.batchBegin(font_material, Matrix4::identity(), DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);
        
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

void ComponentGUIDrawText::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    GUIObject *gui = checkedCast<GUIObject*>(owner);
    if (gui) {
        gui->getDrawGUICallbacks().add(makeCallback(this, &type::draw));
    }
}

void ComponentGUIDrawText::removeFromOwner (void)
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

