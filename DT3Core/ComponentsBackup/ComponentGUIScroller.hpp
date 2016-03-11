#ifndef DT3_COMPONENTGUISCROLLER
#define DT3_COMPONENTGUISCROLLER
//==============================================================================
///	
///	File: ComponentGUIScroller.hpp
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

class GUITouchEvent;
class GUIObject;
class TouchEvent;
class CameraObject;
class WorldNode;
class MaterialResource;

//==============================================================================
/// GUI behaviour for a scroll zone. It scrolls its children objects.
//==============================================================================

class ComponentGUIScroller: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentGUIScroller,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                    ComponentGUIScroller	(void);	
									ComponentGUIScroller	(const ComponentGUIScroller &rhs);
        ComponentGUIScroller &      operator =              (const ComponentGUIScroller &rhs);	
        virtual                     ~ComponentGUIScroller	(void);
    
        virtual void                archive_read			(Archive *archive);
        virtual void                archive_write		(Archive *archive);
		
	public:
		/// Called to initialize the object
		virtual void				initialize			(void);
        
		/// Returns the component type. This defines which slot the component is
        /// put into on the object.
		/// \return Component type
        virtual ComponentType       getComponentType    (void)  {   return COMPONENT_TOUCH;  }

		/// Called when this component is added to the owner. Note that this will
        /// only be called if the owner is added to a world already. If not it 
        /// will be called when it is added to the World.
		/// \param owner Pointer to the owner
		virtual void                addToOwner          (ObjectBase *owner);

		/// Called when this component is removed from its owner.
		virtual void                removeFromOwner     (void);


		/// Callback called when overriding hit testing
        void                        hitTest             (GUITouchEvent *event, GUIObject* &hit_object, const Color &parent_color);

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
        void                        draw                (CameraObject* camera, const Color &parent_color);

		/// Forces the scroller to scroll to the top
        void                        scrollToTop         (void)  {   _scroll_to_top = true;  }

		/// Forces the scroller to scroll to the bottom
        void                        scrollToBottom      (void)  {   _scroll_to_bottom = true;  }
        
		/// Forces the scroller to scroll to the left
        void                        scrollToLeft        (void)  {   _scroll_to_left = true;  }

		/// Forces the scroller to scroll to the right
        void                        scrollToRight       (void)  {   _scroll_to_right = true;  }
        

		/// Called while an item is being dragged
        void                        calculateContectRect(void);

		/// Called while an item is being dragged
        const Rectangle &           getContectRect      (void) const    {   return _contents;   }

        /// Defines standard accessors for the material
  		DEFINE_ACCESSORS		(getMaterial, setMaterial, std::shared_ptr<MaterialResource>, _material);

        /// Defines standard accessors for the delete button material
  		DEFINE_ACCESSORS		(getDeleteMaterial, setDeleteMaterial, std::shared_ptr<MaterialResource>, _delete_material);

        /// Defines standard accessors for the scroll horizontal flag
  		DEFINE_ACCESSORS		(getScrollHorz, setScrollHorz, DTboolean, _scroll_horz);

        /// Defines standard accessors for the scroll vertical flag
  		DEFINE_ACCESSORS		(getScrollVert, setScrollVert, DTboolean, _scroll_vert);

        /// Defines standard accessors for the scroll horizontal pad
  		DEFINE_ACCESSORS		(getPadHorz, setPadHorz, DTfloat, _pad_horz);

        /// Defines standard accessors for the scroll vertical pad
  		DEFINE_ACCESSORS		(getPadVert, setPadVert, DTfloat, _pad_vert);

        /// Defines standard accessors for auto centering
  		DEFINE_ACCESSORS		(getAutoCenterHorz, setAutoCenterHorz, DTboolean, _auto_center_horz);
        
        /// Defines standard accessors for auto centering
  		DEFINE_ACCESSORS		(getAutoCenterVert, setAutoCenterVert, DTboolean, _auto_center_vert);

        /// Defines standard accessors for rearragning items
  		DEFINE_ACCESSORS		(getCanRearrageItems, setCanRearrageItems, DTboolean, _can_rearrage_items);
        
        /// Defines standard accessors for rearragning items
  		DEFINE_ACCESSORS		(getCanRemoveItems, setCanRemoveItems, DTboolean, _can_remove_items);
        
    protected:
		/// Called while an item is being dragged
        virtual void                draggingItem        (GUIObject *item)   {}

		/// Called while an item is being dragged
        virtual void                finishedDraggingItem(GUIObject *item)   {}

		/// Called while an item is being deleted
        virtual void                deleteItem          (GUIObject *item);

		/// Start the wiggle animations
        void                        startWiggle         (void);

		/// Stop the wiggle animations
        void                        stopWiggle          (void);

		/// Start the wiggle animations on one item
        void                        startWiggleItem     (GUIObject *item);

		/// Stop the wiggle animations on one item
        void                        stopWiggleItem      (GUIObject *item);

     private:
        static const DTfloat VELOCITY_DECAY;
        static const DTfloat BORDER_BOUNCE;
        static const DTfloat REARRANGE_TIME_THRESH;
        static const DTfloat REARRANGE_TIME_THRESH2;
        static const DTfloat DELETE_SIZE;

		Plug<std::shared_ptr<MaterialResource> >   _material;
		Plug<std::shared_ptr<MaterialResource> >   _delete_material;
        
        Rectangle                   calcDeleteButtonRectangle   (const GUIObject *object);
        
        enum Mode {
            MODE_NORMAL,
            MODE_REARRANGING,
            MODE_REARRANGING_SCROLLING,
            MODE_REARRANGING_DRAGGING
        } _mode;
        
        DTfloat                     _rearranging_timer;


        Plug<DTfloat>               _horz_scroll_percentage_fill;
        Plug<DTfloat>               _horz_scroll_position;
        Plug<DTfloat>               _vert_scroll_percentage_fill;
        Plug<DTfloat>               _vert_scroll_position;
        
        Rectangle                   _contents;

        DTboolean                   _scroll_horz;
        DTboolean                   _scroll_vert;

        DTboolean                   _auto_center_horz;
        DTboolean                   _auto_center_vert;
        
        DTboolean                   _scroll_to_top;
        DTboolean                   _scroll_to_bottom;
        DTboolean                   _scroll_to_left;
        DTboolean                   _scroll_to_right;
        
        DTfloat                     _vel_x;
        DTfloat                     _vel_y;

        DTfloat                     _pad_horz;
        DTfloat                     _pad_vert;
        
        DTfloat                     _velocity_decay;
        
        GUIObject                   *_focused;
        DTfloat                     _press_timer;
        
        DTboolean                   _can_rearrage_items;
        DTboolean                   _can_remove_items;
        
};

//==============================================================================
//==============================================================================

} // DT3

#endif
