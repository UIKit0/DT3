//==============================================================================
///	
///	File: ComponentDrawText.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentDrawText.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "MaterialResource.hpp"
#include "TextureResource.hpp"
#include "FontResource.hpp"
#include "World.hpp"
#include "PlaceableObject.hpp"
#include "CameraObject.hpp"
#include "DrawBatcherQuads.hpp"
#include "MoreMath.hpp"
#include "TextRenderer.hpp"
#include "System.hpp"
#include "SystemCallbacks.hpp"
#include "DeviceGraphics.hpp"
#include "DrawUtils.hpp"
#include "GlyphCache.hpp"
#include "Callback.hpp"
#include <cmath>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentDrawText,"Drawing","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentDrawText)

IMPLEMENT_PLUG_INFO(_font_material)
IMPLEMENT_PLUG_INFO(_font)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentDrawText)
                        
    PLUG_INIT(_font_material, "Font_Material")
		.setInput(true);
        
    PLUG_INIT(_font, "Font")
		.setInput(true);
        
END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentDrawText::ComponentDrawText (void)
    :   _font_material      (PLUG_INFO(_font_material)),
        _font               (PLUG_INFO(_font)),
        _font_size          (10.0F),
        _font_color         (1.0F,1.0F,1.0F,1.0F),
        _needs_render       (true),
        _can_render         (true),
        _text_image         (NULL)
{

}
		
ComponentDrawText::ComponentDrawText (const ComponentDrawText &rhs)
    :   ComponentBase       (rhs),
        _font_material      (rhs._font_material),
        _font               (rhs._font),
        _font_size          (rhs._font_size),
        _font_color         (rhs._font_color),
        _needs_render       (true),
        _can_render         (true),
        _text_image         (rhs._text_image)
{

}

ComponentDrawText & ComponentDrawText::operator = (const ComponentDrawText &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
                
        _font_material = rhs._font_material;
        _font = rhs._font;
        _font_size = rhs._font_size;
        _font_color = rhs._font_color;
        
        _needs_render = true;
        _can_render = true;
        
        _text_image = rhs._text_image;
    }
    return (*this);
}
			
ComponentDrawText::~ComponentDrawText (void)
{
    SystemCallbacks::getScreenOpenedCB().remove(makeCallback(this,&type::screenOpened));
    SystemCallbacks::getScreenClosedCB().remove(makeCallback(this,&type::screenClosed));
}

//==============================================================================
//==============================================================================

void ComponentDrawText::initialize (void)
{
	ComponentBase::initialize();
    
    SystemCallbacks::getScreenOpenedCB().add(makeCallback(this,&type::screenOpened));
    SystemCallbacks::getScreenClosedCB().add(makeCallback(this,&type::screenClosed));
}

//==============================================================================
//==============================================================================

void ComponentDrawText::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
        		    
	*archive << ARCHIVE_PLUG(_font_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_font, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_font_size, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_font_color, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA(_text_image_width, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_text_image_height, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA(_label, DATA_PERSISTENT | DATA_SETTABLE);
    
    archive->pop_domain ();
}

void ComponentDrawText::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	    
	*archive << ARCHIVE_PLUG(_font_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_font, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_font_size, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_font_color, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA(_text_image_width, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_text_image_height, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA(_label, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentDrawText::screenOpened (DTuint width, DTuint height)
{
    // If for some reason the render context is created, we have to rerender
    
    _can_render = true;
    _needs_render = true;
}
        
void ComponentDrawText::screenClosed (void)
{
    // If for some reason the render context is lost, we have to clean up

    _can_render = false;
    _needs_render = true;
}

//==============================================================================
//==============================================================================

void ComponentDrawText::render (void)
{
    PlaceableObject *object = checkedCast<PlaceableObject*>(getOwner());
    if (!object)
        return;
    
    DTint width_pow2 = MoreMath::nextPower2(_text_image_width);
    DTint height_pow2 = MoreMath::nextPower2(_text_image_height);
    
    if (_text_image.isNull() || (_text_image->getWidth() != width_pow2) || (_text_image->getHeight() != height_pow2) ) {
    
        if (_text_image.isNull()) {
            _text_image = std::shared_ptr<TextureResource>(TextureResource::create());
        }
        
        _text_image->allocateRGBATextels2D (width_pow2, height_pow2, false);
    }
    
    // Build local transform for _bounds rectangle
    Matrix4 transform = object->getTransform();
    transform._m14 = 0.0F;
    transform._m24 = 0.0F;
    transform._m34 = 0.0F;
    
    DTfloat resolution_mul = System::getRenderer()->getScreenWidth() / 1024.0F;

    TextRenderer::beginRender (_text_image.get());
    
    GlyphCache cache;
    TextLines lines;
    lines.addLine( cache, Matrix4(transform), object->getScale(), resolution_mul, getLabel() );
    
    lines.wrap(_text_image_width, _text_image_height, TextLines::ALIGN_MIDDLE);
    TextRenderer::renderLines(_text_image.get(), lines);

    TextRenderer::endRender (_text_image.get());
}

//==============================================================================
//==============================================================================

void ComponentDrawText::draw (CameraObject* camera)
{
    if (_font_material->isNull() || _font->isNull())
        return;
        
    if (_font_color.getA() <= 0.0F)
        return;
        
    PlaceableObject *object = checkedCast<PlaceableObject*>(getOwner());
    if (!object)
        return;
              
    Vector3 screen_pos = camera->projectPoint(object->getTranslation());
    

    
#if DT3_EDITOR
    _needs_render = true;   // always render in editor
#endif
    
    if (_needs_render && _can_render && _font_material->isValid()) {
            
        _needs_render = false;
    
        render();

        // Set the newly rendered image in the material
        (*_font_material)->setCurrentUnit(0);
        (*_font_material)->setTexture(_text_image);
    }
    
    if (_text_image.isValid()) {    
        DTfloat min_s = 0.5F - (DTfloat) _text_image_width / (DTfloat) _text_image->getWidth() * 0.5F;
        DTfloat max_s = 0.5F + (DTfloat) _text_image_width / (DTfloat) _text_image->getWidth() * 0.5F;
        DTfloat min_t = 0.5F - (DTfloat) _text_image_height / (DTfloat) _text_image->getHeight() * 0.5F;
        DTfloat max_t = 0.5F + (DTfloat) _text_image_height / (DTfloat) _text_image->getHeight() * 0.5F;

        (*_font_material)->setCurrentUnit(0);
        (*_font_material)->setTexture(_text_image);
        
        DTfloat pixel_width = (DTfloat) _text_image_width / (DTfloat) System::getRenderer()->getScreenWidth();
        DTfloat pixel_height = (DTfloat) _text_image_height / (DTfloat) System::getRenderer()->getScreenHeight();
        
        // Override the camera with a screen aligned one
        CameraObject gui_camera;
        gui_camera.setOrtho(-1.0F,1.0F,-1.0F,1.0F,1.0F,-1.0F);
        
        DrawUtils::activateCamera(&gui_camera);

        DrawBatcherQuads b;
        b.batchBegin(_font_material->get(), Matrix4::identity(), DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);
        
        Color cf(_font_color);
        b.vertex(screen_pos + Vector3(-pixel_width, -pixel_height, 0.0F), Texcoord2(min_s,min_t), cf );
        b.vertex(screen_pos + Vector3(pixel_width, -pixel_height, 0.0F), Texcoord2(max_s,min_t), cf );
        b.vertex(screen_pos + Vector3(pixel_width, pixel_height, 0.0F), Texcoord2(max_s,max_t), cf );
        b.vertex(screen_pos + Vector3(-pixel_width ,pixel_height, 0.0F), Texcoord2(min_s,max_t), cf );
        
        b.batchEnd();
        b.flush();
   
        DrawUtils::activateCamera(camera);

    }
    
}

//==============================================================================
//==============================================================================

void ComponentDrawText::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    World *w = getOwner()->getWorld();

    w->registerForDraw(getOwner(), makeCallback(this, &type::draw));
}

void ComponentDrawText::removeFromOwner (void)
{
    World *w = getOwner()->getWorld();

    w->unregisterForDraw(getOwner(), makeCallback(this, &type::draw));

    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

} // DT3

