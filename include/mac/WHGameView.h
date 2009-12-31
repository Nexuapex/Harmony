//
// WHGameView.h
// Harmony
//

#import <Cocoa/Cocoa.h>
#import <CoreVideo/CoreVideo.h>

#include "game_interface.h"

@interface WHGameView : NSOpenGLView {
	CVDisplayLinkRef displayLink_;
	hgame_ref game_;
	double clockFrequency_;
	uint64_t lastUpdateTime_;
}

@property (assign, nonatomic) hgame_ref game;

@end

extern NSString * const WHGameNeededForGameViewNotification;
