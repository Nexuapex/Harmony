//
// game_terrain_layer.h
// Harmony
//

#ifndef HARMONY_GAME_TERRAIN_LAYER_H
#define HARMONY_GAME_TERRAIN_LAYER_H

#include <boost/shared_ptr.hpp>

#include "vec2.h"
#include "ivec2.h"
#include "game_types.h"
#include "game_terrain_tile.h"
#include "gl_types.h"

namespace harmony {
	namespace game {
		// A single layer of terrain tiles.
		class terrain_layer {
		public:
			// Constructor and destructor.
			terrain_layer(const ivec2 & origin, game::size_t width,
				game::size_t height, game::size_t tile_size);
			~terrain_layer();
			
			// The origin point of this layer, in cells.
			const ivec2 & origin() const { return origin_; }
			
			// The size of this layer, in cells.
			game::size_t width() const { return width_; }
			game::size_t height() const { return height_; }
			
			// Get the terrain tile in a specific cell.
			terrain_tile_ref tile(const ivec2 & cell) const {
				return (*this)[cell];
			}
			
			// Change the terrain tile in a specific cell.
			void set_tile(const ivec2 & cell, const terrain_tile_ref & new_tile);
			
			// Convert from cell coordinates to world coordinates.
			vec2 cell_center(const ivec2 & cell) const;
			
			// The first cell, scanning in row-major order, that is not empty.
			ivec2 first_nonempty_cell() const;
			
			// The size, in pixels, of a tile in this layer.
			game::size_t tile_size() const;
			
			// The vertices for any individual tile in this layer.
			const gl::float_t * tile_vertices() const;
			
		protected:
			// Subscript operator to provide access to a cell.
			terrain_tile_ref & operator[](const ivec2 & cell) {
				return tiles_[cell.y() * width_ + cell.x()];
			}
			
			// The const version of the subscript operator.
			const terrain_tile_ref & operator[](const ivec2 & cell) const {
				return tiles_[cell.y() * width_ + cell.x()];
			}
			
			// Assignment operator to satisfy MSVC++.
			terrain_layer & operator=(const terrain_layer & that);
			
		private:
			const ivec2 origin_;
			game::size_t width_, height_;
			game::size_t tile_size_;
			terrain_tile_ref * tiles_;
			gl::float_t vertices_[4][2];
		};
		
		typedef boost::shared_ptr<terrain_layer> terrain_layer_ref;
	}
}

#endif // HARMONY_GAME_TERRAIN_LAYER_H
