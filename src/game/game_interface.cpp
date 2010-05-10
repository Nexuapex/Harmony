//
// game_interface.cpp
// Harmony
//

#include "game_interface.h"
#include "game.h"
#include "ivec2.h"

using namespace harmony;

hgame_ref hgame_create() {
	return reinterpret_cast<hgame_ref>(new game::engine);
}

void hgame_step(hgame_ref game, float elapsed) {
	game::engine & self = *reinterpret_cast<game::engine *>(game);
	
	if (elapsed > 100.0f) elapsed = 100.0f;
	
	self.step(static_cast<game::elapsed_t>(elapsed));
}

void hgame_input_state_changed(hgame_ref game, hgame_input_t state, int new_value) {
	game::engine & self = *reinterpret_cast<game::engine *>(game);
	
	if (state >= hgame_input_mouse1 && state <= hgame_input_mouse5)
		self.input_state_changed(state, !!new_value);
}

void hgame_mouse_moved(hgame_ref game, unsigned x, unsigned y) {
	game::engine & self = *reinterpret_cast<game::engine *>(game);
	
	self.set_mouse_position(ivec2(x, y));
}
