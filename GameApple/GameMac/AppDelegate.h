//==============================================================================
///	
///	File: AppDelegate.h
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#import <Cocoa/Cocoa.h>
#import "GameOpenGLView.h"

#include "TouchEvent.hpp"

struct LaunchParameters {
    int display;
    int resolution_width;
    int resolution_height;
    
    BOOL windowed;
    
    NSString *command_line;
    
    BOOL show_at_startup;
};

@interface AppDelegate : NSObject <NSApplicationDelegate>

@property (assign) LaunchParameters launch_parameters;

@property (assign) int capture_mouse;
@property (assign) NSWindow *window;

@property (assign) GameOpenGLView *opengl_view;

@property (assign) DT3::TouchEvent touch_event;


// Static method to get the App delegate (i.e. this class)
+ (AppDelegate *)getAppDelegate;

// Static method to get the OpenGL context
+ (NSOpenGLContext*)getOpenGLContext;

// Sets the launch parameters for the app
- (void)setLaunchParameters:(LaunchParameters)launch_parameters;

// Returns the launch parameters for the app
- (void)getLaunchParameters:(LaunchParameters*)launch_parameters;

// Begin Capture mouse
- (void) beginCaptureMouse;

// End Capture mouse
- (void) endCaptureMouse;


// Launch the game
- (void) launch;

// Exit the game
- (void) exit;

@end
