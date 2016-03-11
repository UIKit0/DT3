//==============================================================================
///	
///	File: ComponentGUIScrollerGrid.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentGUIScrollerGrid.hpp"
#include "ArchiveObjectQueue.hpp"
#include "Factory.hpp"
#include "PlaceableObject.hpp"
#include "GUIObject.hpp"
#include "System.hpp"
#include "Algorithm.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentGUIScrollerGrid,"GUIBehaviour","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentGUIScrollerGrid)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentGUIScrollerGrid)
END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentGUIScrollerGrid::ComponentGUIScrollerGrid (void)
    :   _column_width   (0.1F),
        _row_height     (0.75F),
        _column_padding (0.0F),
        _row_padding    (0.0F),
        _num_columns    (-1),
        _num_rows       (-1)
{

}
		
ComponentGUIScrollerGrid::ComponentGUIScrollerGrid (const ComponentGUIScrollerGrid &rhs)
    :   ComponentGUIScroller    (rhs),
        _column_width   (rhs._column_width),
        _row_height     (rhs._row_height),
        _column_padding (rhs._column_padding),
        _row_padding    (rhs._row_padding),
        _num_columns    (rhs._num_columns),
        _num_rows       (rhs._num_rows)
{

}

ComponentGUIScrollerGrid & ComponentGUIScrollerGrid::operator = (const ComponentGUIScrollerGrid &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentGUIScroller::operator = (rhs);
        
        _column_width = rhs._column_width;
        _row_height = rhs._row_height;

        _column_padding = rhs._column_padding;
        _row_padding = rhs._row_padding;

        _num_columns = rhs._num_columns;
        _num_rows = rhs._num_rows;
    }
    return (*this);
}
			
ComponentGUIScrollerGrid::~ComponentGUIScrollerGrid (void)
{

}

//==============================================================================
//==============================================================================

void ComponentGUIScrollerGrid::initialize (void)
{
	ComponentGUIScroller::initialize();
}

//==============================================================================
//==============================================================================

void ComponentGUIScrollerGrid::archive_read (Archive *archive)
{
    ComponentGUIScroller::archive_read(archive);

	archive->push_domain (getClassID ());
    
	*archive << ARCHIVE_DATA_ACCESSORS("Num_Columns", ComponentGUIScrollerGrid::getNumColumns, ComponentGUIScrollerGrid::setNumColumns, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_ACCESSORS("Num_Rows", ComponentGUIScrollerGrid::getNumRows, ComponentGUIScrollerGrid::setNumRows, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_ACCESSORS("Column_Width", ComponentGUIScrollerGrid::getColumnWidth, ComponentGUIScrollerGrid::setColumnWidth, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_ACCESSORS("Row_Height", ComponentGUIScrollerGrid::getRowHeight, ComponentGUIScrollerGrid::setRowHeight, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_ACCESSORS("Column_Padding", ComponentGUIScrollerGrid::getColumnPadding, ComponentGUIScrollerGrid::setColumnPadding, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_ACCESSORS("Row_Padding", ComponentGUIScrollerGrid::getRowPadding, ComponentGUIScrollerGrid::setRowPadding, DATA_PERSISTENT | DATA_SETTABLE);
    
    archive->pop_domain ();
}

void ComponentGUIScrollerGrid::archive_write (Archive *archive)
{
    ComponentGUIScroller::archive_write(archive);

    archive->push_domain (getClassID ());
    
	*archive << ARCHIVE_DATA_ACCESSORS("Num_Columns", ComponentGUIScrollerGrid::getNumColumns, ComponentGUIScrollerGrid::setNumColumns, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_ACCESSORS("Num_Rows", ComponentGUIScrollerGrid::getNumRows, ComponentGUIScrollerGrid::setNumRows, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_ACCESSORS("Column_Width", ComponentGUIScrollerGrid::getColumnWidth, ComponentGUIScrollerGrid::setColumnWidth, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_ACCESSORS("Row_Height", ComponentGUIScrollerGrid::getRowHeight, ComponentGUIScrollerGrid::setRowHeight, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_ACCESSORS("Column_Padding", ComponentGUIScrollerGrid::getColumnPadding, ComponentGUIScrollerGrid::setColumnPadding, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_ACCESSORS("Row_Padding", ComponentGUIScrollerGrid::getRowPadding, ComponentGUIScrollerGrid::setRowPadding, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentGUIScrollerGrid::addToOwner (ObjectBase *owner)
{
    ComponentGUIScroller::addToOwner(owner);
}

void ComponentGUIScrollerGrid::removeFromOwner (void)
{
    ComponentGUIScroller::removeFromOwner();
}

//==============================================================================
//==============================================================================

void ComponentGUIScrollerGrid::setNumColumns (DTint num_cols)
{
    _num_columns = num_cols;
    arrangeItems(0.0F);
}

DTint ComponentGUIScrollerGrid::getNumColumns (void) const
{
    return _num_columns;
}

void ComponentGUIScrollerGrid::setNumRows (DTint num_rows)
{
    _num_rows = num_rows;
    arrangeItems(0.0F);
}

DTint ComponentGUIScrollerGrid::getNumRows (void) const
{
    return _num_rows;
}

//==============================================================================
//==============================================================================

void ComponentGUIScrollerGrid::setColumnWidth (DTfloat column_width)
{
    _column_width = column_width;
    arrangeItems(0.0F);
}

DTfloat ComponentGUIScrollerGrid::getColumnWidth (void) const
{
    return _column_width;
}

void ComponentGUIScrollerGrid::setRowHeight (DTfloat row_height)
{
    _row_height = row_height;
    arrangeItems(0.0F);
}

DTfloat ComponentGUIScrollerGrid::getRowHeight (void) const
{
    return _row_height;
}

//==============================================================================
//==============================================================================

void ComponentGUIScrollerGrid::setColumnPadding (DTfloat column_padding)
{
    _column_padding = column_padding;
    arrangeItems(0.0F);
}

DTfloat ComponentGUIScrollerGrid::getColumnPadding (void) const
{
    return _column_padding;
}

void ComponentGUIScrollerGrid::setRowPadding (DTfloat row_padding)
{
    _row_padding = row_padding;
    arrangeItems(0.0F);
}

DTfloat ComponentGUIScrollerGrid::getRowPadding (void) const
{
    return _row_padding;
}

//==============================================================================
//==============================================================================

void ComponentGUIScrollerGrid::arrangeItemsDone(void)
{
    calculateContectRect();
}

//==============================================================================
//==============================================================================

void ComponentGUIScrollerGrid::arrangeItems (DTfloat time)
{
    PlaceableObject *placeable = checkedCast<PlaceableObject*>(getOwner());
    if (!placeable)
        return;

    DTuint index = 0;
    DTuint xi = 0,yi = 0;
        
    DTfloat column_width = _column_width;
    DTfloat row_height = _row_height;
    
    DTfloat column_padding = _column_padding;
    DTfloat row_padding = _row_padding;
    
    Rectangle old_contents = getContectRect();
    
    const std::list<PlaceableObject*> &children = placeable->getChildren();
    std::list<PlaceableObject*>::iterator i;
    
    FOR_EACH (i,children) {
        GUIObject *gui = checkedCast<GUIObject*>(*i);
        if (!gui)
            continue;
            
        if (_num_columns > 0) {
            xi = index % _num_columns;
            yi = index / _num_columns;
        } else if (_num_rows > 0) {
            xi = index / _num_rows;
            yi = index % _num_rows;
        }

        DTfloat xpos = /*old_contents.getMinusX() +*/ xi * (column_width + column_padding) + column_width * 0.5F - 0.5F * column_width * _num_columns;
        DTfloat ypos = /*old_contents.getMinusY() +*/ yi * (row_height + row_padding) + row_height * 0.5F - 0.5F * row_height * _num_rows;
        
        if (_num_columns == 1)  xpos = 0.0F;
        if (_num_rows == 1)     ypos = 0.0F;
        
        gui->setWidth(column_width);
        gui->setHeight(row_height);
        
        if (time == 0.0F) {
            gui->setTranslationLocal(Vector3(xpos, ypos, 0.0F));
            arrangeItemsDone();
        } else {
            gui->addAnimKey()
                .setDuration(time)
                .setTranslationLocal(Vector3(xpos, ypos, 0.0F));
                        
            gui->addAnimKey()
                .setCall(makeLatentCall(this, &type::arrangeItemsDone));
        }
        
        ++index;
    }
        
}

//==============================================================================
//==============================================================================

DTint ComponentGUIScrollerGrid::callbackCompareGUIX(PlaceableObject *a, PlaceableObject *b)
{
    if (a->getTranslation().x > b->getTranslation().x)
        return 1;
    if (a->getTranslation().x < b->getTranslation().x)
        return -1;
        
    return 0;
}

//==============================================================================
//==============================================================================

void ComponentGUIScrollerGrid::draggingItem (GUIObject *item)  
{
    if (_num_rows == 1) {
        Vector3 translation = item->getTranslationLocal();
        translation.y = 0.0F;
        translation.z = 1.0F;
        item->setTranslationLocal(translation);
    
    }

    if (_num_columns == 1) {
        Vector3 translation = item->getTranslationLocal();
        translation.x = 0.0F;
        translation.z = 1.0F;
        item->setTranslationLocal(translation);
    
    }
    
    item->setScale(Vector3(1.1F));
}

void ComponentGUIScrollerGrid::finishedDraggingItem (GUIObject *item)
{
    // Restore z pos
    Vector3 translation = item->getTranslationLocal();
    translation.z = 0.0F;
    item->setTranslationLocal(translation);


    
    PlaceableObject *placeable = checkedCast<PlaceableObject*>(getOwner());
    if (!placeable)
        return;

    const std::list<PlaceableObject*> &children = placeable->getChildren();
    std::list<PlaceableObject*> sorted;
    
    std::list<PlaceableObject*>::iterator i;
    
    // Temporarily remove children of GUI object
    FOR_EACH (i,children) {
        sorted.pushBack(RETAIN(*i));
    }
    placeable->unparentChildren();
    
    // Sort
    if (_num_rows == 1) {
        Algorithm::bubblesort(sorted, &callbackCompareGUIX);
    }
    
    // Re add sorted children
    FOR_EACH (i,sorted) {
        placeable->addChild(*i);
        RELEASE(*i);
    }
    
    // Rearrange items
    stopWiggle();
    arrangeItems(0.2F);
    startWiggle();

    item->setScale(Vector3(1.0F));
}

//==============================================================================
//==============================================================================

void ComponentGUIScrollerGrid::deleteItem (GUIObject *item)  
{
    ComponentGUIScroller::deleteItem(item); 

    stopWiggle();
    arrangeItems(0.2F);
    startWiggle();
}

//==============================================================================
//==============================================================================

} // DT3

