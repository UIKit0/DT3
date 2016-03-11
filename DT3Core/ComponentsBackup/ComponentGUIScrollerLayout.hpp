#ifndef DT3_COMPONENTGUISCROLLERLAYOUT
#define DT3_COMPONENTGUISCROLLERLAYOUT
//==============================================================================
///	
///	File: ComponentGUIScrollerLayout.hpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentGUIScroller.hpp"
#include "PlaceableObject.hpp"
#include "GUILayout.hpp"

namespace DT3 {

//==============================================================================
/// GUI behaviour for a scroll zone. It scrolls its children objects.
/// This component arranges its children into a grid
//==============================================================================

class ComponentGUIScrollerLayout: public ComponentGUIScroller {
    public:
        DEFINE_TYPE(ComponentGUIScrollerLayout,ComponentGUIScroller)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                    ComponentGUIScrollerLayout	(void);	
									ComponentGUIScrollerLayout	(const ComponentGUIScrollerLayout &rhs);
        ComponentGUIScrollerLayout& operator =                  (const ComponentGUIScrollerLayout &rhs);	
        virtual                     ~ComponentGUIScrollerLayout	(void);
    
        virtual void                archive_read			(Archive *archive);
        virtual void                archive_write		(Archive *archive);
		
	public:
		/// Called to initialize the object
		virtual void				initialize			(void);
        
		/// Called when this component is added to the owner. Note that this will
        /// only be called if the owner is added to a world already. If not it 
        /// will be called when it is added to the World.
		/// \param owner Pointer to the owner
		virtual void                addToOwner          (ObjectBase *owner);

		/// Called when this component is removed from its owner.
		virtual void                removeFromOwner     (void);
        
        /// Set layout
		/// \param layout layout object
        void                        setLayout           (std::shared_ptr<GUILayout> layout);

        /// Returns the layout object
        std::shared_ptr<GUILayout>         getLayout           (void) const;
    
        /// Sets the width of the sizer (if horizontal scrolling enabled)
        /// \param width Content width
        void                        setContentWidth     (DTfloat width);
    
        /// Returns the width of the content
        DTfloat                     getContentWidth     (void) const;

        /// Sets the height of the sizer (if vertical scrolling enabled)
        /// \param width Content height
        void                        setContentHeight    (DTfloat height);

        /// Returns the height of the content
        DTfloat                     getContentHeight    (void) const;

        /// Causes layout of the items
        void                        arrangeItems        (DTfloat time = 0.0F);

    private:        
        std::shared_ptr<GUILayout>         _layout;
    
        DTfloat                     _content_width;
        DTfloat                     _content_height;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
