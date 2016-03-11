#ifndef DT3_COMPONENTGUISLIDER
#define DT3_COMPONENTGUISLIDER
//==============================================================================
///	
///	File:           ComponentGUISlider.hpp
///	Author:			Tod Baudais
///					Copyright (C) 2000-2007. All rights reserved.
///	
///	Date Created:	1/31/2001
///	Changes:		-none-
///	
//==============================================================================

#include "ComponentBase.hpp"

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class GUITouchEvent;
class GUIObject;
class CameraObject;
class MaterialResource;

//==============================================================================
/// GUI behaviour a slider. This component will also draw it.
//==============================================================================

class ComponentGUISlider: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentGUISlider,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                    ComponentGUISlider	(void);	
									ComponentGUISlider	(const ComponentGUISlider &rhs);
        ComponentGUISlider &        operator =          (const ComponentGUISlider &rhs);	
        virtual                     ~ComponentGUISlider	(void);
    
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
        
        
		/// Draw Callback for component
		/// \param camera Camera used for drawing
        void                        draw                (CameraObject* camera, const Color &parent_color);


        /// Defines standard accessors for the material
  		DEFINE_ACCESSORS		(getMaterial, setMaterial, std::shared_ptr<MaterialResource>, _material);

        /// Defines standard accessors for the delete button material
  		DEFINE_ACCESSORS		(getThumbMaterial, setThumbMaterial, std::shared_ptr<MaterialResource>, _thumb_material);

        /// Defines standard accessors for the cap width
  		DEFINE_ACCESSORS		(getCapWidth, setCapWidth, DTfloat, _slider_cap_width);

        /// Defines standard accessors for the slider height
  		DEFINE_ACCESSORS		(getSliderHeight, setSliderHeight, DTfloat, _slider_height);
    
        /// Defines standard accessors for the thumb width
  		DEFINE_ACCESSORS		(getThumbWidth, setThumbWidth, DTfloat, _thumb_width);
    
        /// Defines standard accessors for the thumb height
  		DEFINE_ACCESSORS		(getThumbHeight, setThumbHeight, DTfloat, _thumb_height);
    

     private:
        void                        touchToValue        (const Vector2 &t);
            
		Plug<std::shared_ptr<MaterialResource> >   _material;
		Plug<std::shared_ptr<MaterialResource> >   _thumb_material;
                
        Plug<DTint>                 _min_value;
        Plug<DTint>                 _max_value;
        Plug<DTint>                 _value;
    
        DTfloat                     _slider_cap_width;
        DTfloat                     _slider_height;

        DTfloat                     _thumb_width;
        DTfloat                     _thumb_height;

        Event                       _value_changed;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
