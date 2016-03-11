#ifndef DT3_COMPONENTDRAWSTREAMINGIMAGESEQUENCEPLANE
#define DT3_COMPONENTDRAWSTREAMINGIMAGESEQUENCEPLANE
//==============================================================================
///	
///	File: ComponentDrawStreamingImageSequencePlane.hpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentBase.hpp"
#include "MaterialResource.hpp"
#include "TimerLores.hpp"
#include "ThreadTaskQueue.hpp"

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class CameraObject;

//==============================================================================
/// Component that can draw a rectangular image.
//==============================================================================

class ComponentDrawStreamingImageSequencePlane: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentDrawStreamingImageSequencePlane,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                                    ComponentDrawStreamingImageSequencePlane	(void);
                                                    ComponentDrawStreamingImageSequencePlane	(const ComponentDrawStreamingImageSequencePlane &rhs);
        ComponentDrawStreamingImageSequencePlane &	operator =                                  (const ComponentDrawStreamingImageSequencePlane &rhs);
        virtual                                     ~ComponentDrawStreamingImageSequencePlane   (void);
    
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
    
        DEFINE_ACCESSORS            (getMaterial, setMaterial, std::shared_ptr<MaterialResource>, _material);

    
		/// Returns the texture for the Image Plane
		/// \return The texture for the image plane
        const String&               getTexture          (void) const;
        
		/// Sets the texture for the Image Plane
        /// \param texture Pointer to new texture
        void                        setTexture          (const String &texture);

		/// Sets the texture for the Image Plane along with aspect ratio
        /// \param texture Pointer to new texture
        void                        setTextureProp      (const String &texture);

    private:
        void                        beginLoad           (void);                                             // Main Thread
        void                        load                (FilePath path, DTint loaded_index);                // Worker Thread
        void                        loadDone            (std::shared_ptr<TextureResource> tex, DTint loaded_index);// Main Thread
        void                        unload              (void);                                             // Main Thread
    
        String                      fillInPath          (DTint index, const String &path);
    
        enum State {
            STATE_UNLOADED,
            STATE_LOADING,
            STATE_LOADED,
            STATE_ERROR
        };

        State                                   _state;
    
        enum LoadBehaviour {
            LOAD_NORMAL,
            LOAD_THREADED
        };
    
        DTint                                   _load_behaviour;    // 0 = normal load, 1 = threaded load

        enum UnloadBehaviour {
            UNLOAD_NEVER,
            UNLOAD_ALWAYS
        };

        DTint                                   _unload_behaviour;    // 0 = never unload, 1 = always unload
    
    
		Plug<String>                            _texture;
    
        Plug<DTint>                             _loaded_index;
		Plug<DTint>                             _index;

		Plug<std::shared_ptr<MaterialResource> >       _material;
    
		Plug<Color>                             _color;
        DTfloat                                 _aspect;
        
        Plug<DTboolean>                         _flip_horz;
        Plug<DTboolean>                         _flip_vert;
                
		Plug<DTfloat>                           _p0;
		Plug<DTfloat>                           _p1;
		Plug<DTfloat>                           _p2;
		Plug<DTfloat>                           _p3;

        DTint                                   _params_pos;
    
        std::shared_ptr<ThreadTaskQueueRef>            _pending_task;
    
        std::shared_ptr<TextureResource>               _pending_texture;
        std::shared_ptr<TextureResource>               _cache_texture;
    
        SpinLock                                _lock;

};

//==============================================================================
//==============================================================================

} // DT3

#endif
