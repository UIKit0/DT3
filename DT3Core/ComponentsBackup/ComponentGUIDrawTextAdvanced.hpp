#ifndef DT3_COMPONENTGUIDRAWTEXTADVANCED
#define DT3_COMPONENTGUIDRAWTEXTADVANCED
//==============================================================================
///	
///	File: ComponentGUIDrawTextAdvanced.hpp
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
/// GUI drawing for text that supports different fonts and styles using
/// a special markup language. The formatting options supported are:
/// \\t		Tab
/// \\n		Newline
/// [j<]	Left justify text
/// [j>]	Right justify text
/// [j><]	Center justify text
/// [j<>]	Full justify text
/// [vlr]	Vertical text, left to right
/// [vrl]	Vertical text, right to left
/// [hrl]	Horizontal text, right to left
/// [hlr]	Horizontal text, left to right	(Default)
/// [ww]	Word Wrap
/// [cw]	Character wrap
/// [font="{somefont.ttf}"]	Set the font
/// [size=##]	Set the font size
/// [kern=##]	Set the font kern
/// [color=R G B A]	Set the font color
/// [outlinecolor=R G B A]	Set the outline color
/// [outlinesize=##]	Set the outline size
/// [color=R G B A]	Set the font color
/// [tab=##]	Set the tab size
/// [baseline=##]	Set the baseline shift
/// [U=##]	Insert a unicode character
//==============================================================================

class ComponentGUIDrawTextAdvanced: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentGUIDrawTextAdvanced,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                        ComponentGUIDrawTextAdvanced	(void);	
                                        ComponentGUIDrawTextAdvanced	(const ComponentGUIDrawTextAdvanced &rhs);
        ComponentGUIDrawTextAdvanced &  operator =                      (const ComponentGUIDrawTextAdvanced &rhs);	
        virtual                         ~ComponentGUIDrawTextAdvanced   (void);
    
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

        /// Defines standard accessors for the vertical centering flag
  		DEFINE_ACCESSORS		(getCenterVertically, setCenterVertically, DTboolean, _center_vertically);
        
        /// Defines standard accessors for state colors
  		DEFINE_ACCESSORS		(getNormalColor, setNormalColor, Color, _normal_color);
  		DEFINE_ACCESSORS		(getPressedColor, setPressedColor, Color, _pressed_color);
    
    private:        
		Plug<std::shared_ptr<MaterialResource> >               _font_material;
        
        Rectangle                                       _bounds;
        String                                          _label;
        DTboolean                                       _needs_render;
        DTboolean                                       _can_render;
        DTboolean                                       _center_vertically;
        
        Color                                           _normal_color;
        Color                                           _pressed_color;
        
        std::shared_ptr<TextureResource>                       _text_image;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
