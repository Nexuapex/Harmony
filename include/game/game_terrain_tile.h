//
// game_terrain_tile.h
// Harmony
//

#ifndef HARMONY_GAME_TERRAIN_TILE_H
#define HARMONY_GAME_TERRAIN_TILE_H

#include <boost/shared_ptr.hpp>

#include "game_types.h"
#include "gl_texture.h"

namespace harmony {
	namespace game {
		// A class of terrain tiles.
		class terrain_tile {
		public:
			terrain_tile(const gl::texture_ref & texture, gl::int_t rotation = 0);
			~terrain_tile();
			
			gl::texture & texture() const;
			gl::int_t rotation() const;
			const gl::float_t * tex_coords() const;
			
		private:
			gl::texture_ref texture_;
			gl::int_t rotation_;
			gl::float_t tex_coords_[4][2];
		};
		
		typedef boost::shared_ptr<terrain_tile> terrain_tile_ref;
	}
}

#endif // HARMONY_GAME_TERRAIN_TILE_H
