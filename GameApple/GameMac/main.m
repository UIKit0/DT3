//
//  main.m
//  GameMac
//
//  Created by Tod Baudais on 2013-08-02.
//  Copyright (c) 2013 Smells Like Donkey Software Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#if DT3_OS == DT3_MACOSX
#include <AppKit/NSRunningApplication.h>
#endif

int main(int argc, char *argv[])
{
    //
    // Bring app to foreground so it plays nicely with the editor
    //
    
    ProcessSerialNumber psn;
    OSErr err;
    
    err = GetCurrentProcess( &psn );
    if (err == noErr)
        SetFrontProcess( &psn );


    return NSApplicationMain(argc, (const char **)argv);
}
