#ifndef DT3_COMPONENTDRAWSHAPE
#define DT3_COMPONENTDRAWSHAPE
//==============================================================================
///	
///	File: ComponentDrawShape.hpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentBase.hpp"
#include "MaterialResource.hpp"
#include <vector>

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class TextureResource;
class FontResource;
class CameraObject;

//==============================================================================
/// Component that can draw an arbitrary spline-based shape. Note that
/// this is a fairly expensive object and needs a stencil buffer to
/// draw properly. It is used mostly when objects get pre rendered
/// to a texture.
//==============================================================================

class ComponentDrawShape: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentDrawShape,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                    ComponentDrawShape	(void);	
									ComponentDrawShape	(const ComponentDrawShape &rhs);
        ComponentDrawShape &        operator =          (const ComponentDrawShape &rhs);	
        virtual                     ~ComponentDrawShape (void);
    
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
                
        /// Defines standard accessors for the fill material
  		DEFINE_ACCESSORS		(getMaterial, setMaterial, std::shared_ptr<MaterialResource>, _material);
    
        /// Defines standard accessors for the edge material
  		DEFINE_ACCESSORS		(getEdgeMaterial, setEdgeMaterial, std::shared_ptr<MaterialResource>, _edge_material);

        /// Defines standard accessors for the color
        DEFINE_ACCESSORS        (getColor, setColor, Color, _color)
    
    
		/// Sets the number of vertices in the shape
		/// \param num number of vertices
        void                        setNumVertices          (DTsize num)                        {   _needs_recalculate = true;   return _vertices.resize(num);   }

		/// Returns the number of vertices in the shape
		/// \return number of vertices
        DTsize                      getNumVertices          (void) const                        {	return _vertices.size();		}

		/// Sets the position of one vertex
		/// \param k index of vertex
		/// \param point position of vertex
		void						setVertexPoint			(DTuint k, const Vector2 &point)	{	_needs_recalculate = true;   _vertices[k].point = point;     }

		/// Returns the position of one vertex
		/// \param k index of vertex
		/// \return position of vertex
		const Vector2 &				getVertexPoint			(DTuint k)	const					{	return _vertices[k].point;      }

		/// Sets the tengent of one vertex
		/// \param k index of vertex
		/// \param tangent tangent of vertex
		void						setVertexPointTangent	(DTuint k, const Vector2 &tangent)	{	_needs_recalculate = true;   _vertices[k].tangent = tangent; }

		/// Returns the tangent of one vertex
		/// \param k index of vertex
		/// \return tangent of vertex
		const Vector2 &				getVertexPointTangent	(DTuint k)	const					{	return _vertices[k].tangent;    }
    
		/// Sets the flag that detemines wether points are connected by a bezier
		/// \param use_bezier true or false
        void                        setUseBezier            (DTboolean use_bezier)              {   _needs_recalculate = true;   _use_bezier = use_bezier;       }

		/// Returns the flag that detemines wether points are connected by a bezier
		/// \return using bezier or not
        DTboolean                   getUseBezier            (void) const                        {   return _use_bezier;         }
        
		/// Sets the scale of the noise that is applied to the tesselated edges
		/// \param noise_scale scale of the noise
        void                        setNoiseScale           (DTfloat noise_scale)               {   _needs_recalculate = true;   _noise_scale = noise_scale;       }

		/// Returns the scale of the noise that is applied to the tesselated edges
		/// \return scale of the noise
        DTfloat                     getNoiseScale           (void) const                        {   return _noise_scale;         }
        
		/// Sets the frequency of the noise that is applied to the tesselated edges
		/// \param noise_freq frequency of the noise
        void                        setNoiseFreq            (DTfloat noise_freq)                {   _needs_recalculate = true;   _noise_freq = noise_freq;       }

		/// Returns the frequency of the noise that is applied to the tesselated edges
		/// \return frequency of the noise
        DTfloat                     getNoiseFreq            (void) const                        {   return _noise_freq;         }
        
    
		/// Calculates a polynomial that fits the contour of the shape. This can be used
        /// to fill the contents of the shape with a texture that follows it's contour.
        /// The polynomial math looks like this:
        ///     y = a + b * x + c * x^2 + d * x^3;

		/// \param a polynomial coefficient
		/// \param b polynomial coefficient
		/// \param c polynomial coefficient
		/// \param d polynomial coefficient
        void                        getPolynomialCoeffs     (DTfloat &a, DTfloat &b, DTfloat &c, DTfloat &d);
    
		/// Accessors to set and retrieve the thickness of the edge.
        DEFINE_ACCESSORS(getEdgeThickness, setEdgeThickness, DTfloat, _edge_thickness)
    
    protected:
        friend class EdManipComponentDrawShape;
        
		Plug<std::shared_ptr<MaterialResource> >   _material;
		Plug<std::shared_ptr<MaterialResource> >   _edge_material;

		Plug<Color>                         _color;
    
        MaterialResource                    _mask_material;
    
        DTboolean                           _use_bezier;
        DTint                               _subdivisions;
    
        DTfloat                             _edge_thickness;
        DTfloat                             _texcoord_scale;
        DTfloat                             _edge_texcoord_scale;
        DTboolean                           _follow_contour;
    
        DTfloat                             _noise_scale;
        DTfloat                             _noise_freq;
    
        struct Vertex {
            Vertex (void)
                :   point   (0.0F,0.0F),
                    tangent (0.0F,0.0F)
            {}
        
            Vector2     point;
            Vector2     tangent;
        };
    
        std::vector<Vertex>   _vertices;
    

        struct Curve {        
            Vector2     point;
            Vector2     perp;
            DTfloat     dist;
        };
    
        std::vector<Curve>    _curve;
    
        DTfloat                             _min_x;
        DTfloat                             _max_x;
        DTfloat                             _min_y;
        DTfloat                             _max_y;
        DTfloat                             _perimeter;
    
        DTboolean                           _needs_recalculate;
    
        void                                calculateCurve          (void);
    
        DTfloat                             _a,_b,_c,_d;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
