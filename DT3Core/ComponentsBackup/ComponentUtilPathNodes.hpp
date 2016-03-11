#ifndef DT3_COMPONENTUTILPATHNODES
#define DT3_COMPONENTUTILPATHNODES
//==============================================================================
///	
///	File: ComponentUtilPathNodes.hpp
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

class World;

//==============================================================================
/// A component that defines a path node network. Nodes can be arbitrarily
/// connected to other nodes.
//==============================================================================

class ComponentUtilPathNodes: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentUtilPathNodes,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                    ComponentUtilPathNodes  (void);	
									ComponentUtilPathNodes  (const ComponentUtilPathNodes &rhs);
        ComponentUtilPathNodes &    operator =              (const ComponentUtilPathNodes &rhs);	
        virtual                     ~ComponentUtilPathNodes	(void);
    
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

		/// Sets the number of nodes in the network
		/// \param num_nodes Number of nodes in the network
        void                        setNumNodes         (DTsize num_nodes)  {   _nodes.resize(num_nodes);   }
    
		/// Returns the number of nodes in the network
		/// return Number of nodes in the network
        DTsize                      getNumNodes         (void) const        {   return _nodes.size();       }


		/// Removes a node from the network
		/// \param node_id index of node to remove
        void                        deleteNode          (DTint node_id);

		/// Adds a connection from one node to another
		/// \param node_id from node
		/// \param other_node_id to node
        void                        addConnection       (DTint node_id, DTint other_node_id);

		/// Removes a connection from one node to another
		/// \param node_id from node
		/// \param other_node_id to node
        void                        deleteConnection    (DTint node_id, DTint other_node_id);

        
        struct Node {
            Node (void) : position(0.0F,0.0F,0.0F)  {}
        
            Vector3                 position;
            std::vector<DTint>            outgoing;
        };
    
        /// Returns all of the path nodes
		/// \return Path nodes
        const std::vector<Node>&          getNodes            (void) const  {   return _nodes;  }

    private:
        friend class EdManipComponentUtilPathNodes;
    
        std::vector<Node>                 _nodes;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
