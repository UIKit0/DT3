#ifndef DT3_ComponentGUIDrawTextAdvancedPagesPAGES
#define DT3_ComponentGUIDrawTextAdvancedPagesPAGES
//==============================================================================
///	
///	File: ComponentGUIDrawTextAdvancedPages.hpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentBase.hpp"
#include "Callback.hpp"
#include "Rectangle.hpp"
#include "TextLines.hpp"

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class MaterialResource;
class TextureResource;
class FontResource;
class CameraObject;
class GUITouchEvent;

//==============================================================================
/// GUI drawing for text that supports different fonts and styles. This
/// Widget will show "bubbles" for multiple pages and will let you
/// scroll through them. See ComponentGUIDrawTextAdvanced for
/// formatting options.
//==============================================================================

class ComponentGUIDrawTextAdvancedPages: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentGUIDrawTextAdvancedPages,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                            ComponentGUIDrawTextAdvancedPages	(void);	
                                            ComponentGUIDrawTextAdvancedPages	(const ComponentGUIDrawTextAdvancedPages &rhs);
        ComponentGUIDrawTextAdvancedPages&  operator =                          (const ComponentGUIDrawTextAdvancedPages &rhs);	
        virtual                             ~ComponentGUIDrawTextAdvancedPages  (void);
    
        virtual void                archive_read			(Archive *archive);
        virtual void                archive_write		(Archive *archive);
		
	public:
		/// Called to initialize the object
		virtual void				initialize			(void);
        
		/// Returns the component type. This defines which slot the component is
        /// put into on the object.
		/// \return Component type
        virtual ComponentType       getComponentType    (void)  {   return COMPONENT_DRAW;  }

		/// Callback called when the component is getting a touch begin event
		/// \param event Touch events
        void                        touchesBegan        (GUITouchEvent *event);

		/// Callback called when the component is getting a touch move event
		/// \param event Touch events
        void                        touchesMoved        (GUITouchEvent *event);        
        
		/// Callback called when the component is getting a touch end event
		/// \param event Touch events
        void                        touchesEnded        (GUITouchEvent *event);

		/// Callback called when the component is getting a touch cancelled event
		/// \param event Touch events
        void                        touchesCancelled    (GUITouchEvent *event);

		/// Callback called when the component is getting a tick
		/// \param dt delta time
        void                        tick                (DTfloat dt);

		/// Draw Callback for component
		/// \param camera Camera used for drawing
		/// \param parent_color Color of the parent GUI Object
        void                        draw                (CameraObject* camera, const Color &parent_color);
        

        
		/// Called when this component is added to the owner. Note that this will
        /// only be called if the owner is added to a world already. If not it 
        /// will be called when it is added to the World.
		/// \param owner Pointer to the owner
		virtual void                addToOwner          (ObjectBase *owner);

		/// Called when this component is removed from its owner.
		virtual void                removeFromOwner     (void);

		/// Screen created callback.
        void                        screenOpened        (DTuint width, DTuint height);
        
		/// Screen destroyed callback.
        void                        screenClosed        (void);
                
        /// Defines standard accessors for the font material
  		DEFINE_ACCESSORS		(getFontMaterial, setFontMaterial, std::shared_ptr<MaterialResource>, _font_material);

        /// Defines standard accessors for the page indicator material
  		DEFINE_ACCESSORS		(getPageIndicatorMaterial, setPageIndicatorMaterial, std::shared_ptr<MaterialResource>, _page_indicator_material);

        /// Defines standard accessors for the page selected indicator material
  		DEFINE_ACCESSORS		(getPageIndicatorMaterialSelected, setPageIndicatorMaterialSelected, std::shared_ptr<MaterialResource>, _page_indicator_material_selected);

        /// Defines standard accessors for the page bar height
  		DEFINE_ACCESSORS		(getPageBarHeight, setPageBarHeight, DTfloat, _page_bar_height);

        /// Defines standard accessors for the page button spacing
  		DEFINE_ACCESSORS		(getPageButtonSpacing, setPageButtonSpacing, DTfloat, _page_button_spacing);

        /// Defines standard accessors for the page button size
  		DEFINE_ACCESSORS		(getPageButtonSize, setPageButtonSize, DTfloat, _page_button_size);

        
    private:
        static const DTfloat PADDING;

		Plug<std::shared_ptr<MaterialResource> >               _font_material;
		Plug<std::shared_ptr<MaterialResource> >               _page_indicator_material;
		Plug<std::shared_ptr<MaterialResource> >               _page_indicator_material_selected;
        
        Rectangle                                       _bounds;
        String                                          _label;
        DTboolean                                       _needs_render;
        DTboolean                                       _can_render;
        DTfloat                                         _page_bar_height;
        DTfloat                                         _page_button_spacing;
        DTfloat                                         _page_button_size;
        
        DTint                                           _current_page;
        DTfloat                                         _current_page_pos;
        DTfloat                                         _scroll_accum;
                
        struct Page {        
            std::shared_ptr<TextureResource>                   _text_image;
            Rectangle                                   _page_button;
        };
        
        std::list<Page>                                      _pages;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
