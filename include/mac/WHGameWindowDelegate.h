//
// WHGameWindowDelegate.h
// Harmony
//

#import <Cocoa/Cocoa.h>

#include "game_interface.h"

@class WHGameView;

@interface WHGameWindowDelegate : NSObject <NSWindowDelegate> {
	NSWindow * window_;
	WHGameView * gameView_;
	hgame_ref game_;
}

@property (assign, nonatomic) IBOutlet NSWindow * window;
@property (assign, nonatomic) IBOutlet WHGameView * gameView;
@property (assign, nonatomic) hgame_ref game;

@end
