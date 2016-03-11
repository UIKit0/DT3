//==============================================================================
///	
///	File: StartupWindowController.h
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#import <Cocoa/Cocoa.h>

@interface StartupWindowController : NSWindowController

@property (assign) IBOutlet NSButton *windowed;
@property (assign) IBOutlet NSTextField *command_line;
@property (assign) IBOutlet NSPopUpButton *resolution;
@property (assign) IBOutlet NSPopUpButton *display;
@property (assign) IBOutlet NSButton *show_at_startup;

- (IBAction)quit:(id)sender;
- (IBAction)play:(id)sender;
- (IBAction)displayChanged:(id)sender;

@end

//==============================================================================
//==============================================================================
