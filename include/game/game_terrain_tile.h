//
// game_terrain_tile.h
// Harmony
//

#ifndef HARMONY_GAME_TERRAIN_TILE_H
#define HARMONY_GAME_TERRAIN_TILE_H

#include "game_types.h"
#include "game_terrain_tile_fwd.h"
#include "gx_texture.h"

namespace harmony {
	namespace game {
		// A class of terrain tiles.
		class terrain_tile {
		public:
			terrain_tile(bool passable, const gx::texture_ref & texture,
				gl::ushort_t rotation = 0);
			~terrain_tile();
			
			// If the tile can be passed by ground or not.
			bool passable() const { return passable_; }
			
			gx::texture_ref texture() const;
			gl::ushort_t rotation() const;
			
		private:
			bool passable_;
			gx::texture_ref texture_;
			gl::ushort_t rotation_;
		};
	}
}

#endif // HARMONY_GAME_TERRAIN_TILE_H
