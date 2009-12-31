//
// gx_tile_renderer.cpp
// Harmony
//

#include "gx_tile_renderer.h"
#include "gl.h"

namespace harmony {
	gx::tile_renderer::tile_renderer() : tile_shader_("tile.vs", "tile.fs") {}
	
	void gx::tile_renderer::draw(game::level & level) const {
		game::size_t num_layers = level.num_terrain_layers();
		
		for (unsigned index = 0; index < num_layers; ++index)
			draw(level.terrain_layer_at(index));
	}
	
	void gx::tile_renderer::draw(game::terrain_layer & layer) const {
		// Find the first cell.
		ivec2 cell = layer.first_nonempty_cell();
		
		// Make sure that the first cell exists.
		if (cell.x() < 0 || cell.y() < 0)
			return;
		
		// Activate the shader and the tile vertices.
		gl::using_shader active_shader(tile_shader_);
		using_layer active_layer(layer, *layer.tile(cell));
		
		// Translate to the layer origin.
		gl::using_translation translation(layer.origin() * layer.tile_size());
		
		// Determine the uniform locations.
		const gl::uniform_t tile_uniform = tile_shader_.uniform_location("tile");
		const gl::uniform_t rotation_uniform = tile_shader_.uniform_location("rotation");
		
		// Initialize uniform values.
		gl::texture * current_texture = &(*layer.tile(cell)).texture();
		gl::int_t current_rotation = 0;
		
		// Set initial uniform values.
		active_shader.set_uniform(tile_uniform, *current_texture);
		active_shader.set_uniform(rotation_uniform, current_rotation);
		
		// Loop through the rest of the cells.
		for (; cell.uy() < layer.height(); cell.incr_y()) {
			for (; cell.ux() < layer.width(); cell.incr_x()) {
				// If the tile exists, draw it.
				game::terrain_tile_ref tile = layer.tile(cell);
				if (tile) {
					// Set the texture.
					if (&tile->texture() != current_texture) {
						current_texture = &tile->texture();
						active_shader.set_uniform(tile_uniform, *current_texture);
					}
					
					// Set the rotation.
					if (tile->rotation() != current_rotation) {
						current_rotation = tile->rotation();
						active_shader.set_uniform(rotation_uniform, current_rotation);
					}
					
					// Actually draw the tile.
					gl::using_translation translation(cell * layer.tile_size());
					active_layer.draw(GL_QUADS);
				}
			}
			cell.set_x(0);
		}
	}
	
	// Potentially incorrect optimization alert! Instead of giving OpenGL correct texture coordinates for
	// every tile, we use the first tile in any given layer's texture coordinates to stand for them all.
	// This will only render incorrectly if a layer consists of multiple tiles that have very different
	// source image sizes, which is something I don't foresee happening in the immediate future.
	gx::tile_renderer::using_layer::using_layer(game::terrain_layer & layer, game::terrain_tile & initial_tile)
			: using_vertices(4, 2, layer.tile_vertices(), initial_tile.tex_coords()) {}
}
