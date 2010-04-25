//
// game_terrain_tile_fwd.h
// Harmony
//

#ifndef HARMONY_GAME_TERRAIN_TILE_FWD_H
#define HARMONY_GAME_TERRAIN_TILE_FWD_H

#include <boost/shared_ptr.hpp>

namespace harmony {
	namespace game {
		class terrain_tile;
		typedef boost::shared_ptr<terrain_tile> terrain_tile_ref;
	}
}

#endif // HARMONY_GAME_TERRAIN_TILE_FWD_H
