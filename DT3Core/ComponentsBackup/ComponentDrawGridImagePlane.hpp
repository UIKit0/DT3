#ifndef DT3_COMPONENTDRAWGRIDIMAGEPLANE
#define DT3_COMPONENTDRAWGRIDIMAGEPLANE
//==============================================================================
///	
///	File: ComponentDrawGridImagePlane.hpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentBase.hpp"
#include "GridImageData.hpp"

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class GeometryGroupResource;
class MaterialResource;
class CameraObject;

//==============================================================================
/// Component that can draw a grid warped image. A grid warp is a simple
/// way to animate a distortion in an image.
//==============================================================================

class ComponentDrawGridImagePlane: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentDrawGridImagePlane,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                        ComponentDrawGridImagePlane	(void);	
                                        ComponentDrawGridImagePlane	(const ComponentDrawGridImagePlane &rhs);
        ComponentDrawGridImagePlane &	operator =                  (const ComponentDrawGridImagePlane &rhs);	
        virtual                         ~ComponentDrawGridImagePlane(void);
    
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
        
		/// Returns the grid data.
		/// \return Grid data
        GridImageData&              getGrid             (void) {    return *_grid;  }
        
		/// Sets the number of grid points in the X direction
		/// \param num_x Number of grid points
   		void                        setNumX				(const DTuint num_x);

		/// Returns the number of grid points in the X direction
		/// \return Number of grid points in X
   		const DTuint				getNumX				(void) const;

		/// Sets the number of grid points in the Y direction
		/// \param num_y Number of grid points
   		void                        setNumY				(const DTuint num_y);

		/// Returns the number of grid points in the Y direction
		/// \return Number of grid points in Y
   		const DTuint				getNumY				(void) const;

        
		/// Called when this component is added to the owner. Note that this will
        /// only be called if the owner is added to a world already. If not it 
        /// will be called when it is added to the World.
		/// \param owner Pointer to the owner
		virtual void                addToOwner          (ObjectBase *owner);

		/// Called when this component is removed from its owner.
		virtual void                removeFromOwner     (void);

		/// Get and retrieve the color for this image
  		DEFINE_ACCESSORS		(getColor, setColor, Color, _color);
    
		/// Get and retrieve the aspect ratio for this image
  		DEFINE_ACCESSORS		(getAspect, setAspect, DTfloat, _aspect);
    
		/// Get and retrieve the material for this image
  		DEFINE_ACCESSORS		(getMaterial, setMaterial, std::shared_ptr<MaterialResource>, _material);

    private:
		Plug<std::shared_ptr<MaterialResource> >   _material;
		Plug<Color>                         _color;
        DTfloat                             _aspect;
        
        Plug<GridImageData>                 _grid;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
