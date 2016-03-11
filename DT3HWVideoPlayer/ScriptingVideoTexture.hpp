#ifndef DT3_SCRIPTINGVIDEOTEXTURE
#define DT3_SCRIPTINGVIDEOTEXTURE
//==============================================================================
///	
///	File: ScriptingVideoTexture.hpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3Core/Scripting/ScriptingBase.hpp"
#include "DT3Core/Types/Math/Vector3.hpp"
#include "DT3Core/Resources/ResourceTypes/TextureResource2D.hpp"
#include "DT3Core/Types/Math/Rectangle.hpp"

#include "DT3HWVideoPlayer/FFmpeg/HWVideoPlayerFF.hpp"

namespace DT3 {

//==============================================================================
//==============================================================================

typedef HWVideoPlayerFF Video;

//==============================================================================
/// Video texture source.
//==============================================================================

class ScriptingVideoTexture: public ScriptingBase {
    public:
        DEFINE_TYPE(ScriptingVideoTexture,ScriptingBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE
         
                                    ScriptingVideoTexture	(void);
                                    ScriptingVideoTexture	(const ScriptingVideoTexture &rhs);
        ScriptingVideoTexture &     operator =				(const ScriptingVideoTexture &rhs);
        virtual                     ~ScriptingVideoTexture  (void);
    
        virtual void                archive                 (const std::shared_ptr<Archive> &archive);
        virtual void                archive_done            (const std::shared_ptr<Archive> &archive);
		
		/// Object was added to a world
		/// world world that object was added to
        virtual void                add_to_world            (World *world);

		/// Object was removed from a world
        virtual void                remove_from_world       (void);

	public:

		/// Called to initialize the object
		virtual void				initialize				(void);
				
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

		/// Returns the length of the video
        /// \return length (in seconds) of the video
        DTfloat                     length                  (void) const;

		/// Seeks to a position in the video
		/// \param time time to seek to
        void                        seek                    (DTfloat time);

	private:
        
        Plug<std::string>                   _file_or_url;
        std::string                         _last_file_or_url;
    
        Plug<DTboolean>                     _is_playing;
        Plug<DTfloat>                       _current_time;
        Plug<DTfloat>                       _length;
    
		Event                               _play;
		Event                               _pause;
		Event                               _rewind;
        
        std::shared_ptr<TextureResource2D>  _frame;
        Rectangle                           _frame_rect;

		Plug<std::shared_ptr<TextureResource2D> >   _out;
		Plug<Rectangle>                             _rectangle;
    
        Video::HWVideoPlayerType            _hw;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
