//==============================================================================
///	
///	File: AppDelegate.mm
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#import "AppDelegate.h"
#import "StartupWindowController.h"

#include "DT3Core/System/SystemCallbacks.hpp"
#include "DT3Core/System/Globals.hpp"
#include "DT3Core/Entry/GameMainThread.hpp"
#include "DT3Core/Types/Utility/MoreStrings.hpp"
#include "DT3Core/Types/Utility/DisplayMode.hpp"
#include "DT3Core/Types/Utility/ConsoleStream.hpp"
#include "DT3Core/Devices/DeviceInput.hpp"
#include DT3_HAL_INCLUDE_PATH

#import <Carbon/Carbon.h>
#import <OpenGL/gl.h>
#import <OpenGL/glext.h>

using namespace DT3;

//==============================================================================
//==============================================================================

const char PLATFORM_DISPLAY[]       = "PLATFORM_DISPLAY";
const char PLATFORM_RES_WIDTH[]     = "PLATFORM_RES_WIDTH";  // Will get corrected later
const char PLATFORM_RES_HEIGHT[]    = "PLATFORM_RES_HEIGHT";
const char PLATFORM_WINDOWED[]      = "PLATFORM_WINDOWED";
const char PLATFORM_COMMAND_LINE[]  = "PLATFORM_COMMAND_LINE";
const char PLATFORM_SHOW_AT_STARTUP[]  = "PLATFORM_SHOW_AT_STARTUP";

//==============================================================================
//==============================================================================

void screenInited (void)
{
    // In order to render with OpenGL from another thread, this has
    // to be called in the thread. Conveniently, this callback will
    // be called when the screen has been opened.
    [[AppDelegate getOpenGLContext] makeCurrentContext];
}

void screenClosed (void)
{
    // Screen is invalid so clear the current context
    [NSOpenGLContext clearCurrentContext];
}

void screenSwap (void)
{
    ::glSwapAPPLE();
}

void beginCaptureMouse (void)
{
    [[[NSApplication sharedApplication] delegate] beginCaptureMouse];
}

void endCaptureMouse (void)
{
    [[[NSApplication sharedApplication] delegate] endCaptureMouse];
}

//==============================================================================
//==============================================================================

@implementation AppDelegate

- (void)dealloc
{
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    //
    // Start engine
    //

    // Initialize the engine. Do it before "start" is called on the main loop. This will run it synchronously
    DT3::GameMainThread::initialize_engine();
    
    // Register callbacks
    DT3::SystemCallbacks::screen_inited_cb().add(DT3::make_callback(screenInited));
    DT3::SystemCallbacks::screen_closed_cb().add(DT3::make_callback(screenClosed));
    DT3::SystemCallbacks::screen_swap_cb().add(DT3::make_callback(screenSwap));

    DT3::SystemCallbacks::begin_capture_mouse_cb().add(DT3::make_callback(beginCaptureMouse));
    DT3::SystemCallbacks::end_capture_mouse_cb().add(DT3::make_callback(endCaptureMouse));

    // Process arguments
    NSArray *arguments = [[NSProcessInfo processInfo] arguments];
    std::vector<std::string> arguments_s;

    for (NSUInteger i = 1; i < [arguments count]; ++i) {
        const char *argument_c = [[arguments objectAtIndex:i] UTF8String];
        arguments_s.push_back(argument_c);
    }
    DT3::GameMainThread::process_arguments(arguments_s);

    //
    // Load settings
    //
        
    // Set some defaults
    Globals::set_global_default(PLATFORM_DISPLAY, "0", Globals::PERSISTENT);      // Will get corrected later
    Globals::set_global_default(PLATFORM_RES_WIDTH, "0", Globals::PERSISTENT);    // Will get corrected later
    Globals::set_global_default(PLATFORM_RES_HEIGHT, "0", Globals::PERSISTENT);   // Will get corrected later
    Globals::set_global_default(PLATFORM_WINDOWED, "1", Globals::PERSISTENT);
    Globals::set_global_default(PLATFORM_COMMAND_LINE, "", Globals::PERSISTENT);
    Globals::set_global_default(PLATFORM_SHOW_AT_STARTUP, "1", Globals::PERSISTENT);
    
    
    _launch_parameters.display = MoreStrings::cast_from_string<DTint>(Globals::global(PLATFORM_DISPLAY));
    _launch_parameters.resolution_width = MoreStrings::cast_from_string<DTint>(Globals::global(PLATFORM_RES_WIDTH));
    _launch_parameters.resolution_height = MoreStrings::cast_from_string<DTint>(Globals::global(PLATFORM_RES_HEIGHT));
    _launch_parameters.windowed = MoreStrings::cast_from_string<DTboolean>(Globals::global(PLATFORM_WINDOWED));
    _launch_parameters.command_line = @""; //MoreStrings::cast_from_string<DTint>(Globals::global(PLATFORM_COMMAND_LINE));
    _launch_parameters.show_at_startup = MoreStrings::cast_from_string<DTboolean>(Globals::global(PLATFORM_SHOW_AT_STARTUP));

    // Validate the settings just in case hardware capabilities changed
    std::map<DTint, std::vector<DisplayMode>> modes;
    HAL::display_modes (modes);
    
    if (modes.size() == 0)
        [self exit];
    
    // Check if display exists
    if (modes.find(_launch_parameters.display) == modes.end()) {
        _launch_parameters.display = modes.begin()->first;
        _launch_parameters.show_at_startup = true;
    }
    
    // If fullscreen, check resolution
    if (!_launch_parameters.windowed || _launch_parameters.resolution_width == 0 || _launch_parameters.resolution_height == 0) {
        // Check if resolution exists
        DisplayMode m;
        m.set_width(_launch_parameters.resolution_width);
        m.set_height(_launch_parameters.resolution_height);
        
        std::vector<DisplayMode> &resolutions = modes[_launch_parameters.display];
        if (resolutions.size() == 0)
            [self exit];
        
        if (std::find(resolutions.begin(), resolutions.end(), m) == resolutions.end()) {
            _launch_parameters.resolution_width = resolutions[resolutions.size()-1].width();
            _launch_parameters.resolution_height = resolutions[resolutions.size()-1].height();
            _launch_parameters.show_at_startup = true;
        }
    }
    
    
    // Show startup dialog
    DTboolean option_key = GetCurrentKeyModifiers() & optionKey;
    
    if (_launch_parameters.show_at_startup || option_key) {
        StartupWindowController *startup_controller = [[StartupWindowController alloc] initWithWindowNibName:@"StartupWindowController"];
        [startup_controller showWindow:self];
    } else {
        [self launch];
    }
}

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender
{
    //
    // Save settings
    //
    
    Globals::set_global(PLATFORM_DISPLAY, MoreStrings::cast_to_string(_launch_parameters.display), Globals::PERSISTENT);
    Globals::set_global(PLATFORM_RES_WIDTH, MoreStrings::cast_to_string(_launch_parameters.resolution_width), Globals::PERSISTENT);
    Globals::set_global(PLATFORM_RES_HEIGHT, MoreStrings::cast_to_string(_launch_parameters.resolution_height), Globals::PERSISTENT);
    Globals::set_global(PLATFORM_WINDOWED, MoreStrings::cast_to_string( (DTboolean) _launch_parameters.windowed), Globals::PERSISTENT);
    //Globals::set_global(PLATFORM_COMMAND_LINE, MoreStrings::cast_to_string(_launch_parameters.command_line), Globals::PERSISTENT);
    Globals::set_global(PLATFORM_SHOW_AT_STARTUP, MoreStrings::cast_to_string( (DTboolean) _launch_parameters.show_at_startup), Globals::PERSISTENT);


    // Hide the engine
    DT3::GameMainThread::hide_engine();
    
    // Stop the main loop (and consume all pending events)
    DT3::GameMainThread::stop();

    // Destroy the engine
    DT3::GameMainThread::destroy_engine();

    return NSTerminateNow;
}

//==============================================================================
//==============================================================================

+ (AppDelegate *)getAppDelegate
{
    return (AppDelegate *)[[NSApplication sharedApplication] delegate];
}

+ (NSOpenGLContext *)getOpenGLContext
{
    return [[AppDelegate getAppDelegate].opengl_view openGLContext];
}


- (void)setLaunchParameters:(LaunchParameters)launch_parameters
{
    self.launch_parameters = launch_parameters;
}

- (void)getLaunchParameters:(LaunchParameters*)launch_parameters
{
    *launch_parameters = self.launch_parameters;
}

- (void) launch
{

    // "Synthesized" events (ones that don't come from hardware),
    // more specifically, ones from CGWarpMouseCursorPosition(),
    // trigger a "suppression interval" during which events from
    // local hardware (the user's physical mouse) are ignored for
    // a default of 0.25 seconds. We really don't want that, so
    // we turn it off. 
    // This function is deprecated but there's no way around it.
    CGSetLocalEventsSuppressionInterval(0.0);


    NSOpenGLPixelFormatAttribute attrs[] =  {   NSOpenGLPFADoubleBuffer,    true,
                                                NSOpenGLPFADepthSize,       24,
                                                NSOpenGLPFAStencilSize,     8,
                                                0   };

    if (self.launch_parameters.windowed) {
    
        // Create a window on the display
        // Get the rect for the display to make a fullscreen window
        DTint x, y, width, height;
        HAL::display_rect (self.launch_parameters.display, x, y, width, height);

        DTint main_x, main_y, main_width, main_height;
        HAL::display_rect (0, main_x, main_y, main_width, main_height);
        
        NSRect mainDisplayRect;
        mainDisplayRect.origin.x = x + (width - _launch_parameters.resolution_width) * 0.5F;
        mainDisplayRect.origin.y = main_height - y - height + (height - _launch_parameters.resolution_height) * 0.5F;
        mainDisplayRect.size.width = _launch_parameters.resolution_width;
        mainDisplayRect.size.height = _launch_parameters.resolution_height;

        NSRect rect = [NSWindow frameRectForContentRect:mainDisplayRect styleMask:NSTitledWindowMask];
        NSWindow *windowedWindow = [[NSWindow alloc] initWithContentRect:rect styleMask:NSTitledWindowMask backing:NSBackingStoreBuffered defer:YES];
        
        // Center the window
        [windowedWindow setFrame:rect display:NO];
    
        // Set the window title
        NSString *appName = [[NSRunningApplication currentApplication] localizedName];
        [windowedWindow setTitle:appName];
        
        // Perform any other window configuration you desire:
        [windowedWindow setOpaque:YES];
        [windowedWindow setHidesOnDeactivate:NO];
        [windowedWindow setAcceptsMouseMovedEvents:YES];
        
        // Create a view with a double-buffered OpenGL context and attach it to the window:
        NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attrs];
         
        NSRect viewRect = NSMakeRect(0.0, 0.0, mainDisplayRect.size.width, mainDisplayRect.size.height);
        _opengl_view = [[GameOpenGLView alloc] initWithFrame:viewRect pixelFormat: pixelFormat];
        [windowedWindow setContentView: _opengl_view];
        
        [windowedWindow makeFirstResponder:_opengl_view];
        [windowedWindow setAcceptsMouseMovedEvents:YES];

        // Show the window:
        [windowedWindow makeKeyAndOrderFront:self];
        
        // Save the window
        self.window = windowedWindow;

        // Clear the screen
        [[_opengl_view openGLContext] makeCurrentContext];
        ::glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
        ::glClear(GL_COLOR_BUFFER_BIT);
        ::glSwapAPPLE();

    // Upscale mode. Recommended by Apple here:
    // https://developer.apple.com/library/mac/#documentation/graphicsimaging/conceptual/opengl-macprogguide/opengl_fullscreen/opengl_cgl.html
    } else {
        
        // Get the rect for the display to make a fullscreen window
        DTint x, y, width, height;
        HAL::display_rect (self.launch_parameters.display, x, y, width, height);

        DTint main_x, main_y, main_width, main_height;
        HAL::display_rect (0, main_x, main_y, main_width, main_height);
        
        NSRect mainDisplayRect;
        mainDisplayRect.origin.x = x;
        mainDisplayRect.origin.y = main_height - y - height;
        mainDisplayRect.size.width = width;
        mainDisplayRect.size.height = height;
        
        NSRect rect = [NSWindow contentRectForFrameRect:mainDisplayRect styleMask:NSBorderlessWindowMask];
        NSWindow *fullScreenWindow = [[NSWindow alloc] initWithContentRect: rect styleMask:NSBorderlessWindowMask backing:NSBackingStoreBuffered defer:YES];
        
        // Set the window level to be above the menu bar.:
        [fullScreenWindow setLevel:NSMainMenuWindowLevel+1];
        
        // Perform any other window configuration you desire:
        [fullScreenWindow setOpaque:YES];
        [fullScreenWindow setHidesOnDeactivate:NO];
        [fullScreenWindow setAcceptsMouseMovedEvents:YES];

        // Create a view with a double-buffered OpenGL context and attach it to the window:
        NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attrs];
         
        NSRect viewRect = NSMakeRect(0.0, 0.0, mainDisplayRect.size.width, mainDisplayRect.size.height);
        _opengl_view = [[GameOpenGLView alloc] initWithFrame:viewRect pixelFormat: pixelFormat];
        
        // Set the size of the backing store
        GLint dim[2] = {self.launch_parameters.resolution_width, self.launch_parameters.resolution_height};
        CGLContextObj ctx = (CGLContextObj) [[_opengl_view openGLContext] CGLContextObj];
        CGLSetParameter(ctx, kCGLCPSurfaceBackingSize, dim);
        CGLEnable (ctx, kCGLCESurfaceBackingSize);

        // Set the view
        [fullScreenWindow setContentView: _opengl_view];
        
        [fullScreenWindow makeFirstResponder:_opengl_view];
        [fullScreenWindow setAcceptsMouseMovedEvents:YES];

        // Show the window:
        [fullScreenWindow makeKeyAndOrderFront:self];

        // Save the window
        self.window = fullScreenWindow;
        
        // Clear the screen
        [[_opengl_view openGLContext] makeCurrentContext];
        ::glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
        ::glClear(GL_COLOR_BUFFER_BIT);
        ::glSwapAPPLE();

    }
    
    // Pass in arguments from advanced tab
    NSArray *arguments = [self.launch_parameters.command_line componentsSeparatedByString:@" "];
    std::vector<std::string> arguments_s;

    for (int i = 0; i < [arguments count]; ++i) {
        NSString *argument = [arguments objectAtIndex:i];
        arguments_s.push_back([argument UTF8String]);
    }

    DT3::GameMainThread::process_arguments(arguments_s);

    // Start main thread
    DT3::GameMainThread::start();
            
    // Screen is ready so fire these off
    DT3::GameMainThread::show_engine(self.launch_parameters.resolution_width, self.launch_parameters.resolution_height);

}

- (void) exit
{
    [NSApp performSelector:@selector(terminate:) withObject:nil afterDelay:0.0];
}

//==============================================================================
//==============================================================================

- (void)keyDown:(NSEvent *)event
{
    NSUInteger m = [event modifierFlags];
    
    DTuint modifiers =  ((m & NSShiftKeyMask) ? DeviceInput::MOD_LSHIFT | DeviceInput::MOD_RSHIFT : 0) |
                        ((m & NSControlKeyMask) ? DeviceInput::MOD_LCTRL | DeviceInput::MOD_RCTRL : 0) |
                        ((m & NSAlternateKeyMask) ? DeviceInput::MOD_LALT | DeviceInput::MOD_RALT : 0) |
                        ((m & NSCommandKeyMask) ? DeviceInput::MOD_LMETA | DeviceInput::MOD_RMETA : 0);
    DTushort key = [event keyCode];

    GameMainThread::key_down_event(modifiers, key);
}

- (void)keyUp:(NSEvent *)event
{
    NSUInteger m = [event modifierFlags];
    
    DTuint modifiers =  ((m & NSShiftKeyMask) ? DeviceInput::MOD_LSHIFT | DeviceInput::MOD_RSHIFT : 0) |
                        ((m & NSControlKeyMask) ? DeviceInput::MOD_LCTRL | DeviceInput::MOD_RCTRL : 0) |
                        ((m & NSAlternateKeyMask) ? DeviceInput::MOD_LALT | DeviceInput::MOD_RALT : 0) |
                        ((m & NSCommandKeyMask) ? DeviceInput::MOD_LMETA | DeviceInput::MOD_RMETA : 0);
    DTushort key = [event keyCode];

    GameMainThread::key_up_event(modifiers, key);
}

//==============================================================================
//==============================================================================

- (void) beginCaptureMouse
{
    ++(self.capture_mouse);
    
    if (self.capture_mouse > 0) {
        [NSCursor hide];
    }
}

- (void) endCaptureMouse
{
    --(self.capture_mouse);
    
    if (self.capture_mouse <= 0) {
        [NSCursor unhide];
    }

}

//==============================================================================
//==============================================================================

- (void)mouseDown:(NSEvent *)event
{
    if (self.capture_mouse <= 0) {
    
        NSPoint event_location = [event locationInWindow];
        event_location.x = event_location.x / _opengl_view.frame.size.width * _launch_parameters.resolution_width;
        event_location.y = (_opengl_view.frame.size.height - event_location.y) / _opengl_view.frame.size.height * _launch_parameters.resolution_height;

        _touch_event.touches[0].state = TouchEvent::STATE_PRESSED;
        _touch_event.touches[0].pos = Vector2(event_location.x, event_location.y);
        _touch_event.touches[0].previous_pos = Vector2(event_location.x,event_location.y);
        _touch_event.touches[0].first_pos = Vector2(event_location.x,event_location.y);
        _touch_event.touches[0].delta = DT3::Vector2(0.0F,0.0F);
        _touch_event.touches[0].velocity = DT3::Vector2(0.0F,0.0F);

        _touch_event.touches[0].timer.delta_time();

        LOG_MESSAGE << "mousePressEvent: " << event_location.x << "," << event_location.y;
        
    } else {
    
        NSRect bounds = CGRectMake(0, 0, _opengl_view.frame.size.width, _opengl_view.frame.size.height);
        bounds = [self.window convertRectToScreen:bounds];
        bounds.origin.y = NSMaxY([[NSScreen screens][0] frame]) - NSMaxY(bounds);
        CGPoint center = { bounds.origin.x + bounds.size.width * 0.5F, bounds.origin.y + bounds.size.height * 0.5F };

        _touch_event.touches[0].state = TouchEvent::STATE_PRESSED;
        _touch_event.touches[0].pos = DT3::Vector2(center.x,center.y);
        _touch_event.touches[0].previous_pos = DT3::Vector2(center.x,center.y);
        _touch_event.touches[0].first_pos = DT3::Vector2(center.x,center.y);
        _touch_event.touches[0].delta = DT3::Vector2(0.0F,0.0F);
        _touch_event.touches[0].velocity = DT3::Vector2(0.0F,0.0F);

        _touch_event.touches[0].timer.delta_time();

        LOG_MESSAGE << "mousePressEvent: Captured";
    
    }

    GameMainThread::touch_event(_touch_event);
}

- (void)mouseDragged:(NSEvent *)event
{
    if (self.capture_mouse <= 0) {
    
        NSPoint event_location = [event locationInWindow];
        event_location.x = event_location.x / _opengl_view.frame.size.width * _launch_parameters.resolution_width;
        event_location.y = (_opengl_view.frame.size.height - event_location.y) / _opengl_view.frame.size.height * _launch_parameters.resolution_height;

        _touch_event.touches[0].state = TouchEvent::STATE_DOWN;
        _touch_event.touches[0].previous_pos = _touch_event.touches[0].pos;
        _touch_event.touches[0].pos = Vector2(event_location.x,event_location.y);
        _touch_event.touches[0].delta = _touch_event.touches[0].pos - _touch_event.touches[0].previous_pos;
        _touch_event.touches[0].dt = _touch_event.touches[0].timer.delta_time();
        _touch_event.touches[0].velocity = _touch_event.touches[0].delta / _touch_event.touches[0].dt;

        LOG_MESSAGE << "mouseDragged: " << event_location.x << "," << event_location.y;

    } else {

        CGEventRef event = ::CGEventCreate(NULL);
        CGPoint cursor = ::CGEventGetLocation(event);
        ::CFRelease(event);
        
        NSRect bounds = CGRectMake(0, 0, _opengl_view.frame.size.width, _opengl_view.frame.size.height);
        bounds = [self.window convertRectToScreen:bounds];
        bounds.origin.y = NSMaxY([[NSScreen screens][0] frame]) - NSMaxY(bounds);
        CGPoint center = { bounds.origin.x + bounds.size.width * 0.5F, bounds.origin.y + bounds.size.height * 0.5F };

        _touch_event.touches[0].state = TouchEvent::STATE_DOWN;
        _touch_event.touches[0].previous_pos = DT3::Vector2(center.x,center.y);
        _touch_event.touches[0].pos = Vector2(cursor.x,cursor.y);
        _touch_event.touches[0].delta = _touch_event.touches[0].pos - _touch_event.touches[0].previous_pos;
        _touch_event.touches[0].dt = _touch_event.touches[0].timer.delta_time();
        _touch_event.touches[0].velocity = _touch_event.touches[0].delta / _touch_event.touches[0].dt;
        
        ::CGAssociateMouseAndMouseCursorPosition (0);
        ::CGWarpMouseCursorPosition (center);
        ::CGAssociateMouseAndMouseCursorPosition (1);

        LOG_MESSAGE << "mouseDragged: Captured " << _touch_event.touches[0].delta.x << "," << _touch_event.touches[0].delta.y;

    }

    GameMainThread::touch_event(_touch_event);
}

- (void)mouseMoved:(NSEvent *)event
{
    if (self.capture_mouse <= 0) {
        // Do nothing
        
    } else {

        CGEventRef event = ::CGEventCreate(NULL);
        CGPoint cursor = ::CGEventGetLocation(event);
        ::CFRelease(event);
        
        NSRect bounds = CGRectMake(0, 0, _opengl_view.frame.size.width, _opengl_view.frame.size.height);
        bounds = [self.window convertRectToScreen:bounds];
        bounds.origin.y = NSMaxY([[NSScreen screens][0] frame]) - NSMaxY(bounds);
        CGPoint center = { bounds.origin.x + bounds.size.width * 0.5F, bounds.origin.y + bounds.size.height * 0.5F };

        _touch_event.touches[0].state = TouchEvent::STATE_HOVER;
        _touch_event.touches[0].previous_pos = DT3::Vector2(center.x,center.y);
        _touch_event.touches[0].pos = Vector2(cursor.x,cursor.y);
        _touch_event.touches[0].delta = _touch_event.touches[0].pos - _touch_event.touches[0].previous_pos;
        _touch_event.touches[0].dt = _touch_event.touches[0].timer.delta_time();
        _touch_event.touches[0].velocity = _touch_event.touches[0].delta / _touch_event.touches[0].dt;
        
        ::CGAssociateMouseAndMouseCursorPosition (0);
        ::CGWarpMouseCursorPosition (center);
        ::CGAssociateMouseAndMouseCursorPosition (1);

        LOG_MESSAGE << "mouseMoveEvent: Captured " << _touch_event.touches[0].delta.x << "," << _touch_event.touches[0].delta.y;

        GameMainThread::touch_event(_touch_event);
        
    }

}

- (void)mouseUp:(NSEvent *)event
{
    if (self.capture_mouse <= 0) {
    
        NSPoint event_location = [event locationInWindow];
        event_location.x = event_location.x / _opengl_view.frame.size.width * _launch_parameters.resolution_width;
        event_location.y = (_opengl_view.frame.size.height - event_location.y) / _opengl_view.frame.size.height * _launch_parameters.resolution_height;

        _touch_event.touches[0].state = TouchEvent::STATE_RELEASED;
        _touch_event.touches[0].previous_pos = _touch_event.touches[0].pos;
        _touch_event.touches[0].pos = Vector2(event_location.x,event_location.y);
        _touch_event.touches[0].delta = _touch_event.touches[0].pos - _touch_event.touches[0].previous_pos;
        _touch_event.touches[0].dt = _touch_event.touches[0].timer.delta_time();
        _touch_event.touches[0].velocity = _touch_event.touches[0].delta / _touch_event.touches[0].dt;

        LOG_MESSAGE << "mouseReleaseEvent: " << event_location.x << "," << event_location.y;
        
    } else {
    
        CGEventRef event = ::CGEventCreate(NULL);
        CGPoint cursor = ::CGEventGetLocation(event);
        ::CFRelease(event);
        
        NSRect bounds = CGRectMake(0, 0, _opengl_view.frame.size.width, _opengl_view.frame.size.height);
        bounds = [self.window convertRectToScreen:bounds];
        bounds.origin.y = NSMaxY([[NSScreen screens][0] frame]) - NSMaxY(bounds);
        CGPoint center = { bounds.origin.x + bounds.size.width * 0.5F, bounds.origin.y + bounds.size.height * 0.5F };

        _touch_event.touches[0].state = TouchEvent::STATE_RELEASED;
        _touch_event.touches[0].previous_pos = DT3::Vector2(center.x,center.y);
        _touch_event.touches[0].pos = Vector2(cursor.x,cursor.y);
        _touch_event.touches[0].delta = _touch_event.touches[0].pos - _touch_event.touches[0].previous_pos;
        _touch_event.touches[0].dt = _touch_event.touches[0].timer.delta_time();
        _touch_event.touches[0].velocity = _touch_event.touches[0].delta / _touch_event.touches[0].dt;
        
        ::CGAssociateMouseAndMouseCursorPosition (0);
        ::CGWarpMouseCursorPosition (center);
        ::CGAssociateMouseAndMouseCursorPosition (1);

        LOG_MESSAGE << "mouseReleaseEvent: Captured " << _touch_event.touches[0].delta.x << "," << _touch_event.touches[0].delta.y;
    
    }
   
    GameMainThread::touch_event(_touch_event);

    _touch_event.touches[0].state = TouchEvent::STATE_NONE;
}

//==============================================================================
//==============================================================================

@end
