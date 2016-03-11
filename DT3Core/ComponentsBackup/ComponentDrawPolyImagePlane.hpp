#ifndef DT3_COMPONENTDRAWPOLYIMAGEPLANE
#define DT3_COMPONENTDRAWPOLYIMAGEPLANE
//==============================================================================
///	
///	File: ComponentDrawPolyImagePlane.hpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentBase.hpp"
#include "MaterialResource.hpp"
#include "Texcoord.hpp"

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class GeometryGroupResource;
class CameraObject;
class ComponentDrawPolyImagePlane;

//==============================================================================
//==============================================================================

struct ComponentDrawPolyImagePlanePoint {
	ComponentDrawPolyImagePlanePoint(void)
		:	position	(0.0F,0.0F),
			texcoord	(0.0F,0.0F)
	{}

	ComponentDrawPolyImagePlanePoint(const ComponentDrawPolyImagePlanePoint &rhs)
		:	position	(rhs.position),
			texcoord	(rhs.texcoord)
	{}
	
	ComponentDrawPolyImagePlanePoint(const Vector2 &p, const Texcoord2 &t)	
		:	position	(p),
			texcoord	(t)
	{}
	
	Vector2				position;
	Texcoord2			texcoord;
};

//==============================================================================
//==============================================================================

class ComponentDrawPolyImagePlaneHull: public BaseRefCounted {
    public:
        DEFINE_TYPE(ComponentDrawPolyImagePlaneHull, BaseRefCounted)
		DEFINE_CREATE_AND_CLONE
		DEFINE_POOL_ALLOCATOR
		
                                            ComponentDrawPolyImagePlaneHull     (void);	
                                            ComponentDrawPolyImagePlaneHull     (const ComponentDrawPolyImagePlaneHull &rhs);
        ComponentDrawPolyImagePlaneHull &   operator =                          (const ComponentDrawPolyImagePlaneHull &rhs);	
                                            ~ComponentDrawPolyImagePlaneHull    (void);
    
    
		/// Returns the point indices for the hull
		/// \return Point indices for the hull
		const std::vector<DTint>                  getPolyPoints                       (void) const  {   return _points;  }

    private:
        friend class EdManipComponentDrawPolyImagePlane;
        friend class ComponentDrawPolyImagePlane;
    
		std::vector<DTint>                    _points;
		ComponentDrawPolyImagePlane		*_polygon_object;
};

//==============================================================================
/// Component that can draw an image bounded by a polygon. If you are
/// wanting to draw a large image with lots of transparent spaces you
/// can use this to save fill rate.
//==============================================================================

class ComponentDrawPolyImagePlane: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentDrawPolyImagePlane,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                        ComponentDrawPolyImagePlane	(void);	
                                        ComponentDrawPolyImagePlane	(const ComponentDrawPolyImagePlane &rhs);
        ComponentDrawPolyImagePlane &	operator =                  (const ComponentDrawPolyImagePlane &rhs);	
        virtual                         ~ComponentDrawPolyImagePlane(void);
    
        virtual void                archive_read			(Archive *archive);
        virtual void                archive_read_done		(void);
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

        /// Defines standard accessors for the color of the image plane
  		DEFINE_ACCESSORS            (getColor, setColor, Color, _color);
        
        /// Defines standard accessors for the aspect ratio
  		DEFINE_ACCESSORS            (getAspect, setAspect, DTfloat, _aspect);
        
        /// Defines standard accessors for flip flags
  		DEFINE_ACCESSORS            (getFlipHorz, setFlipHorz, DTboolean, _flip_horz);
  		DEFINE_ACCESSORS            (getFlipVert, setFlipVert, DTboolean, _flip_vert);

        /// Defines standard accessors for user parameters
  		DEFINE_ACCESSORS            (getP1, setP1, DTfloat, _p0);
  		DEFINE_ACCESSORS            (getP2, setP2, DTfloat, _p1);
  		DEFINE_ACCESSORS            (getP3, setP3, DTfloat, _p2);
  		DEFINE_ACCESSORS            (getP4, setP4, DTfloat, _p3);

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


		/// Calculates the convex hulls for the polygon
		void						calcHulls           (void);

		/// Calculates the texture coordinates for the polygon
		void						calcDefaultTexcoords(void);

		/// Returns all of the polygon points for the polygon
		/// \return Polygon points
		std::vector<ComponentDrawPolyImagePlanePoint>             getPolyPoints   (void)          {   return _poly_points;    }
    
		/// Returns all of the hulls for the polygon
		/// \return Polygon hulls
		const std::vector<ComponentDrawPolyImagePlaneHull*>       getPolyHulls    (void) const    {   return _hulls;          }

	private:
		friend class EdManipComponentDrawPolyImagePlane;
	
		std::vector<ComponentDrawPolyImagePlanePoint>     _poly_points;
		std::vector<ComponentDrawPolyImagePlaneHull*>     _hulls;
        
		// Construction Routines
		DTboolean					isConvex            (ComponentDrawPolyImagePlaneHull &hull);
		DTboolean					intersect           (Vector2 &p0, Vector2 &p1, Vector2 &p2, Vector2 &p3);
		DTboolean					isEmpty				(ComponentDrawPolyImagePlaneHull &hull);
		void						calcHullsRecursive	(ComponentDrawPolyImagePlaneHull &hull);	

		Plug<std::shared_ptr<MaterialResource> >           _material;
		Plug<Color>                                 _color;
        DTfloat                                     _aspect;
        
        Plug<DTboolean>                             _flip_horz;
        Plug<DTboolean>                             _flip_vert;
        
		Plug<DTfloat>                               _p0;
		Plug<DTfloat>                               _p1;
		Plug<DTfloat>                               _p2;
		Plug<DTfloat>                               _p3;
        
        DTint                                       _params_pos;

};

//==============================================================================
//==============================================================================

} // DT3

#endif
