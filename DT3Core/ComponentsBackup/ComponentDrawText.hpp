#ifndef DT3_COMPONENTDRAWTEXT
#define DT3_COMPONENTDRAWTEXT
//==============================================================================
///	
///	File: ComponentDrawText.hpp
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
/// Component that can draw text using freetype. If you want styled text,
/// use ComponentDrawTextAdvanced instead.
//==============================================================================

class ComponentDrawText: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentDrawText,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                    ComponentDrawText	(void);	
									ComponentDrawText	(const ComponentDrawText &rhs);
        ComponentDrawText &         operator =          (const ComponentDrawText &rhs);	
        virtual                     ~ComponentDrawText  (void);
    
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
        void                        draw                (CameraObject* camera);
        
		/// Called when this component is added to the owner. Note that this will
        /// only be called if the owner is added to a world already. If not it 
        /// will be called when it is added to the World.
		/// \param owner Pointer to the owner
		virtual void                addToOwner          (ObjectBase *owner);

		/// Called when this component is removed from its owner.
		virtual void                removeFromOwner     (void);

		/// Screen created callback.
        void                        screenOpened       (DTuint width, DTuint height);
        
		/// Screen destroyed callback.
        void                        screenClosed     (void);
                
        /// Defines standard accessors for the font material
  		DEFINE_ACCESSORS		(getFontMaterial, setFontMaterial, std::shared_ptr<MaterialResource>, _font_material);

        /// Defines standard accessors for the font
  		DEFINE_ACCESSORS		(getFont, setFont, std::shared_ptr<FontResource>, _font);

        /// Defines standard accessors for the font size
  		DEFINE_ACCESSORS_RANGED	(getFontSize, setFontSize, DTfloat, _font_size, 0.1F, 1024.0F);

        /// Defines standard accessors for the font color
  		DEFINE_ACCESSORS		(getFontColor, setFontColor, Color, _font_color);

        /// Defines standard accessors for the label
  		DEFINE_ACCESSORS		(getLabel, setLabel, String, _label);

        /// Defines standard accessors for the texture image width
  		DEFINE_ACCESSORS_RANGED (getTextImageWidth, setTextImageWidth, DTuint, _text_image_width, 0, 2048);
        
        /// Defines standard accessors for the texture image height
  		DEFINE_ACCESSORS_RANGED (getTextImageHeight, setTextImageHeight, DTuint, _text_image_height, 0, 2048);
        
    private:
        void                        render              (void);
        
		Plug<std::shared_ptr<MaterialResource> >   _font_material;
		Plug<std::shared_ptr<FontResource> >       _font;
        DTfloat                             _font_size;
        Color                               _font_color;
                
        String                              _label;
        DTboolean                           _needs_render;
        DTboolean                           _can_render;
        
        DTuint                              _text_image_width;
        DTuint                              _text_image_height;
        std::shared_ptr<TextureResource>           _text_image;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
