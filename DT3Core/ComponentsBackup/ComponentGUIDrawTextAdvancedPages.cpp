//==============================================================================
///	
///	File: ComponentGUIDrawTextAdvancedPages.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentGUIDrawTextAdvancedPages.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "MaterialResource.hpp"
#include "TextureResource.hpp"
#include "FontResource.hpp"
#include "World.hpp"
#include "GUIObject.hpp"
#include "GUITouchEvent.hpp"
#include "DrawBatcherQuads.hpp"
#include "MoreMath.hpp"
#include "TextRenderer.hpp"
#include "System.hpp"
#include "SystemCallbacks.hpp"
#include "DeviceGraphics.hpp"
#include "Globals.hpp"
#include "DrawUtils.hpp"
#include "GlyphCache.hpp"
#include "ConsoleStream.hpp"
#include <cmath>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentGUIDrawTextAdvancedPages,"GUI","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentGUIDrawTextAdvancedPages)

IMPLEMENT_PLUG_INFO(_font_material)
IMPLEMENT_PLUG_INFO(_page_indicator_material)
IMPLEMENT_PLUG_INFO(_page_indicator_material_selected)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentGUIDrawTextAdvancedPages)
                        
    PLUG_INIT(_font_material, "Font_Material")
		.setInput(true);
                
    PLUG_INIT(_page_indicator_material, "Page_Indicator_Material")
		.setInput(true);
                
    PLUG_INIT(_page_indicator_material_selected, "Page_Indicator_Material_Selected")
		.setInput(true);
                
END_IMPLEMENT_PLUGS

//==============================================================================
//==============================================================================

const DTfloat ComponentGUIDrawTextAdvancedPages::PADDING = 0.05F;

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentGUIDrawTextAdvancedPages::ComponentGUIDrawTextAdvancedPages (void)
    :   _font_material                      (PLUG_INFO(_font_material)),
        _page_indicator_material            (PLUG_INFO(_page_indicator_material)),
        _page_indicator_material_selected   (PLUG_INFO(_page_indicator_material_selected)),
        _bounds                             (0.0F,0.0F,0.0F,0.0F),
        _needs_render                       (true),
        _can_render                         (true),
        _page_bar_height                    (16.0F/768.0F),
        _page_button_spacing                (12.0F/1024.0F),
        _page_button_size                   (8.0F/768.0F),
        _current_page                       (0),
        _current_page_pos                   (0.0F),
        _scroll_accum                       (0.0F)
{

}
		
ComponentGUIDrawTextAdvancedPages::ComponentGUIDrawTextAdvancedPages (const ComponentGUIDrawTextAdvancedPages &rhs)
    :   ComponentBase                       (rhs),
        _font_material                      (rhs._font_material),
        _page_indicator_material            (rhs._page_indicator_material),
        _page_indicator_material_selected   (rhs._page_indicator_material_selected),
        _bounds                             (rhs._bounds),
        _needs_render                       (true),
        _can_render                         (true),
        _page_bar_height                    (rhs._page_bar_height),
        _page_button_spacing                (rhs._page_button_spacing),
        _page_button_size                   (rhs._page_button_size),
        _current_page                       (0),
        _current_page_pos                   (rhs._current_page_pos),
        _scroll_accum                       (0.0F)
{
    _pages.clear();
}

ComponentGUIDrawTextAdvancedPages & ComponentGUIDrawTextAdvancedPages::operator = (const ComponentGUIDrawTextAdvancedPages &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
                
        _font_material = rhs._font_material;
        
        _bounds = rhs._bounds;
        _needs_render = true;
        _can_render = true;
        _page_bar_height = rhs._page_bar_height;
        _page_button_spacing = rhs._page_button_spacing;
        _page_button_size = rhs._page_button_size;
        _current_page = rhs._current_page;
        _current_page_pos = rhs._current_page_pos;
        
        _pages.clear();
    }
    return (*this);
}
			
ComponentGUIDrawTextAdvancedPages::~ComponentGUIDrawTextAdvancedPages (void)
{
    SystemCallbacks::getScreenOpenedCB().remove(makeCallback(this,&type::screenOpened));    
    SystemCallbacks::getScreenClosedCB().remove(makeCallback(this,&type::screenClosed));
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawTextAdvancedPages::initialize (void)
{
	ComponentBase::initialize();
    
    SystemCallbacks::getScreenOpenedCB().add(makeCallback(this,&type::screenOpened));
    SystemCallbacks::getScreenClosedCB().add(makeCallback(this,&type::screenClosed));
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawTextAdvancedPages::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
        		    
	*archive << ARCHIVE_PLUG(_font_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_page_indicator_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_page_indicator_material_selected, DATA_PERSISTENT | DATA_SETTABLE);
    if (archive->getVersion() < 1381) {
        DTboolean _color;
        *archive << ARCHIVE_DATA(_color, DATA_PERSISTENT | DATA_SETTABLE);
    }
	*archive << ARCHIVE_DATA(_page_bar_height, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_page_button_spacing, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_page_button_size, DATA_PERSISTENT | DATA_SETTABLE);
        
    archive->pop_domain ();
}

void ComponentGUIDrawTextAdvancedPages::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	    
	*archive << ARCHIVE_PLUG(_font_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_page_indicator_material, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_page_indicator_material_selected, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_page_bar_height, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_page_button_spacing, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_page_button_size, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawTextAdvancedPages::screenOpened (DTuint width, DTuint height)
{
    // If for some reason the render context is created, we have to rerender
    
    _can_render = true;
    _needs_render = true;
}
        
void ComponentGUIDrawTextAdvancedPages::screenClosed (void)
{
    // If for some reason the render context is lost, we have to clean up

    _can_render = false;
    _needs_render = true;
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawTextAdvancedPages::tick (DTfloat dt)
{
    if (_scroll_accum == 0.0F)
        _current_page_pos = 0.65F * _current_page_pos + 0.35F * _current_page;
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawTextAdvancedPages::draw (CameraObject* camera, const Color &parent_color)
{        
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui) {
        _pages.clear();
        _needs_render = true;
        return;
    }
    
    MaterialResource *font_material = _font_material->get();

    if (gui->getColor().getA() * parent_color.getA() <= 0.0F) {
        _pages.clear();
        _needs_render = true;
        return;
    }
   
    Rectangle local_rect = gui->getRectangle();
    DTfloat screen_width = System::getRenderer()->getViewportWidth();
    DTfloat screen_aspect = System::getRenderer()->getViewportAspect();
    
    //
    // Check screen space rectangle to see if it has changed
    //
    
    Matrix4 transform = gui->getDrawTransform();

    Vector2 p0 = transform * Vector2(local_rect.getMinusX(), local_rect.getMinusY() + _page_bar_height);
    Vector2 p1 = transform * Vector2(local_rect.getPlusX(), local_rect.getMinusY() + _page_bar_height);
    Vector2 p2 = transform * Vector2(local_rect.getMinusX(), local_rect.getPlusY());
    Vector2 p3 = transform * Vector2(local_rect.getPlusX(), local_rect.getPlusY());

    Rectangle bounds;
    bounds.setMinusX( min4(p0.x, p1.x, p2.x, p3.x) );
    bounds.setPlusX( max4(p0.x, p1.x, p2.x, p3.x) );
    bounds.setMinusY( min4(p0.y, p1.y, p2.y, p3.y) );
    bounds.setPlusY( max4(p0.y, p1.y, p2.y, p3.y) );
        
    if (!bounds.isTouching( Rectangle(0.0F,1.0F,0.0F,1.0F) ) ) {
        _pages.clear();
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
        
        //
        // Render Text boxes
        //
            
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
        
        //
        // Paginate Text
        //

        GlyphCache cache;
        TextLines lines;

        Matrix3 orientation = gui->getTransform().orientation();
        orientation.ortho();

        DTfloat resolution_mul = System::getRenderer()->getScreenWidth() / 1024.0F;

        lines.addLine( cache, Matrix4(orientation), gui->getScale(), resolution_mul, gui->getLabel() );

        // First Wrap the text
        lines.wrap(box_width, box_height, TextLines::ALIGN_TOP);   

        // Then paginate the text
        std::list<TextLines> page_lines = lines.paginate(box_width, box_height);
        _pages.resize(page_lines.size());

        std::list<Page>::iterator p;
        std::list<TextLines>::iterator pl;
        DTuint pi;

        for (p = _pages.begin(), pl = page_lines.begin(), pi = 0; p != _pages.end(); ++p,++pl,++pi) {
            Page &page = *p;
            
            if (page._text_image.isNull() || (page._text_image->getWidth() != tex_width_pow2) || (page._text_image->getHeight() != tex_height_pow2) ) {
            
                if (page._text_image.isNull()) {
                    page._text_image = std::shared_ptr<TextureResource>(TextureResource::create());
                }
                    
                page._text_image->allocateRGBATextels2D (tex_width_pow2, tex_height_pow2, false);
            }
                
            TextRenderer::beginRender (page._text_image.get());
            TextRenderer::renderLines(page._text_image.get(), (*pl), offset);
            TextRenderer::endRender (page._text_image.get());
            
            // Page buttons
            Vector2 base_position = Vector2(-_page_bar_height * (_pages.size() - 1.0F) / 2.0F, (-gui->getHeight() + _page_bar_height) * 0.5);
            base_position.x = base_position.x + _page_bar_height * pi;
            page._page_button.set(base_position.x - _page_button_size*0.5F / screen_aspect, base_position.x + _page_button_size*0.5F / screen_aspect, base_position.y - _page_button_size*0.5F, base_position.y + _page_button_size*0.5F);
        }
    }
    
    // Draw pages
    std::list<Page>::iterator p;
    DTuint pi;

    for (p = _pages.begin(), pi = 0; p != _pages.end(); ++p,++pi) {
        std::shared_ptr<TextureResource> _text_image = (*p)._text_image;
        DTfloat offset_x = (pi - _current_page_pos) * (gui->getWidth() + PADDING);
    
        DTfloat min_s = 0.0F;
        DTfloat min_t = 0.0F;
        DTfloat max_s = (_bounds.getPlusX() - _bounds.getMinusX()) * (DTfloat) System::getRenderer()->getScreenWidth() / ( (DTfloat) _text_image->getWidth() );
        DTfloat max_t = (_bounds.getPlusY() - _bounds.getMinusY()) * (DTfloat) System::getRenderer()->getScreenHeight() / ( (DTfloat) _text_image->getHeight() );

        font_material->setCurrentUnit(0);
        font_material->setTexture(_text_image);

        DrawBatcherQuads b;
        b.batchBegin(font_material, Matrix4::identity(), DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);
        
        Color cf(gui->getColor() * parent_color);
        b.vertex(Vector3(_bounds.getMinusX() + offset_x,_bounds.getMinusY(),0.0F), Texcoord2(min_s,min_t), cf );
        b.vertex(Vector3(_bounds.getPlusX() + offset_x,_bounds.getMinusY(),0.0F), Texcoord2(max_s,min_t), cf );
        b.vertex(Vector3(_bounds.getPlusX() + offset_x,_bounds.getPlusY(),0.0F), Texcoord2(max_s,max_t), cf );
        b.vertex(Vector3(_bounds.getMinusX() + offset_x,_bounds.getPlusY(),0.0F), Texcoord2(min_s,max_t), cf );
        
        b.batchEnd();
        b.flush();
    }
    
    if (_pages.size() > 1) {
        // Draw buttons
        for (p = _pages.begin(), pi = 0; p != _pages.end(); ++p,++pi) {
            Page &page = *p;
            
            DrawBatcherQuads b;
            
            if (pi == _current_page)    b.batchBegin(_page_indicator_material_selected->get(), gui->getDrawTransform(), DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);
            else                        b.batchBegin(_page_indicator_material->get(), gui->getDrawTransform(), DrawBatcherQuads::FMT_V | DrawBatcherQuads::FMT_T1 | DrawBatcherQuads::FMT_C);
            
            Color cf(gui->getColor() * parent_color);
            b.vertex(Vector3(page._page_button.getMinusX(),page._page_button.getMinusY(),0.0F), Texcoord2(0.0F,0.0F), cf );
            b.vertex(Vector3(page._page_button.getPlusX(),page._page_button.getMinusY(),0.0F), Texcoord2(1.0F,0.0F), cf );
            b.vertex(Vector3(page._page_button.getPlusX(),page._page_button.getPlusY(),0.0F), Texcoord2(1.0F,1.0F), cf );
            b.vertex(Vector3(page._page_button.getMinusX(),page._page_button.getPlusY(),0.0F), Texcoord2(0.0F,1.0F), cf );
            
            b.batchEnd();
            b.flush();
        
        }
    }
    
    
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawTextAdvancedPages::touchesBegan (GUITouchEvent *event)
{
    _scroll_accum = 0.0F;
}

void ComponentGUIDrawTextAdvancedPages::touchesMoved (GUITouchEvent *event)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui) {
        return;
    }

    //DTfloat width = System::getRenderer()->getScreenWidth();
    //DTfloat delta = (event->getPosition().x - event->getPreviousPosition().x) / (DTfloat) width;
    
    Vector2 delta = gui->velocityToObjectCoord(event->getPosition() - event->getPreviousPosition());

    
    _scroll_accum += delta.x;
    _current_page_pos -= delta.x / gui->getWidth();
}

void ComponentGUIDrawTextAdvancedPages::touchesEnded (GUITouchEvent *event)
{
    if ( _scroll_accum > 0.1F) {
        --_current_page;
        if (_current_page < 0)
            _current_page = 0;
    }
    if ( _scroll_accum < -0.1F) {
        ++_current_page;
        if (_current_page >= _pages.size())
            _current_page = (DTint) (_pages.size()-1);
    }
    
    _scroll_accum = 0.0F;
}

void ComponentGUIDrawTextAdvancedPages::touchesCancelled (GUITouchEvent *event)
{
    _scroll_accum = 0.0F;
}

//==============================================================================
//==============================================================================

void ComponentGUIDrawTextAdvancedPages::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    GUIObject *gui = checkedCast<GUIObject*>(owner);
    if (gui) {
        gui->getTouchesBeganCallbacks().add(makeCallback(this, &type::touchesBegan));
        gui->getTouchesMovedCallbacks().add(makeCallback(this, &type::touchesMoved));
        gui->getTouchesEndedCallbacks().add(makeCallback(this, &type::touchesEnded));
        gui->getTouchesCancelledCallbacks().add(makeCallback(this, &type::touchesCancelled));
        gui->getDrawGUICallbacks().add(makeCallback(this, &type::draw));
    }
    
    World *w = getOwner()->getWorld();
    w->registerForTick(getOwner(), makeCallback(this, &type::tick));

}

void ComponentGUIDrawTextAdvancedPages::removeFromOwner (void)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (gui) {
        gui->getTouchesBeganCallbacks().remove(makeCallback(this, &type::touchesBegan));
        gui->getTouchesMovedCallbacks().remove(makeCallback(this, &type::touchesMoved));
        gui->getTouchesEndedCallbacks().remove(makeCallback(this, &type::touchesEnded));
        gui->getTouchesCancelledCallbacks().remove(makeCallback(this, &type::touchesCancelled));
        gui->getDrawGUICallbacks().remove(makeCallback(this, &type::draw));
    }

    World *w = getOwner()->getWorld();
    w->unregisterForTick(getOwner(), makeCallback(this, &type::tick));

    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

} // DT3

