//
// game_terrain_tile.cpp
// Harmony
//

#include "game_terrain_tile.h"

namespace harmony {
	game::terrain_tile::terrain_tile(const gl::texture_ref & texture, gl::int_t rotation)
		: texture_(texture), rotation_(rotation)
	{
		texture->load_tex_coords(tex_coords_);
	}
	
	game::terrain_tile::~terrain_tile() {}
	
	gl::texture_ref game::terrain_tile::texture() const {
		return texture_;
	}
	
	gl::int_t game::terrain_tile::rotation() const {
		return rotation_;
	}

	const gl::float_t * game::terrain_tile::tex_coords() const {
		return &tex_coords_[0][0];
	}
}
