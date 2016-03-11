//==============================================================================
///	
///	File: ComponentUtilExpire.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentUtilExpire.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "World.hpp"
#include "ConsoleStream.hpp"
#include "PlugNodeUtils.hpp"
#include "ObjectBase.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentUtilExpire,"Utility","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentUtilExpire)

IMPLEMENT_PLUG_INFO(_timer_running)

IMPLEMENT_EVENT_INFO(_start_timer)
IMPLEMENT_EVENT_INFO(_stop_timer)
IMPLEMENT_EVENT_INFO(_expire_now)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentUtilExpire)

    PLUG_INIT(_timer_running, "Timer_Running")
		.setOutput(true);

    EVENT_INIT(_start_timer,"Start_Timer")
        .setInput(true)
        .setEvent(EventBindCreator(&ComponentUtilExpire::startTimer));
   
    EVENT_INIT(_stop_timer,"Stop_Timer")
        .setInput(true)
        .setEvent(EventBindCreator(&ComponentUtilExpire::stopTimer));
   
    EVENT_INIT(_expire_now,"Expire_Now")
        .setInput(true)
        .setEvent(EventBindCreator(&ComponentUtilExpire::expireNow));
   
END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentUtilExpire::ComponentUtilExpire (void)
    :   _timer_running          (PLUG_INFO(_timer_running), true),
        _start_timer            (EVENT_INFO(_start_timer)),
        _stop_timer             (EVENT_INFO(_stop_timer)),
        _expire_now             (EVENT_INFO(_expire_now)),
        _expire_time            (5.0F),
        _remove_connected_nodes (true)
{

}
		
ComponentUtilExpire::ComponentUtilExpire (const ComponentUtilExpire &rhs)
    :   ComponentBase           (rhs),
        _timer_running          (rhs._timer_running),
        _start_timer            (EVENT_INFO(_start_timer)),
        _stop_timer             (EVENT_INFO(_stop_timer)),
        _expire_now             (EVENT_INFO(_expire_now)),
        _expire_time            (rhs._expire_time),
        _remove_connected_nodes (rhs._remove_connected_nodes)
{

}

ComponentUtilExpire & ComponentUtilExpire::operator = (const ComponentUtilExpire &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
        
        _timer_running = rhs._timer_running;
        _expire_time = rhs._expire_time;
        
        _remove_connected_nodes = rhs._remove_connected_nodes;
    }
    return (*this);
}
			
ComponentUtilExpire::~ComponentUtilExpire (void)
{

}

//==============================================================================
//==============================================================================

void ComponentUtilExpire::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentUtilExpire::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
        		
	*archive << ARCHIVE_PLUG(_timer_running, DATA_PERSISTENT);
	*archive << ARCHIVE_DATA(_expire_time, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA(_remove_connected_nodes, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

void ComponentUtilExpire::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
	
	*archive << ARCHIVE_PLUG(_timer_running, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_expire_time, DATA_PERSISTENT | DATA_SETTABLE);

	*archive << ARCHIVE_DATA(_remove_connected_nodes, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentUtilExpire::startTimer (PlugNode *sender)
{
    World *w = getOwner()->getWorld();

    w->registerForTick(getOwner(), makeCallback(this, &type::tick));
}

void ComponentUtilExpire::stopTimer (PlugNode *sender)
{
    World *w = getOwner()->getWorld();

    w->unregisterForTick(getOwner(), makeCallback(this, &type::tick));
}

void ComponentUtilExpire::expireNow (PlugNode *sender)
{
    stopTimer(NULL);
    
    // Shortcut
    if (!_remove_connected_nodes) {
        getOwner()->getWorld()->removeNodeSafely(getOwner());
        return;
    }
            
    std::list<PlugNode*> connected;
    PlugNodeUtils::getAllConnectedNodes(getOwner(), connected);

    for (auto i : connected) {
        PlugNode *node = i;
    
        // Remove this node
        if (node->isA(WorldNode::kind())) {
            WorldNode *world_node = checkedStaticCast<WorldNode*>(node);
        
            World *world = world_node->getWorld();
            if (world) {
                world->removeNodeSafely(world_node);
            }
        }

    }
    
}

//==============================================================================
//==============================================================================

void ComponentUtilExpire::tick (DTfloat dt)
{
    _expire_time -= dt;
    if (_expire_time <= 0.0F)
        expireNow(NULL);
}

//==============================================================================
//==============================================================================

void ComponentUtilExpire::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
    
    if (_timer_running) {
        startTimer(NULL);
    }
}

void ComponentUtilExpire::removeFromOwner (void)
{
    stopTimer(NULL);
    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

} // DT3

