//==============================================================================
///	
///	File: AppDelegate.m
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "AppDelegate.h"
#include "TouchEvent.hpp"
#include "GameMainThread.hpp"
#include "System.hpp"
#include "ConsoleStream.hpp"
#include "Analytics.hpp"
#include "Globals.hpp"
#include "SystemCallbacks.hpp"
#include "Matrix.hpp"

#include "DeviceInput.hpp"
#include "DeviceMusic.hpp"
#include "DeviceAudio.hpp"

#import <sys/utsname.h>

using namespace DT3;

//==============================================================================
//==============================================================================

#define DT3_RUN_IPHONE4_AT_HALF_RES 1

//==============================================================================
//==============================================================================

AppViewController*	gController;
UIWindow*			gWindow;
EAGLView*			gGLView;

CGRect				gRect;
float               gScale = 1.0F;

UITouch*			gTouches[TouchEvent::MAX_NUM_TOUCHES] = { NULL };
TouchEvent          gTouchEvent;
    
//==============================================================================
// Define hooks from the engine
//==============================================================================

void screenInited (void)
{
    // In order to render with OpenGL from another thread, this has
    // to be called in the thread. Conveniently, this callback will
    // be called when the screen has been opened.
    [gGLView makeCurrentContext];
}

void screenClosed (void)
{
    // Screen is invalid so clear the current context
    [gGLView clearCurrentContext];
}

void screenChanged (DTuint width, DTuint height)
{
    // In order to render with OpenGL from another thread, this has
    // to be called in the thread. Conveniently, this callback will
    // be called when the screen has been opened.
    [gGLView makeCurrentContext];
}

void screenSwap (void)
{
    [gGLView swapBuffers];
}

//==============================================================================
// View Controller for app
//==============================================================================

@implementation AppViewController

- (id)init
{
    self = [super init];
    if (self) {		
		self.view = gGLView;
		self.view.autoresizingMask = (UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight);
		self.view.clipsToBounds = YES;
                
        [self setWantsFullScreenLayout:YES];
    }
    
    return self;
}

- (void)dealloc {	
	[super dealloc];
}

//==============================================================================
//==============================================================================

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{

    switch (interfaceOrientation) {
        case UIInterfaceOrientationLandscapeLeft:
        case UIInterfaceOrientationLandscapeRight:
            return YES;
            
        default:
            return NO;
    
    }

}

-(void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
    if (!System::getInputManager())
        return;
    
    switch (toInterfaceOrientation) {
        case UIInterfaceOrientationLandscapeLeft:   // Home button on left
            break;
            
        case UIInterfaceOrientationLandscapeRight:  // Home button on right
            break;

        case UIInterfaceOrientationPortrait:
            break;
            
        case UIInterfaceOrientationPortraitUpsideDown:
            break;
            
        default:
            break;
    }
    
}

//==============================================================================
//==============================================================================

- (NSUInteger)supportedInterfaceOrientations {
    return UIInterfaceOrientationMaskLandscapeLeft | UIInterfaceOrientationMaskLandscapeRight;
}

- (BOOL) shouldAutorotate {
    return YES;
}

@end

//==============================================================================
// App delegate
//==============================================================================

@implementation AppDelegate

- (id)init
{
    self = [super init];
    if (self) {		
        motionManager = [[CMMotionManager alloc] init];
        motionQueue = [[NSOperationQueue alloc] init];
    }
    
    return self;
}

- (void)dealloc {	
	[super dealloc];
    
    [motionQueue release];
    [motionManager release];
}

- (void) touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event
{	

	NSArray *all_touches = [touches allObjects];
	
    int touch_count = [all_touches count];
	for (int i = 0; i < touch_count; ++i) {
		UITouch*	touch = [all_touches objectAtIndex:i];
		CGPoint		location = [touch locationInView:gGLView];
		
		// Figure out index of touches
		for (int j = 0; j < TouchEvent::MAX_NUM_TOUCHES; ++j) {
			if (gTouches[j] == NULL) {
                LOG_MESSAGE << "touchesBegan " << j;
            
				gTouches[j] = touch;
                
                gTouchEvent.touches[j].data1 = touches;
                gTouchEvent.touches[j].data2 = event;
     
                gTouchEvent.touches[j].state = TouchEvent::STATE_PRESSED;
                gTouchEvent.touches[j].pos = Vector2(location.x*gScale,location.y*gScale);
                gTouchEvent.touches[j].previous_pos = Vector2(location.x*gScale,location.y*gScale);
                gTouchEvent.touches[j].first_pos = Vector2(location.x*gScale,location.y*gScale);
                gTouchEvent.touches[j].delta = Vector2(0.0F,0.0F);
                gTouchEvent.touches[j].dt = 0.0F;
                gTouchEvent.touches[j].velocity = Vector2(0.0F,0.0F);
                
                gTouchEvent.touches[j].timer.getDeltaTime();
   
                GameMainThread::touchEvent(gTouchEvent);

				break;
			}
		}
	}
	
}

- (void) touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event
{
	NSArray *all_touches = [touches allObjects];
	
    int touch_count = [all_touches count];
	for (int i = 0; i < touch_count; ++i) {
		UITouch*	touch = [all_touches objectAtIndex:i];
		CGPoint		location = [touch locationInView:gGLView];

		// Figure out index of touches
		for (int j = 0; j < TouchEvent::MAX_NUM_TOUCHES; ++j) {
			if (gTouches[j] == touch) {
                LOG_MESSAGE << "touchesMoved " << j;
                
                gTouchEvent.touches[j].data1 = touches;
                gTouchEvent.touches[j].data2 = event;

                gTouchEvent.touches[j].state = TouchEvent::STATE_DOWN;
                gTouchEvent.touches[j].previous_pos = gTouchEvent.touches[j].pos;
                gTouchEvent.touches[j].pos = Vector2(location.x*gScale,location.y*gScale);
                gTouchEvent.touches[j].delta = gTouchEvent.touches[j].pos - gTouchEvent.touches[j].previous_pos;
                gTouchEvent.touches[j].dt = gTouchEvent.touches[j].timer.getDeltaTime();
                gTouchEvent.touches[j].velocity = gTouchEvent.touches[j].delta / gTouchEvent.touches[j].dt;

                GameMainThread::touchEvent(gTouchEvent);

				break;
			}
		}
	}
}

- (void) touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event
{
	NSArray *all_touches = [touches allObjects];

    int touch_count = [all_touches count];
	for (int i = 0; i < touch_count; ++i) {
		UITouch*	touch = [all_touches objectAtIndex:i];
		CGPoint		location = [touch locationInView:gGLView];

		// Figure out index of touches
		for (int j = 0; j < TouchEvent::MAX_NUM_TOUCHES; ++j) {
			if (gTouches[j] == touch) {
                LOG_MESSAGE << "touchesEnded " << j;

				gTouches[j] = NULL;
				
                gTouchEvent.touches[j].data1 = touches;
                gTouchEvent.touches[j].data2 = event;

                gTouchEvent.touches[j].state = TouchEvent::STATE_RELEASED;
                gTouchEvent.touches[j].previous_pos = gTouchEvent.touches[j].pos;
                gTouchEvent.touches[j].pos = Vector2(location.x*gScale,location.y*gScale);
                gTouchEvent.touches[j].delta = gTouchEvent.touches[j].pos - gTouchEvent.touches[j].previous_pos;
                gTouchEvent.touches[j].dt = gTouchEvent.touches[j].timer.getDeltaTime();
                gTouchEvent.touches[j].velocity = gTouchEvent.touches[j].delta / gTouchEvent.touches[j].dt;

                GameMainThread::touchEvent(gTouchEvent);

                gTouchEvent.touches[j].state = TouchEvent::STATE_NONE;

				break;
			}
		}
	}
}

//==============================================================================
// Rotates the sensor data so that it matches the UI orientation. ie.
// +Y will always be "up" according to the UI.
//==============================================================================

- (void) rotateSensorData:(Vector3*)sensor toOrientation:(UIInterfaceOrientation) orientation
{
    Matrix3 rot(Matrix3::identity());

    switch (orientation) {
        case UIInterfaceOrientationLandscapeLeft:   // Home button on left
            rot = Matrix3 ( 0.0F,   1.0F,   0.0F,
                            -1.0F,  0.0F,  0.0F,
                            0.0F,   0.0F,   1.0F );
            break;
            
        case UIInterfaceOrientationLandscapeRight:   // Home button on right
            rot = Matrix3 ( 0.0F,   -1.0F,   0.0F,
                            1.0F,   0.0F,  0.0F,
                            0.0F,   0.0F,   1.0F );
            break;

            
        case UIInterfaceOrientationPortraitUpsideDown:
            rot = Matrix3 ( -1.0F,  0.0F,   0.0F,
                            0.0F,   -1.0F,  0.0F,
                            0.0F,   0.0F,   1.0F );
            break;
            
        case UIInterfaceOrientationPortrait:
            rot = Matrix3 ( 1.0F,   0.0F,   0.0F,
                            0.0F,   1.0F,   0.0F,
                            0.0F,   0.0F,   1.0F );
            break;
    }

    *sensor = rot * (*sensor);
}

//==============================================================================
//==============================================================================

-(BOOL)startAppWithOptions:(NSDictionary*)launchOptions application:(UIApplication*)application
{
    [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];  
    
    //
    // Start engine
    //

    // Initialize the engine. Do it before "start" is called on the main loop. This will run it synchronously
    GameMainThread::initializeEngine();
    
    // Register callbacks
    SystemCallbacks::getScreenInitedCB().add(makeCallback(screenInited));
    SystemCallbacks::getScreenClosedCB().add(makeCallback(screenClosed));
    SystemCallbacks::getScreenSwapCB().add(makeCallback(screenSwap));
    SystemCallbacks::getScreenChangedCB().add(makeCallback(screenChanged));

    //
    // Initialize Analytics
    //
    
    NSString *model = [[UIDevice currentDevice] model]; 
    NSString *osversion = [[UIDevice currentDevice] systemVersion]; 

    // Pirated Flag
	FilePath piracy_check("{APPDIR}/_CodeSignature/CodeResources");
    DTboolean pirated = !piracy_check.exists();
    
    // Initialize Analytics
    Analytics::initialize ( [model UTF8String], [osversion UTF8String], pirated);
    Analytics::recordEvent (ANALYTICS_APP, "Started");

    //
    // Build Screen
    //
    
    // Small Screen
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        Globals::setGlobal("SYS_SMALL_SCREEN", "1", Globals::VOLATILE);
    } else {
        Globals::setGlobal("SYS_SMALL_SCREEN", "0", Globals::VOLATILE);
    }

    // Change resolution for retina
    if([[UIScreen mainScreen] respondsToSelector:@selector(scale)])
        gScale = [UIScreen mainScreen].scale;
    
#if DT3_RUN_IPHONE4_AT_HALF_RES
    // The iPhone 4 is a pretty fill rate limited device so lets turn off Retina support.

    struct utsname systemInfo;
    ::uname(&systemInfo);
    
    if (::strcmp(systemInfo.machine, "iPhone3,1") == 0)
        gScale = 1.0F;
#endif
    
	gRect = [UIScreen mainScreen].applicationFrame;
    CGRect gRectTransposed = CGRectMake(0, 0, gRect.size.height, gRect.size.width);
        
    //
    // Build gl view
    //
    	
    gGLView = [[EAGLView alloc] initWithFrame:gRectTransposed];

    if (gScale != 1.0F)
        gGLView.contentScaleFactor = gScale;
        
    //
    // Build window hierarchy
    //
    
	gController = [[AppViewController alloc] init];
	gWindow = [[UIWindow alloc] initWithFrame:gRect];
    gWindow.rootViewController = gController; 

	[gWindow addSubview:gGLView];
    [gWindow makeKeyAndVisible];
            
	return YES;
}

//2.0 - Application Launching Method
- (void)applicationDidFinishLaunching:(UIApplication*)application
{
	[self startAppWithOptions:nil application:application];
}

//3.0 - Application Launching Method
- (BOOL)application:(UIApplication*)application didFinishLaunchingWithOptions: (NSDictionary*)launchOptions
{
	return [self startAppWithOptions:launchOptions application:application];
}

//==============================================================================
//==============================================================================

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Clear touches
    for (int j = 0; j < TouchEvent::MAX_NUM_TOUCHES; ++j)
        gTouches[j] = NULL;
    gTouchEvent.clear();

    // Analytics
    Analytics::recordEvent (ANALYTICS_APP, "Resumed");
    
    //
    // Startup audio
    //
    
	if (System::getMusicRenderer())	System::getMusicRenderer()->restartAudio();
	if (System::getAudioRenderer())	System::getAudioRenderer()->restartAudio();

    //
    // Start Main Loop
    //
    
    GameMainThread::start();
    GameMainThread::showEngine(gRect.size.height*gScale, gRect.size.width*gScale);
    
    
    //
    // Motion manager
    // 
    
    motionManager.accelerometerUpdateInterval = 1.0F/100.0F;
    [motionManager startAccelerometerUpdatesToQueue: motionQueue withHandler: 
        ^( CMAccelerometerData* data, NSError* error) {
            Vector3 s(data.acceleration.x, data.acceleration.y, data.acceleration.z);
            [self rotateSensorData:&s toOrientation:gController.interfaceOrientation];
            GameMainThread::doAccelerometer(s);
        }
    ];

    motionManager.gyroUpdateInterval = 1.0F/100.0F;
    [motionManager startGyroUpdatesToQueue: motionQueue withHandler: 
        ^( CMGyroData* data, NSError* error) {
            Vector3 s(data.rotationRate.x, data.rotationRate.y, data.rotationRate.z);
            [self rotateSensorData:&s toOrientation:gController.interfaceOrientation];
            GameMainThread::doGyro(s);
        }
    ];

    motionManager.magnetometerUpdateInterval = 1.0F/100.0F;
    [motionManager startMagnetometerUpdatesToQueue: motionQueue withHandler:
        ^( CMMagnetometerData* data, NSError* error) {
            Vector3 s(data.magneticField.x, data.magneticField.y, data.magneticField.z);
            [self rotateSensorData:&s toOrientation:gController.interfaceOrientation];
            GameMainThread::doMagnetometer(s);
        }
    ];

}

//==============================================================================
//==============================================================================

- (void) applicationWillResignActive:(UIApplication*)application
{

    GameMainThread::stop();

    //
    // Turn off audio
    //

	if (System::getMusicRenderer())	System::getMusicRenderer()->shutdownAudio();
	if (System::getAudioRenderer())	System::getAudioRenderer()->shutdownAudio();

    [motionManager stopAccelerometerUpdates];
    [motionManager stopGyroUpdates];
    [motionManager stopMagnetometerUpdates];

    Analytics::recordEvent (ANALYTICS_APP, "Suspended");

    //
    // Hide the engine
    //

    GameMainThread::hideEngine();
}
//==============================================================================
//==============================================================================

- (void) applicationWillTerminate:(UIApplication*)application
{     
    
    // Analytics
    Analytics::recordEvent (ANALYTICS_APP, "Stopped");
    
    //
    // Destroy the engine
    //
    
    Analytics::destroy();

    GameMainThread::destroyEngine();
}

//==============================================================================
//==============================================================================

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application
{
	NSLog(@"**************************************************************");
	NSLog(@"*                                                            *");
	NSLog(@"*                   Low memory warning!!!                    *");
	NSLog(@"*                                                            *");
	NSLog(@"**************************************************************");
    

}

//==============================================================================
//==============================================================================

@end
