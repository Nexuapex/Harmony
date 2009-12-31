//
// game_interface.h
// Harmony
//

#ifndef HARMONY_GAME_INTERFACE_H
#define HARMONY_GAME_INTERFACE_H

#include "glue.h"

typedef void * hgame_ref;

typedef enum {
	hgame_input_mouse1 = 101,
	hgame_input_mouse2 = 102,
	hgame_input_mouse3 = 103,
	hgame_input_mouse4 = 104,
	hgame_input_mouse5 = 105
} hgame_input_t;

#ifdef __cplusplus
namespace harmony {
	namespace game {
		typedef hgame_input_t bool_state_t;
	}
}
#endif

// Create the game engine object. Needs an OpenGL context activated.
HARMONY_API hgame_ref hgame_create();

// Advance the game time. The parameter is in milliseconds.
HARMONY_API void hgame_step(hgame_ref game, float elapsed);

// Let the game know that an input state has changed.
HARMONY_API void hgame_input_state_changed(hgame_ref game, hgame_input_t state,
	int new_value);

// Let the game know that the mouse has moved.
HARMONY_API void hgame_mouse_moved(hgame_ref game, unsigned x, unsigned y);

#endif // HARMONY_GAME_INTERFACE_H
