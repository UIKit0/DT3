//==============================================================================
///	
///	File: EAGLView.m
///	Author:			Tod Baudais
///					Copyright (C) 2000-2008. All backs reserved.
///	
///	Date Created:	3/23/2008
///	Changes:		-none-
///	
//==============================================================================

#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGLDrawable.h>

#import "EAGLView.h"
#import "AppDelegate.h"

//==============================================================================
//==============================================================================

@implementation EAGLView

//==============================================================================
//==============================================================================

+ (Class) layerClass
{
	return [CAEAGLLayer class];
}

//==============================================================================
//==============================================================================

- (id) initWithFrame:(CGRect)frame
{
	if((self = [super initWithFrame:frame])) {
		[self setMultipleTouchEnabled:YES];
        self.exclusiveTouch = YES;
        self.userInteractionEnabled = YES;

		// Get the layer
		CAEAGLLayer *eaglLayer = (CAEAGLLayer*) self.layer;
		
		eaglLayer.opaque = YES;
		eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
									   [NSNumber numberWithBool:FALSE],		kEAGLDrawablePropertyRetainedBacking,
									   kEAGLColorFormatRGBA8,				kEAGLDrawablePropertyColorFormat,
									   nil];
		
		context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
		
		if(!context || ![EAGLContext setCurrentContext:context] || ![self createFramebuffer]) {
			[self release];
			return nil;
		}
				
	}
	
	return self;
}


- (void)layoutSubviews
{
	[EAGLContext setCurrentContext:context];
	[self destroyFramebuffer];
	[self createFramebuffer];
}


- (BOOL)createFramebuffer
{
	glGenFramebuffersOES(1, &viewFramebuffer);
	glGenRenderbuffersOES(1, &viewRenderbuffer);
	
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, viewFramebuffer);
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
	[context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:(id<EAGLDrawable>)self.layer];
	glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, viewRenderbuffer);
	
	glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth);
	glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight);

	glGenRenderbuffersOES(1, &depthRenderbuffer);
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, depthRenderbuffer);
	glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_DEPTH24_STENCIL8_OES, backingWidth, backingHeight);
	glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, depthRenderbuffer);
	glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_STENCIL_ATTACHMENT_OES, GL_RENDERBUFFER_OES, depthRenderbuffer);
	
	if(glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES) != GL_FRAMEBUFFER_COMPLETE_OES) {
		NSLog(@"failed to make complete framebuffer object %x", glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES));
		return NO;
	}
	
	[EAGLContext setCurrentContext:context];		
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, viewFramebuffer);
	
	return YES;
}


- (void)destroyFramebuffer
{
	glDeleteFramebuffersOES(1, &viewFramebuffer);
	viewFramebuffer = 0;
	glDeleteRenderbuffersOES(1, &viewRenderbuffer);
	viewRenderbuffer = 0;
	
	if(depthRenderbuffer) {
		glDeleteRenderbuffersOES(1, &depthRenderbuffer);
		depthRenderbuffer = 0;
	}
}

//==============================================================================
//==============================================================================

- (void)dealloc
{	
	
	if([EAGLContext currentContext] == context) {
		[EAGLContext setCurrentContext:nil];
	}
	
	[context release];
	context = nil;
	
	[super dealloc];
}

//==============================================================================
//==============================================================================

- (void) makeCurrentContext
{
	[EAGLContext setCurrentContext:context];
}

- (void) clearCurrentContext
{
	[EAGLContext setCurrentContext:nil];
}

//==============================================================================
//==============================================================================

- (void) swapBuffers
{	
	// Make sure that you are drawing to the current context
	[context presentRenderbuffer:GL_RENDERBUFFER_OES];
	
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, viewFramebuffer);
    
    //GLenum attachments[] = { GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT };
    //glDiscardFramebufferEXT(GL_FRAMEBUFFER_OES, ARRAY_SIZE(attachments), attachments);

}

//==============================================================================
//==============================================================================

- (void) touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event
{
	[(AppDelegate*)[[UIApplication sharedApplication] delegate] touchesBegan:touches withEvent:event];
}

- (void) touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event
{
	[(AppDelegate*)[[UIApplication sharedApplication] delegate] touchesMoved:touches withEvent:event];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
	[(AppDelegate*)[[UIApplication sharedApplication] delegate] touchesEnded:touches withEvent:event];
}

- (void) touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event
{
	[(AppDelegate*)[[UIApplication sharedApplication] delegate] touchesEnded:touches withEvent:event];
}

//==============================================================================
//==============================================================================

@end

//==============================================================================
//==============================================================================

