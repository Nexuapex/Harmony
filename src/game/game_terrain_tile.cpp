//
// game_terrain_tile.cpp
// Harmony
//

#include "game_terrain_tile.h"

namespace harmony {
	game::terrain_tile::terrain_tile(bool passable,
		const gx::texture_ref & texture, gl::ushort_t rotation)
		: passable_(passable), texture_(texture), rotation_(rotation) {}
	
	game::terrain_tile::~terrain_tile() {}
	
	gx::texture_ref game::terrain_tile::texture() const {
		return texture_;
	}
	
	gl::ushort_t game::terrain_tile::rotation() const {
		return rotation_;
	}
}
