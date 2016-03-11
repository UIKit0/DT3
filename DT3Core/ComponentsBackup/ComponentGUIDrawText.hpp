#ifndef DT3_COMPONENTGUIDRAWTEXT
#define DT3_COMPONENTGUIDRAWTEXT
//==============================================================================
///	
///	File: ComponentGUIDrawText.hpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentBase.hpp"
#include "Rectangle.hpp"

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class MaterialResource;
class TextureResource;
class FontResource;
class CameraObject;

//==============================================================================
/// Component that can draw static text.
//==============================================================================

class ComponentGUIDrawText: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentGUIDrawText,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                    ComponentGUIDrawText	(void);	
									ComponentGUIDrawText	(const ComponentGUIDrawText &rhs);
        ComponentGUIDrawText &      operator =              (const ComponentGUIDrawText &rhs);	
        virtual                     ~ComponentGUIDrawText   (void);
    
        virtual void                archive_read			(Archive *archive);
        virtual void                archive_write		(Archive *archive);
		
	public:
		/// Called to initialize the object
		virtual void				initialize			(void);
        
		/// Returns the component type. This defines which slot the component is
        /// put into on the object.
		/// \return Component type
        virtual ComponentType       getComponentType    (void)  {   return COMPONENT_DRAW;  }

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

        /// Defines standard accessors for the font
  		DEFINE_ACCESSORS		(getFont, setFont, std::shared_ptr<FontResource>, _font);

        /// Defines standard accessors for the font size
  		DEFINE_ACCESSORS_RANGED	(getFontSize, setFontSize, DTfloat, _font_size, 0.1F, 1024.0F);

        /// Defines standard accessors for the font color
  		DEFINE_ACCESSORS		(getFontColor, setFontColor, Color, _font_color);
        
        /// Defines standard accessors for the font justification
  		DEFINE_ACCESSORS		(getJustification, setJustification, DTuint, _justification);
        
        /// Defines standard accessors for the x offset
  		DEFINE_ACCESSORS		(getOffsetX, setOffsetX, DTfloat, _offset_x);

        /// Defines standard accessors for the y offset
  		DEFINE_ACCESSORS		(getOffsetY, setOffsetY, DTfloat, _offset_y);

    private:
        void                        render              (void);
        
		Plug<std::shared_ptr<MaterialResource> >               _font_material;
		Plug<std::shared_ptr<FontResource> >                   _font;
        DTfloat                                         _font_size;
        Color                                           _font_color;
                
        DTuint                                          _justification;
        
        DTfloat                                         _offset_x;
        DTfloat                                         _offset_y;

        Rectangle                                       _bounds;
        String                                          _label;
        DTboolean                                       _needs_render;
        DTboolean                                       _can_render;
        
        std::shared_ptr<TextureResource>                       _text_image;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
