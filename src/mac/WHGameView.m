//
// WHGameView.m
// Harmony
//

#import "WHGameView.h"

#include "gx_interface.h"

NSString * const WHGameNeededForGameViewNotification = @"WHGameNeededForGameViewNotification";

@implementation WHGameView

@synthesize game = game_;

// Parameter for the NSOpenGLCPSwapInterval context property.
static const GLint swapBufferUsesVerticalSync = 1;

// Rendering callback for the display link.
static CVReturn WHRender(CVDisplayLinkRef displayLink,
		const CVTimeStamp * now, const CVTimeStamp * when,
		CVOptionFlags flagsIn, CVOptionFlags flagsOut,
		void * view) {
	(void)displayLink;
	(void)now;
	(void)when;
	(void)flagsIn;
	(void)flagsOut;
	
	// The seperate thread that the display link uses requires an autorelease pool.
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	// Get the host object.
	WHGameView * self = (WHGameView *)view;
	
	if ([self lockFocusIfCanDraw]) {
		// Obtain and lock the OpenGL context.
		NSOpenGLContext * context = [self openGLContext];
		CGLLockContext([context CGLContextObj]);
		
		// Get the game object.
		hgame_ref game = [self game];
		
		// For now, the game engine will be updated by the graphics callback.
		uint64_t elapsed_host = when->hostTime - self->lastUpdateTime_;
		float elapsed = (float)(elapsed_host / self->clockFrequency_);
		hgame_step(game, elapsed);
		self->lastUpdateTime_ = when->hostTime;
		
		// Perform the rendering.
		hgx_render(game, elapsed);
		[context flushBuffer];
		
		// Unlock the OpenGL context.
		CGLUnlockContext([context CGLContextObj]);
		[self unlockFocus];
	}
	
	[pool drain];
	return kCVReturnSuccess;
}

- (void)prepareOpenGL {
	// In case the superclass needs to do anything.
	[super prepareOpenGL];
	
	// Use vertical synchronization.
	[[self openGLContext] setValues:&swapBufferUsesVerticalSync forParameter:NSOpenGLCPSwapInterval];
	
	// Initialize the display link.
	CVDisplayLinkCreateWithActiveCGDisplays(&displayLink_);
	CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(
		displayLink_,
		[[self openGLContext] CGLContextObj],
		[[self pixelFormat] CGLPixelFormatObj]
	);
	
	// Hook up the display link.
	CVDisplayLinkSetOutputCallback(displayLink_, (CVDisplayLinkOutputCallback)&WHRender, self);
	
	// Begin rendering.
	CVDisplayLinkStart(displayLink_);
	
	// Remember the host clock frequency of the display link (in milliseconds).
	clockFrequency_ = CVGetHostClockFrequency(displayLink_) / 1000.0f;
	
	// Get the initial time.
	lastUpdateTime_ = CVGetCurrentHostTime();
}

- (void)reshape {
	NSSize size = [self bounds].size;
	
	// Tell the engine that our view bounds changed.
	if ([self lockFocusIfCanDraw]) {
		hgx_reshape([self game], size.width, size.height);
		[self unlockFocus];
	}
}

- (void)viewDidMoveToWindow {
	[super viewDidMoveToWindow];
	[[self window] setAcceptsMouseMovedEvents:YES];
	[[self window] makeFirstResponder:self];
}

- (BOOL)resignFirstResponder {
	return NO;
}

- (void)mousePositionDidChange:(NSEvent *)event {
	// Get the point, in view coordinates.
	NSPoint point = [self convertPoint:[event locationInWindow] fromView:nil];
	
	// Get the current size of the view.
	NSSize size = [self bounds].size;
	
	// Invert the y coordinate, to account for the view coordinate system.
	point.y = size.height - point.y;
	
	// Clamp the point to the desired range.
	if (point.x < 0.0f) point.x = 0.0f;
	if (point.y < 0.0f) point.y = 0.0f;
	if (point.x > size.width) point.x = size.width;
	if (point.y > size.height) point.y = size.height;
	
	// Tell the engine about the new mouse position.
	hgame_mouse_moved([self game], (unsigned)(point.x), (unsigned)(point.y));
}

- (void)pressedMouseButtonsDidChange {
	// Get the current pressed mouse buttons.
	NSUInteger buttons = [NSEvent pressedMouseButtons];
	
	// Get the game object.
	hgame_ref game = [self game];
	
	// Update all the mouse button states.
	hgame_input_state_changed(game, hgame_input_mouse1, !!(buttons & (1 << 0)));
	hgame_input_state_changed(game, hgame_input_mouse2, !!(buttons & (1 << 1)));
	hgame_input_state_changed(game, hgame_input_mouse3, !!(buttons & (1 << 2)));
	hgame_input_state_changed(game, hgame_input_mouse4, !!(buttons & (1 << 3)));
	hgame_input_state_changed(game, hgame_input_mouse5, !!(buttons & (1 << 4)));
}

- (void)mouseDown:(NSEvent *)event {
	[self mousePositionDidChange:event];
	[self pressedMouseButtonsDidChange];
}

- (void)mouseDragged:(NSEvent *)event {
	[self mousePositionDidChange:event];
}

- (void)mouseUp:(NSEvent *)event {
	[self mousePositionDidChange:event];
	[self pressedMouseButtonsDidChange];
}

- (void)rightMouseDown:(NSEvent *)event {
	[self mousePositionDidChange:event];
	[self pressedMouseButtonsDidChange];
}

- (void)rightMouseDragged:(NSEvent *)event {
	[self mousePositionDidChange:event];
}

- (void)rightMouseUp:(NSEvent *)event {
	[self mousePositionDidChange:event];
	[self pressedMouseButtonsDidChange];
}

- (void)otherMouseDown:(NSEvent *)event {
	[self mousePositionDidChange:event];
	[self pressedMouseButtonsDidChange];
}

- (void)otherMouseDragged:(NSEvent *)event {
	[self mousePositionDidChange:event];
}

- (void)otherMouseUp:(NSEvent *)event {
	[self mousePositionDidChange:event];
	[self pressedMouseButtonsDidChange];
}

- (void)mouseMoved:(NSEvent *)event {
	[self mousePositionDidChange:event];
}

- (hgame_ref)game {
	// Lazily load the game object if needed.
	if (!game_)
		[[NSNotificationCenter defaultCenter] postNotificationName:WHGameNeededForGameViewNotification object:self];
	
	return game_;
}

- (void)dealloc {
	CVDisplayLinkRelease(displayLink_);
	[super dealloc];
}

- (void)finalize {
	CVDisplayLinkRelease(displayLink_);
	[super finalize];
}

@end
