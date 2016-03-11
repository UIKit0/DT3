#ifndef DT3_COMPONENTDRAWSTRETCHIMAGEPLANE
#define DT3_COMPONENTDRAWSTRETCHIMAGEPLANE
//==============================================================================
///	
///	File: ComponentDrawStretchImagePlane.hpp
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
/// Component that can draw a rectangular image. This difference with this
/// component is that the image is split into a 3x3 grid and the corners
/// are drawn at a constant size while the edges and middle are stretched.
//==============================================================================

class ComponentDrawStretchImagePlane: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentDrawStretchImagePlane,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                            ComponentDrawStretchImagePlane	(void);	
                                            ComponentDrawStretchImagePlane	(const ComponentDrawStretchImagePlane &rhs);
        ComponentDrawStretchImagePlane &	operator =                      (const ComponentDrawStretchImagePlane &rhs);	
        virtual                             ~ComponentDrawStretchImagePlane (void);
    
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

        /// Accessors to get and set the color of the image plane
  		DEFINE_ACCESSORS            (getColor, setColor, Color, _color);
    
        /// Accessors to get and set the aspect of the image plane
  		DEFINE_ACCESSORS            (getAspect, setAspect, DTfloat, _aspect);
    
        /// Accessors to get and set the horizontal corner size
  		DEFINE_ACCESSORS_RANGED		(getCornerWidth, setCornerWidth, DTfloat, _corner_width, 0.0F, 1.0F);

        /// Accessors to get and set the vertical corner size
  		DEFINE_ACCESSORS_RANGED		(getCornerHeight, setCornerHeight, DTfloat, _corner_height, 0.0F, 1.0F);

		/// Returns the material for the Image Plane
		/// \return The material for the image plane
        std::shared_ptr<MaterialResource>  getMaterial         (void) const;
        
		/// Sets the material for the Image Plane
        /// \param material Pointer to new material
        void                        setMaterial         (std::shared_ptr<MaterialResource> material);
    
		/// Sets the material for the image. This is only called from the editor when
        /// a material is changed in the property list.
		/// \param material Material for the image
        void                        setMaterialProp     (std::shared_ptr<MaterialResource> material);


    private:
		Plug<std::shared_ptr<MaterialResource> >   _material;
		Plug<Color>                         _color;
        DTfloat                             _aspect;
                
        DTfloat                             _corner_width;
        DTfloat                             _corner_height;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
