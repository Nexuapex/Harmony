//
// game_types.h
// Harmony
//

#ifndef HARMONY_GAME_TYPES_H
#define HARMONY_GAME_TYPES_H

#include <cstddef>

#include "types.h"
#include "vec2.h"
#include "ivec2.h"
#include "irect.h"

namespace harmony {
	namespace game {
		using std::size_t;
		
		// Time intervals are measured in milliseconds.
		typedef float elapsed_t;
		
		// Angles are measured in degrees.
		typedef float angle_t;
	}
}

#endif // HARMONY_GAME_TYPES_H
