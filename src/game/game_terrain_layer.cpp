//
// game_terrain_layer.cpp
// Harmony
//

#include "game_terrain_layer.h"

namespace harmony {
	game::terrain_layer::terrain_layer(const ivec2 & origin,
		game::size_t width, game::size_t height, game::size_t tile_size)
		: origin_(origin), width_(width), height_(height)
		, tile_size_(tile_size), tiles_(new terrain_tile_ref[width * height])
	{
		// Cast the tile's size to a float.
		gl::float_t size = static_cast<gl::float_t>(tile_size);

		// The vertices of any given tile.
		vertices_[0][0] = 0.00; vertices_[0][1] = 0.00; // Top left.
		vertices_[1][0] = 0.00; vertices_[1][1] = size; // Bottom left.
		vertices_[2][0] = size; vertices_[2][1] = size; // Bottom right.
		vertices_[3][0] = size; vertices_[3][1] = 0.00; // Top right.
	}
	
	game::terrain_layer::~terrain_layer() {
		delete [] tiles_;
	}
	
	void game::terrain_layer::set_tile(const ivec2 & cell, const terrain_tile_ref & new_tile) {
		(*this)[cell] = new_tile;
	}
	
	game::size_t game::terrain_layer::tile_size() const {
		return tile_size_;
	}
	
	vec2 game::terrain_layer::cell_center(const ivec2 & cell) const {
		float size = static_cast<float>(tile_size_);
		return (vec2(cell) * size) + vec2(size / 2.0f, size / 2.0f);
	}
	
	ivec2 game::terrain_layer::first_nonempty_cell(const irect & region) const {
		for (ivec2 cell = region.origin; cell.y() < region.y2(); cell.incr_y())
			for (cell.set_x(region.x1()); cell.x() < region.x2(); cell.incr_x())
				if ((*this)[cell])
					return cell;
		
		return ivec2(-1, -1);
	}
	
	const gl::float_t * game::terrain_layer::tile_vertices() const {
		return &vertices_[0][0];
	}
	
	game::terrain_layer & game::terrain_layer::operator=(const game::terrain_layer & that) {
		(void)that;
		return *this;
	}
}
