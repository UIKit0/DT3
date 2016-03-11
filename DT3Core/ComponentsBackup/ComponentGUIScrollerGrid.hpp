#ifndef DT3_COMPONENTGUISCROLLERGRID
#define DT3_COMPONENTGUISCROLLERGRID
//==============================================================================
///	
///	File: ComponentGUIScrollerGrid.hpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentGUIScroller.hpp"
#include "PlaceableObject.hpp"

namespace DT3 {

//==============================================================================
/// GUI behaviour for a scroll zone. It scrolls its children objects.
/// This component arranges its children into a grid
//==============================================================================

class ComponentGUIScrollerGrid: public ComponentGUIScroller {
    public:
        DEFINE_TYPE(ComponentGUIScrollerGrid,ComponentGUIScroller)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                    ComponentGUIScrollerGrid	(void);	
									ComponentGUIScrollerGrid	(const ComponentGUIScrollerGrid &rhs);
        ComponentGUIScrollerGrid&   operator =                  (const ComponentGUIScrollerGrid &rhs);	
        virtual                     ~ComponentGUIScrollerGrid	(void);
    
        virtual void                archive_read			(Archive *archive);
        virtual void                archive_write		(Archive *archive);
		
	public:
		/// Called to initialize the object
		virtual void				initialize			(void);
        
		/// Called when this component is added to the owner. Note that this will
        /// only be called if the owner is added to a world already. If not it 
        /// will be called when it is added to the World.
		/// \param owner Pointer to the owner
		virtual void                addToOwner          (ObjectBase *owner);

		/// Called when this component is removed from its owner.
		virtual void                removeFromOwner     (void);
        
        /// Set the number of columns
		/// \param num_cols number of columns
        void                        setNumColumns       (DTint num_cols);

        /// Returns the number of columns
		/// \return number of columns
        DTint                       getNumColumns       (void) const;

        /// Set the number of rows
		/// \param num_rows number of rows
        void                        setNumRows          (DTint num_rows);
    
        /// Returns the number of rows
		/// \return num_rows number of rows
        DTint                       getNumRows          (void) const;
        
        
        /// Set the width of the columns
		/// \param column_width width of columns
        void                        setColumnWidth      (DTfloat column_width);
    
        /// Returns the width of the columns
		/// \return width of columns
        DTfloat                     getColumnWidth      (void) const;

        /// Set the height of the rows
		/// \param row_height height of rows
        void                        setRowHeight        (DTfloat row_height);
    
        /// Returns the height of the rows
		/// \return height of rows
        DTfloat                     getRowHeight        (void) const;
                
        /// Set the padding of the columns
		/// \param padding padding of columns
        void                        setColumnPadding    (DTfloat padding);
    
        /// Returns the padding of the columns
		/// \return padding of columns
        DTfloat                     getColumnPadding    (void) const;
        
        /// Set the padding of the rows
		/// \param padding padding of rows
        void                        setRowPadding       (DTfloat padding);
    
        /// Returns the padding of the rows
		/// \return padding of rows
        DTfloat                     getRowPadding       (void) const;
        
        /// Animate the placement of the children
		/// \param time animation duration
        void                        arrangeItems        (DTfloat time);
        
    protected:
		/// Called while an item is being dragged
        virtual void                draggingItem        (GUIObject *item);

		/// Called while an item is being dragged
        virtual void                finishedDraggingItem(GUIObject *item);

		/// Called while an item is being deleted
        virtual void                deleteItem          (GUIObject *item);

    private:        
        void                        arrangeItemsDone    (void);

        static DTint                callbackCompareGUIX (PlaceableObject *a, PlaceableObject *b);
    
        DTfloat                     _column_width;
        DTfloat                     _row_height;
        DTfloat                     _column_padding;
        DTfloat                     _row_padding;
    
        DTint                       _num_columns;
        DTint                       _num_rows;
        
        DTint                       _units;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
