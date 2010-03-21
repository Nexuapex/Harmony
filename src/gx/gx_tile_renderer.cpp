//
// gx_tile_renderer.cpp
// Harmony
//

#include "gx_tile_renderer.h"
#include "gl.h"

namespace harmony {
	gx::tile_renderer::tile_renderer() : tile_shader_("tile.vs", "tile.fs") {}
	
	void gx::tile_renderer::draw(const irect & viewport, game::level & level) const {
		game::size_t num_layers = level.num_terrain_layers();
		
		for (unsigned index = 0; index < num_layers; ++index)
			draw(viewport, level.terrain_layer_at(index));
	}
	
	void gx::tile_renderer::draw(const irect & viewport, game::terrain_layer & layer) const {
		// Find the visible area.
		irect visible = viewport.tile_bounding_rect(layer.tile_size()).intersect(layer.rect());
		visible.origin -= layer.origin();
		
		// Find the first cell.
		ivec2 cell = layer.first_nonempty_cell(visible);
		
		// Make sure that the first cell exists.
		if (cell.x() < 0 || cell.y() < 0)
			return;
		
		// Activate the shader and the tile vertices.
		using_layer active_layer(tile_shader_, layer, *layer.tile(cell));
		
		// Initialize uniforms.
		gl::using_uniform<gl::texture_ref> current_texture(
			tile_shader_, "tile", (*layer.tile(cell)).texture()
		);
		gl::using_uniform<gl::int_t> current_rotation(
			tile_shader_, "rotation", 0
		);
		
		// Loop through the rest of the cells.
		for (; cell.y() < visible.y2(); cell.incr_y()) {
			for (cell.set_x(visible.x1()); cell.x() < visible.x2(); cell.incr_x()) {
				// If the tile exists, draw it.
				game::terrain_tile_ref tile = layer.tile(cell);
				if (tile) {
					// Set the texture.
					current_texture.set(tile->texture());
					
					// Set the rotation.
					current_rotation.set(tile->rotation());
					
					// Actually draw the tile.
					gl::using_translation translation(cell * layer.tile_size());
					active_layer.draw(GL_QUADS);
				}
			}
		}
	}
	
	// Potentially incorrect optimization alert: Instead of giving OpenGL correct texture coordinates for
	// every tile, we use the first tile in any given layer's texture coordinates to stand for them all.
	// This will only render incorrectly if a layer consists of multiple tiles that have very different
	// source image sizes, which is something I don't foresee happening in the immediate future.
	gx::tile_renderer::using_layer::using_layer(const gl::shader_program & shader,
		const game::terrain_layer & layer, const game::terrain_tile & initial_tile)
		: using_shader(shader)
		, using_vertices(4, 2, layer.tile_vertices(), initial_tile.tex_coords())
		, translation_(layer.origin() * layer.tile_size())
		, tile_ratio_(shader, "tile_ratio", initial_tile.texture()->area_ratio()) {}
}
