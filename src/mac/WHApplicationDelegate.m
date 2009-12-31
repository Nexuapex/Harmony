//
// WHApplicationDelegate.m
// Harmony
//

#import "WHApplicationDelegate.h"

@implementation WHApplicationDelegate

@synthesize window = window_;

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
	(void)notification;
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)app {
	(void)app;
	return YES;
}

@end
