//
// WHApplicationDelegate.h
// Harmony
//

#import <Cocoa/Cocoa.h>

@interface WHApplicationDelegate : NSObject <NSApplicationDelegate> {
	NSWindow * window_;
}

@property (assign, nonatomic) IBOutlet NSWindow * window;

@end
