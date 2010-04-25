//
// game_terrain_layer_fwd.h
// Harmony
//

#ifndef HARMONY_GAME_TERRAIN_LAYER_FWD_H
#define HARMONY_GAME_TERRAIN_LAYER_FWD_H

#include <boost/shared_ptr.hpp>

namespace harmony {
	namespace game {
		class terrain_layer;
		typedef boost::shared_ptr<terrain_layer> terrain_layer_ref;
	}
}

#endif // HARMONY_GAME_TERRAIN_LAYER_FWD_H
