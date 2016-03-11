#ifndef DT3_COMPONENTGUIVIDEOPLAYER
#define DT3_COMPONENTGUIVIDEOPLAYER
//==============================================================================
///	
///	File: ComponentGUIVideoPlayer.hpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3Core/Components/ComponentBase.hpp"
#include "DT3Core/Types/Math/Rectangle.hpp"
#include "DT3Core/Resources/ResourceTypes/FontResource.hpp"
#include "DT3Core/Resources/ResourceTypes/MaterialResource.hpp"
#include "DT3Core/Types/GUI/GUITouchEvent.hpp"
#include "DT3Core/Types/Node/Plug.hpp"
#include "DT3Core/Types/Node/Event.hpp"

#include "DT3HWVideoPlayer/FFmpeg/HWVideoPlayerFF.hpp"

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class TextureResource2D;
class CameraObject;

//==============================================================================
//==============================================================================

typedef HWVideoPlayerFF Video;

//==============================================================================
/// GUI drawing for a button.
//==============================================================================

class ComponentGUIVideoPlayer: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentGUIVideoPlayer,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                    ComponentGUIVideoPlayer (void);
									ComponentGUIVideoPlayer (const ComponentGUIVideoPlayer &rhs);
        ComponentGUIVideoPlayer &   operator =              (const ComponentGUIVideoPlayer &rhs);
        virtual                     ~ComponentGUIVideoPlayer(void);
    
        virtual void                archive                 (const std::shared_ptr<Archive> &archive);
        virtual void                archive_done            (const std::shared_ptr<Archive> &archive);
		
	public:
		/// Called to initialize the object
		virtual void				initialize              (void);
        
		/// Returns the component type. This defines which slot the component is
        /// put into on the object.
		/// \return Component type
        virtual ComponentType       component_type          (void)  {   return COMPONENT_DRAW;  }

		/// Draw Callback for component
		/// \param camera Camera used for drawing
		/// \param parent_color Color of the parent GUI Object
        void                        draw                    (const std::shared_ptr<CameraObject> &camera, const Color4f &parent_color);
    
        /// Registered with world to tick this node
		/// \param dt delta time
		virtual void                tick                    (const DTfloat dt);


		/// Open a video file
		/// \param path path to video file
        void                        open                    (const FilePath &path);

		/// Open a video URL
		/// \param purl url of video file
        void                        open                    (const URL &url);

		/// Close the currently opened video
        void                        close                   (void);


		/// Play the currently opened video
		/// \param sender pointer to node that fired the event
        void                        play                    (PlugNode *sender);

		/// Pause the currently opened video
		/// \param sender pointer to node that fired the event
        void                        pause                   (PlugNode *sender);

		/// Rewinds the video to the beginning
		/// \param sender pointer to node that fired the event
        void                        rewind                  (PlugNode *sender);

    
    
		/// Called when this component is added to the owner. Note that this will
        /// only be called if the owner is added to a world already. If not it 
        /// will be called when it is added to the World.
		/// \param owner Pointer to the owner
		virtual void                add_to_owner            (ObjectBase *owner);

		/// Called when this component is removed from its owner.
		virtual void                remove_from_owner       (void);


		/// Callback called when the component is getting a touch begin event
		/// \param event Touch events
        void                        touches_began           (GUITouchEvent *event);

		/// Callback called when the component is getting a touch move event
		/// \param event Touch events
        void                        touches_moved           (GUITouchEvent *event);

		/// Callback called when the component is getting a touch end event
		/// \param event Touch events
        void                        touches_ended           (GUITouchEvent *event);

		/// Callback called when the component is getting a touch cancelled event
		/// \param event Touch events
        void                        touches_cancelled       (GUITouchEvent *event);

    
        /// Defines standard accessors for the play material
  		DEFINE_ACCESSORS		(video_material, video_material, std::shared_ptr<MaterialResource>, _video_material);

        /// Defines standard accessors for the play material
  		DEFINE_ACCESSORS		(play_material, play_material, std::shared_ptr<MaterialResource>, _play_material);

        /// Defines standard accessors for the pause material
  		DEFINE_ACCESSORS		(pause_material, pause_material, std::shared_ptr<MaterialResource>, _pause_material);

        /// Defines standard accessors for the thumb material
  		DEFINE_ACCESSORS		(thumb_material, thumb_material, std::shared_ptr<MaterialResource>, _thumb_material);

        /// Defines standard accessors for the track loaded material
  		DEFINE_ACCESSORS		(track_loaded_material, track_loaded_material, std::shared_ptr<MaterialResource>, _track_loaded);

        /// Defines standard accessors for the track unloaded material
  		DEFINE_ACCESSORS		(track_unloaded_material, track_unloaded_material, std::shared_ptr<MaterialResource>, _track_unloaded);

        /// Defines standard accessors for the track unloaded material
  		DEFINE_ACCESSORS		(background_material, background_material, std::shared_ptr<MaterialResource>, _background);

    
    private:
    
        Rectangle   calc_play_pause_rect    (const Rectangle &rect);
        Rectangle   calc_seek_rect          (const Rectangle &rect);
        Rectangle   calc_track_rect         (const Rectangle &rect);
        Rectangle   calc_thumb_rect         (const Rectangle &rect, DTfloat current, DTfloat length);
        Rectangle   calc_background_rect    (const Rectangle &rect);
    
        Plug<std::string>                   _file_or_url;
        std::string                         _last_file_or_url;
    
        Plug<DTboolean>                     _is_playing;
        Plug<DTfloat>                       _current_time;
        Plug<DTfloat>                       _length;

		Plug<std::shared_ptr<MaterialResource> >   _video_material;
		Plug<std::shared_ptr<MaterialResource> >   _play_material;
		Plug<std::shared_ptr<MaterialResource> >   _pause_material;
		Plug<std::shared_ptr<MaterialResource> >   _thumb_material;
		Plug<std::shared_ptr<MaterialResource> >   _track_loaded;
		Plug<std::shared_ptr<MaterialResource> >   _track_unloaded;
		Plug<std::shared_ptr<MaterialResource> >   _background;
    
        DTfloat                             _controls_size;
        DTfloat                             _track_size;
        DTfloat                             _thumb_size;

		Event                               _play;
		Event                               _pause;
		Event                               _rewind;

        Video::HWVideoPlayerType            _hw;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
