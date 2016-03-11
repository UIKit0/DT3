//==============================================================================
///	
///	File: ComponentGUIScrollerLayout.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentGUIScrollerLayout.hpp"
#include "Archive.hpp"
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

IMPLEMENT_FACTORY_CREATION_COMPONENT(ComponentGUIScrollerLayout,"GUIBehaviour","ComponentAdapter")
IMPLEMENT_PLUG_NODE(ComponentGUIScrollerLayout)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ComponentGUIScrollerLayout)
END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ComponentGUIScrollerLayout::ComponentGUIScrollerLayout (void)
    :   _content_width  (0.0F),
        _content_height (0.0F)
{

}
		
ComponentGUIScrollerLayout::ComponentGUIScrollerLayout (const ComponentGUIScrollerLayout &rhs)
    :   ComponentGUIScroller    (rhs),
        _content_width          (rhs._content_width),
        _content_height         (rhs._content_height)
{

}

ComponentGUIScrollerLayout & ComponentGUIScrollerLayout::operator = (const ComponentGUIScrollerLayout &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ComponentGUIScroller::operator = (rhs);
        
        _content_width = rhs._content_width;
        _content_height = rhs._content_height;
    }
    return (*this);
}
			
ComponentGUIScrollerLayout::~ComponentGUIScrollerLayout (void)
{

}

//==============================================================================
//==============================================================================

void ComponentGUIScrollerLayout::initialize (void)
{
	ComponentGUIScroller::initialize();
}

//==============================================================================
//==============================================================================

void ComponentGUIScrollerLayout::archive_read (Archive *archive)
{
    ComponentGUIScroller::archive_read(archive);

	archive->push_domain (getClassID ());
    
	*archive << ARCHIVE_DATA_ACCESSORS("Content_Width", ComponentGUIScrollerLayout::getContentWidth, ComponentGUIScrollerLayout::setContentWidth, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_ACCESSORS("Content_Height", ComponentGUIScrollerLayout::getContentHeight, ComponentGUIScrollerLayout::setContentHeight, DATA_PERSISTENT | DATA_SETTABLE);
    
    archive->pop_domain ();
}

void ComponentGUIScrollerLayout::archive_write (Archive *archive)
{
    ComponentGUIScroller::archive_write(archive);

    archive->push_domain (getClassID ());
    
	*archive << ARCHIVE_DATA_ACCESSORS("Content_Width", ComponentGUIScrollerLayout::getContentWidth, ComponentGUIScrollerLayout::setContentWidth, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA_ACCESSORS("Content_Height", ComponentGUIScrollerLayout::getContentHeight, ComponentGUIScrollerLayout::setContentHeight, DATA_PERSISTENT | DATA_SETTABLE);

    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ComponentGUIScrollerLayout::addToOwner (ObjectBase *owner)
{
    ComponentGUIScroller::addToOwner(owner);
}

void ComponentGUIScrollerLayout::removeFromOwner (void)
{
    ComponentGUIScroller::removeFromOwner();
}

//==============================================================================
//==============================================================================

void ComponentGUIScrollerLayout::arrangeItems (DTfloat time)
{
    GUIObject *gui = checkedCast<GUIObject*>(getOwner());
    if (!gui)
        return;
    
    if (_layout.isNull())
        return;
    
    DTfloat width = getScrollHorz() ? _content_width : gui->getRectangle().getWidth();
    DTfloat height = getScrollVert() ? _content_height : gui->getRectangle().getHeight();
    
    _layout->animate(Rectangle(-width*0.5F, width*0.5F, -height*0.5F, height*0.5F), time);

    calculateContectRect();
}

//==============================================================================
//==============================================================================

void ComponentGUIScrollerLayout::setLayout (std::shared_ptr<GUILayout> layout)
{
    _layout = layout;
}

std::shared_ptr<GUILayout> ComponentGUIScrollerLayout::getLayout (void) const
{
    return _layout;
}

void ComponentGUIScrollerLayout::setContentWidth (DTfloat width)
{
    _content_width = width;
}

DTfloat ComponentGUIScrollerLayout::getContentWidth (void) const
{
    return _content_width;
}

void ComponentGUIScrollerLayout::setContentHeight (DTfloat height)
{
    _content_height = height;
}

DTfloat ComponentGUIScrollerLayout::getContentHeight (void) const
{
    return _content_height;
}

//==============================================================================
//==============================================================================

} // DT3

