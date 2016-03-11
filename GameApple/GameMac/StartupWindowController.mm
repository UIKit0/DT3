//==============================================================================
///	
///	File: StartupWindowController.mm
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#import "StartupWindowController.h"
#import "AppDelegate.h"

#include "DT3Core/Types/Utility/DisplayMode.hpp"
#include DT3_HAL_INCLUDE_PATH
#include <map>

using namespace DT3;

//==============================================================================
//==============================================================================

@interface StartupWindowController ()

@end

@implementation StartupWindowController

- (id)initWithWindow:(NSWindow *)window
{
    self = [super initWithWindow:window];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

- (void)windowDidLoad
{
    [super windowDidLoad];
    
    //
    // Populate Displays
    //
    
    std::map<DTint, std::vector<DisplayMode>> modes;
    HAL::display_modes (modes);
    
    // Extract displays
    std::vector<DTint> displays;
    for (auto i = modes.begin(); i != modes.end(); ++i) {
        displays.push_back(i->first);
    }
    
    // Make sure entries are unique
    std::sort(displays.begin(), displays.end());
    auto e = std::unique(displays.begin(), displays.end());
    displays.erase(e, displays.end());
    
    // Update displays menus
    [_display removeAllItems];
    for (std::size_t i = 0; i < displays.size(); ++i) {
        NSString *s = [NSString stringWithFormat:@"%d", displays[i]];
        [_display addItemWithTitle: s];
    }
            
    //
    // Read saved values
    //
    
    LaunchParameters launch_parameters;
    [[AppDelegate getAppDelegate] getLaunchParameters:&launch_parameters];
    
    NSString *s = [NSString stringWithFormat:@"%d", launch_parameters.display];
    
    // Set the selected display
    [_display selectItemWithTitle:s];
    [self displayChanged:NULL];
    
    // Set the selected resolution
    s = [NSString stringWithFormat:@"%dx%d", launch_parameters.resolution_width, launch_parameters.resolution_height];
    [_resolution selectItemWithTitle:s];
 
    // Set windowed flag
    [_windowed setState:launch_parameters.windowed];
    
    // Show at startup windowed flag
    [_show_at_startup setState:launch_parameters.show_at_startup];

    // Set command line params
    [_command_line setStringValue:launch_parameters.command_line];
}

- (IBAction)quit:(id)sender {
    [[AppDelegate getAppDelegate] exit];
    [self close];
}

- (IBAction)play:(id)sender {
    LaunchParameters launch_parameters;
    
    // Display index
    launch_parameters.display = [[[_display selectedItem] title] intValue];
    
    // Extract resolution
    NSArray *res = [[[_resolution selectedItem] title] componentsSeparatedByString:@"x"];
    launch_parameters.resolution_width = [[res objectAtIndex:0] intValue];
    launch_parameters.resolution_height = [[res objectAtIndex:1] intValue];
    
    // Windowed
    launch_parameters.windowed = (BOOL) [_windowed state];
    
    // Startup dialog
    launch_parameters.show_at_startup = (BOOL) [_show_at_startup state];
    launch_parameters.command_line = nil;

    [[AppDelegate getAppDelegate] setLaunchParameters:launch_parameters];
    [[AppDelegate getAppDelegate] launch];

    [self close];
}

- (IBAction)displayChanged:(id)sender {
    //
    // Populate Resolutions
    //
    
    std::map<DTint, std::vector<DisplayMode>> modes;
    HAL::display_modes (modes);
    
    DTint display_id = [[[_display selectedItem] title] intValue];
    
    std::vector<DisplayMode> &resolutions = modes[display_id];
    
    // Update resolutions menu
    [_resolution removeAllItems];
    for (std::size_t i = 0; i < resolutions.size(); ++i) {
        NSString *s = [NSString stringWithFormat:@"%dx%d", resolutions[i].width(), resolutions[i].height()];
        [_resolution addItemWithTitle: s];
    }

}
@end

//==============================================================================
//==============================================================================

