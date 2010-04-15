//
// gx_tile_renderer.cpp
// Harmony
//

#include "gx_tile_renderer.h"
#include "gl.h"

namespace harmony {
	gx::tile_renderer::tile_renderer() : tile_shader_("tile.vs", "tile.fs") {}
	
	void gx::tile_renderer::draw(gx::atlas_renderer & intermediate_renderer, game::level & level) const {
		game::size_t num_layers = level.num_terrain_layers();
		
		for (unsigned index = 0; index < num_layers; ++index)
			draw(intermediate_renderer, level.terrain_layer_at(index));
	}
	
	void gx::tile_renderer::draw(gx::atlas_renderer & intermediate_renderer, game::terrain_layer & layer) const {
		// Find the first cell.
		ivec2 cell = layer.first_nonempty_cell(layer.rect());
		
		// Make sure that the first cell exists.
		if (cell.x() < 0 || cell.y() < 0)
			return;
		
		// Get the rendering object.
		const game::terrain_layer::buffer_object & rendering_object
			= layer.rendering_object(intermediate_renderer);
		
		// Activate the rendering elements.
		using_layer active(
			tile_shader_, layer, rendering_object, *layer.tile(cell)
		);
		
		// Draw the layer.
		active.draw();
	}
	
	// Potentially incorrect optimization alert: Instead of giving OpenGL correct texture coordinates for
	// every tile, we use the first tile in any given layer's texture coordinates to stand for them all.
	// This will only render incorrectly if a layer consists of multiple tiles that have very different
	// source image sizes, which is something I don't foresee happening in the immediate future.
	gx::tile_renderer::using_layer::using_layer(const gl::shader_program & shader,
		game::terrain_layer & layer,
		const game::terrain_layer::buffer_object & rendering_object, 
		const game::terrain_tile & initial_tile)
		: shader(shader)
		, vertex_buffer(rendering_object.vertices())
		, index_buffer(rendering_object.indices())
		, translation(layer.origin() * layer.tile_size())
		, extent(shader, "extent", initial_tile.texture()->source_extent())
		, texture(shader, "tile", initial_tile.texture()->source())
		, rotation(shader, "rotation", 0) {}
	
	void gx::tile_renderer::using_layer::draw() {
		index_buffer.draw(GL_QUADS);
	}
}
