#ifndef DT3_COMPONENTUTILEXPIRE
#define DT3_COMPONENTUTILEXPIRE
//==============================================================================
///	
///	File: ComponentUtilExpire.hpp
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
class World;

//==============================================================================
/// A component that can expire its owner a few different ways. It can also
/// expire any connected nodes too.
//==============================================================================

class ComponentUtilExpire: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentUtilExpire,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                    ComponentUtilExpire     (void);	
									ComponentUtilExpire     (const ComponentUtilExpire &rhs);
        ComponentUtilExpire &       operator =              (const ComponentUtilExpire &rhs);	
        virtual                     ~ComponentUtilExpire	(void);
    
        virtual void                archive_read			(Archive *archive);
        virtual void                archive_write		(Archive *archive);
		
	public:
		/// Called to initialize the object
		virtual void				initialize			(void);
                
		/// Returns the component type. This defines which slot the component is
        /// put into on the object.
		/// \return Component type
        virtual ComponentType       getComponentType    (void)  {   return COMPONENT_UTILITY;  }

		/// Called when this component is added to the owner. Note that this will
        /// only be called if the owner is added to a world already. If not it 
        /// will be called when it is added to the World.
		/// \param owner Pointer to the owner
		virtual void                addToOwner          (ObjectBase *owner);

		/// Called when this component is removed from its owner.
		virtual void                removeFromOwner     (void);


		/// Starts the timer to expire the component and clean up nodes
		/// \param sender Sender of the event
        void                        startTimer          (PlugNode *sender);

		/// Stops the timer to expire the component and clean up nodes
		/// \param sender Sender of the event
        void                        stopTimer           (PlugNode *sender);

		/// Forces a cleanup immediately
		/// \param sender Sender of the event
        void                        expireNow           (PlugNode *sender);

		/// Callback called when the component is getting a tick
		/// \param dt delta time
        void                        tick                (DTfloat dt);

        /// Defines standard accessors for the timer running flag
		DEFINE_ACCESSORS            (getTimerRunning, setTimerRunning, DTboolean, _timer_running);

        /// Defines standard accessors for the timer time
		DEFINE_ACCESSORS            (getExpireTime, setExpireTime, DTfloat, _expire_time);
        
        /// Defines standard accessors for the remove connected nodes flag
		DEFINE_ACCESSORS            (getRemoveConnectedNodes, setRemoveConnectedNodes, DTboolean, _remove_connected_nodes);

    private:
        Plug<DTboolean>             _timer_running;
        DTfloat                     _expire_time;
        
        Event                       _start_timer;
        Event                       _stop_timer;
        Event                       _expire_now;
        
        DTboolean                   _remove_connected_nodes;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
