//
// WHGameWindowDelegate.m
// Harmony
//

#import "WHGameWindowDelegate.h"
#import "WHGameView.h"

@implementation WHGameWindowDelegate

@synthesize window = window_;
@synthesize gameView = gameView_;
@synthesize game = game_;

- (void)awakeFromNib {
	[[NSNotificationCenter defaultCenter] addObserver:self
											 selector:@selector(gameNeededForGameView:)
												 name:WHGameNeededForGameViewNotification
											   object:nil];
}

- (void)gameNeededForGameView:(NSNotification *)notification {
	if ([notification object] == gameView_) {
		if (!game_) {
			game_ = hgame_create();
		}
		
		[gameView_ setGame:game_];
	}
}

- (void)windowWillClose:(NSNotification *)notification {
	(void)notification;
	[[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
