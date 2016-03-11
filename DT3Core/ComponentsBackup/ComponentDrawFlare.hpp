#ifndef DT3_COMPONENTDRAWFLARE
#define DT3_COMPONENTDRAWFLARE
//==============================================================================
///	
///	File: ComponentDrawFlare.hpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentBase.hpp"

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class GeometryGroupResource;
class MaterialResource;
class CameraObject;

//==============================================================================
/// Component that can draw a lens flare.
//==============================================================================

class ComponentDrawFlare: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentDrawFlare,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                    ComponentDrawFlare	(void);	
									ComponentDrawFlare	(const ComponentDrawFlare &rhs);
        ComponentDrawFlare &        operator =			(const ComponentDrawFlare &rhs);	
        virtual                     ~ComponentDrawFlare	(void);
    
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
        
        
		DEFINE_ACCESSORS(getMaterial0, setMaterial0, std::shared_ptr<MaterialResource>, _mat[0]);
		DEFINE_ACCESSORS(getMaterial1, setMaterial1, std::shared_ptr<MaterialResource>, _mat[1]);
		DEFINE_ACCESSORS(getMaterial2, setMaterial2, std::shared_ptr<MaterialResource>, _mat[2]);
		DEFINE_ACCESSORS(getMaterial3, setMaterial3, std::shared_ptr<MaterialResource>, _mat[3]);
		DEFINE_ACCESSORS(getMaterial4, setMaterial4, std::shared_ptr<MaterialResource>, _mat[4]);
		DEFINE_ACCESSORS(getMaterial5, setMaterial5, std::shared_ptr<MaterialResource>, _mat[5]);


		/// Sets the alpha for the lens flare. This can be used to manually fade it out.
		/// \param alpha alpha to set
        void                                setAlpha    (DTfloat alpha) {   _alpha = alpha; }
        
	private:

        Plug<DTfloat>						_alpha;

		static const DTint NUM_FLARES = 6;
	
		std::shared_ptr<MaterialResource>          _mat[NUM_FLARES];
		DTfloat								_size[NUM_FLARES];
		DTfloat								_pos[NUM_FLARES];
};

//==============================================================================
//==============================================================================

} // DT3

#endif
