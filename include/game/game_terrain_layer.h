//
// game_terrain_layer.h
// Harmony
//

#ifndef HARMONY_GAME_TERRAIN_LAYER_H
#define HARMONY_GAME_TERRAIN_LAYER_H

#include <boost/shared_ptr.hpp>

#include "game_types.h"
#include "game_terrain_tile.h"
#include "geom_rect.h"
#include "gl_types.h"
#include "gl_buffer.h"
#include "gx_texture_atlas.h"

namespace harmony {
	namespace game {
		// A single layer of terrain tiles.
		class terrain_layer {
		public:
			// Constructor and destructor.
			terrain_layer(const ivec2 & origin, const ivec2 & size, game::size_t tile_size);
			~terrain_layer();
			
			// The origin point of this layer, in cell coordinates.
			ivec2 origin() const { return origin_; }
			
			// The size of this layer, in cell coordinates.
			ivec2 size() const { return size_; }
			
			// The rectangle that includes all cells in the layer.
			geom::rect rect() const {
				return geom::rect(origin_.x(), origin_.y(), size_.x(), size_.y());
			}
			
			// Get the terrain tile in a specific cell.
			terrain_tile_ref tile(const ivec2 & cell) const {
				return (*this)[cell];
			}
			
			// Change the terrain tile in a specific cell.
			void set_tile(const ivec2 & cell, const terrain_tile_ref & new_tile);
			
			// Convert from cell coordinates to world coordinates.
			vec2 cell_center(const ivec2 & cell) const;
			
			// The first cell in the given region that, scanning in row-major
			// order, is not empty.
			ivec2 first_nonempty_cell(const geom::rect & region) const;
			
			// The size, in pixels, of a tile in this layer.
			game::size_t tile_size() const;
			
		public:
			struct tile_vertex {
				gl::float_t x, y;
				gl::float_t s, t;
				gl::ushort_t rotation;
				
			public:
				void set_tex_coords(const gl::float_t (& coords)[2]);
			};
			
		public:
			class buffer_object {
			public:
				// Useful typedefs.
				typedef gl::buffer<tile_vertex> vertex_buffer;
				typedef gl::buffer_types<tile_vertex>::ref vertex_buffer_ref;
				typedef gl::buffer<gl::index_t> index_buffer;
				typedef gl::buffer_types<gl::index_t>::ref index_buffer_ref;
				
			public:
				// Create or recreate the buffers for a specific layer.
				void prepare(terrain_layer & layer);
				
				// Getting your hands on the buffers.
				const vertex_buffer_ref vertices() const { return vertices_; }
				const index_buffer_ref indices() const { return indices_; }
				
			private:
				vertex_buffer_ref vertices_;
				index_buffer_ref indices_;
			};
			
		public:
			// Prepare and return the object used for rendering.
			const buffer_object & rendering_object(gx::atlas_renderer & intermediate_renderer);
			
		protected:
			// Subscript operator to provide access to a cell.
			terrain_tile_ref & operator[](const ivec2 & cell) {
				return tiles_[cell.y() * size_.x() + cell.x()];
			}
			
			// The const version of the subscript operator.
			const terrain_tile_ref & operator[](const ivec2 & cell) const {
				return tiles_[cell.y() * size_.x() + cell.x()];
			}
			
		protected:
			// Assignment operator to satisfy MSVC++.
			terrain_layer & operator=(const terrain_layer & that);
			
		private:
			ivec2 origin_, size_;
			game::size_t tile_size_;
			terrain_tile_ref * tiles_;
			gx::texture_atlas atlas_;
			buffer_object buffer_object_;
			bool dirty_;
		};
		
		typedef boost::shared_ptr<terrain_layer> terrain_layer_ref;
	}
}

#endif // HARMONY_GAME_TERRAIN_LAYER_H
