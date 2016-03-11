//==============================================================================
///	
///	File: GameOpenGLView.m
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#import "GameOpenGLView.h"
#import "AppDelegate.h"

@implementation GameOpenGLView

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

//==============================================================================
//==============================================================================

- (BOOL)acceptsFirstResponder
{
    return YES;
}

- (BOOL)becomeFirstResponder
{
    return YES;
}

- (BOOL)resignFirstResponder
{
    return YES;
}

//==============================================================================
//==============================================================================

- (void)keyDown:(NSEvent *)event
{
    [[AppDelegate getAppDelegate] keyDown:event];
}

- (void)keyUp:(NSEvent *)event
{
    [[AppDelegate getAppDelegate] keyUp:event];
}

//==============================================================================
//==============================================================================

- (void)mouseDown:(NSEvent *)event
{
    [[AppDelegate getAppDelegate] mouseDown:event];
}

- (void)mouseDragged:(NSEvent *)event
{
    [[AppDelegate getAppDelegate] mouseDragged:event];
}

- (void)mouseMoved:(NSEvent *)event
{
    [[AppDelegate getAppDelegate] mouseMoved:event];
}

- (void)mouseUp:(NSEvent *)event
{
    [[AppDelegate getAppDelegate] mouseUp:event];
}

//==============================================================================
//==============================================================================

@end
