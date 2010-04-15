//
// game_terrain_tile.h
// Harmony
//

#ifndef HARMONY_GAME_TERRAIN_TILE_H
#define HARMONY_GAME_TERRAIN_TILE_H

#include <boost/shared_ptr.hpp>

#include "game_types.h"
#include "gx_texture.h"

namespace harmony {
	namespace game {
		// A class of terrain tiles.
		class terrain_tile {
		public:
			terrain_tile(const gx::texture_ref & texture, gl::ushort_t rotation = 0);
			~terrain_tile();
			
			gx::texture_ref texture() const;
			gl::ushort_t rotation() const;
			
		private:
			gx::texture_ref texture_;
			gl::ushort_t rotation_;
		};
		
		typedef boost::shared_ptr<terrain_tile> terrain_tile_ref;
	}
}

#endif // HARMONY_GAME_TERRAIN_TILE_H
