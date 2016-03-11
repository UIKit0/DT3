//==============================================================================
///	
///	File: ComponentUtilPathNodes.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentUtilPathNodes.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "World.hpp"
#include "ConsoleStream.hpp"
#include "StringCast.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentUtilPathNodes,"Utility","EdManipComponentUtilPathNodes")
IMPLEMENT_PLUG_NODE(ComponentUtilPathNodes)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentUtilPathNodes)   
END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentUtilPathNodes::ComponentUtilPathNodes (void)
{

}
		
ComponentUtilPathNodes::ComponentUtilPathNodes (const ComponentUtilPathNodes &rhs)
    :   ComponentBase           (rhs)
{

}

ComponentUtilPathNodes & ComponentUtilPathNodes::operator = (const ComponentUtilPathNodes &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentBase::operator = (rhs);
    }
    return (*this);
}
			
ComponentUtilPathNodes::~ComponentUtilPathNodes (void)
{

}

//==============================================================================
//==============================================================================

void ComponentUtilPathNodes::initialize (void)
{
	ComponentBase::initialize();
}

//==============================================================================
//==============================================================================

void ComponentUtilPathNodes::archive_read (Archive *archive)
{
    ComponentBase::archive_read(archive);

	archive->push_domain (getClassID ());
    
    *archive << ARCHIVE_DATA_ACCESSORS("Num_Nodes", ComponentUtilPathNodes::getNumNodes, ComponentUtilPathNodes::setNumNodes, DATA_PERSISTENT | DATA_SETTABLE | DATA_FLUSH_UI);
    
    for (DTsize i = 0; i < _nodes.size(); ++i) {
        *archive << ARCHIVE_DATA_NAMED("Node_" + castToString(i), _nodes[i].position, DATA_PERSISTENT | DATA_SETTABLE);
        
        DTsize num_outgoing;
        *archive << ARCHIVE_DATA(num_outgoing, DATA_PERSISTENT);
        _nodes[i].outgoing.resize(num_outgoing);

        for (DTsize j = 0; j < _nodes[i].outgoing.size(); ++j) {
            *archive << ARCHIVE_DATA_RAW(_nodes[i].outgoing[j], DATA_PERSISTENT);
        }
    }

    archive->pop_domain ();
}

void ComponentUtilPathNodes::archive_write (Archive *archive)
{
    ComponentBase::archive_write(archive);

    archive->push_domain (getClassID ());
    
    *archive << ARCHIVE_DATA_ACCESSORS("Num_Nodes", ComponentUtilPathNodes::getNumNodes, ComponentUtilPathNodes::setNumNodes, DATA_PERSISTENT | DATA_SETTABLE | DATA_FLUSH_UI);
    
    for (DTsize i = 0; i < _nodes.size(); ++i) {
        *archive << ARCHIVE_DATA_NAMED("Node_" + castToString(i), _nodes[i].position, DATA_PERSISTENT | DATA_SETTABLE);
        
        DTsize num_outgoing = _nodes[i].outgoing.size();
        *archive << ARCHIVE_DATA(num_outgoing, DATA_PERSISTENT);

        for (DTsize j = 0; j < _nodes[i].outgoing.size(); ++j) {
            *archive << ARCHIVE_DATA_RAW(_nodes[i].outgoing[j], DATA_PERSISTENT);
        }
    }

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentUtilPathNodes::deleteNode (DTint node_id)
{
    _nodes.erase(node_id);
    
    // Renumber all connections
    for (DTint i = 0; i < _nodes.size(); ++i) {
    
        deleteConnection(i, node_id);
        
        for (DTsize j = 0; j < _nodes[i].outgoing.size(); ++j) {
            if (_nodes[i].outgoing[j] > node_id) {
                --_nodes[i].outgoing[j];
            }
        }
        
    }
}

void ComponentUtilPathNodes::addConnection (DTint node_id, DTint other_node_id)
{
    std::vector<DTint> &outgoing = _nodes[node_id].outgoing;
    
    if (outgoing.find(other_node_id) == outgoing.end()) {
        outgoing.pushBack(other_node_id);
    }
}

void ComponentUtilPathNodes::deleteConnection (DTint node_id, DTint other_node_id)
{
    std::vector<DTint> &outgoing = _nodes[node_id].outgoing;
    std::vector<DTint>::iterator i = outgoing.find(other_node_id);
    
    if (i != outgoing.end()) {
        outgoing.erase(i);
    }
}

//==============================================================================
//==============================================================================

void ComponentUtilPathNodes::addToOwner (ObjectBase *owner)
{
    ComponentBase::addToOwner(owner);
}

void ComponentUtilPathNodes::removeFromOwner (void)
{
    ComponentBase::removeFromOwner();
}

//==============================================================================
//==============================================================================

} // DT3

