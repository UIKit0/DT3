#ifndef DT3_COMPONENTDRAWFILLIMAGEPLANE
#define DT3_COMPONENTDRAWFILLIMAGEPLANE
//==============================================================================
///	
///	File: ComponentDrawFillImagePlane.hpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentBase.hpp"
#include "MaterialResource.hpp"

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class GeometryGroupResource;
class CameraObject;

//==============================================================================
/// Component that can draw an image that can be filled (like a progress bar).
//==============================================================================

class ComponentDrawFillImagePlane: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentDrawFillImagePlane,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                        ComponentDrawFillImagePlane	(void);	
                                        ComponentDrawFillImagePlane	(const ComponentDrawFillImagePlane &rhs);
        ComponentDrawFillImagePlane &	operator =                  (const ComponentDrawFillImagePlane &rhs);	
        virtual                         ~ComponentDrawFillImagePlane(void);
    
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

  		DEFINE_ACCESSORS		(getColor, setColor, Color, _color);
  		DEFINE_ACCESSORS		(getAspect, setAspect, DTfloat, _aspect);
        
		/// Returns the material for the image
		/// \return material for the image
        std::shared_ptr<MaterialResource>  getMaterial         (void) const;
    
		/// Sets the material for the image
		/// \param material Material for the image
        void                        setMaterial         (std::shared_ptr<MaterialResource> material);
    
		/// Sets the material for the image. This is only called from the editor when
        /// a material is changed in the property list.
		/// \param material Material for the image
        void                        setMaterialProp     (std::shared_ptr<MaterialResource> material);


    private:
		Plug<std::shared_ptr<MaterialResource> >       _material;
		Plug<Color>                             _color;
        DTfloat                                 _aspect;
        
		Plug<DTfloat>                           _fill;
		Plug<DTfloat>                           _angle;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
