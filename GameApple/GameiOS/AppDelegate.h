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

#import "EAGLView.h"
#import <CoreMotion/CoreMotion.h>

//==============================================================================
//==============================================================================

@interface AppViewController : UIViewController 
{
    UIInterfaceOrientation orientationBeforeDashboard;
}

@end

//==============================================================================
//==============================================================================

@interface AppDelegate : NSObject <UIApplicationDelegate,UIAccelerometerDelegate>
{	
    CMMotionManager     *motionManager;
    NSOperationQueue    *motionQueue;
}

@end

//==============================================================================
//==============================================================================
