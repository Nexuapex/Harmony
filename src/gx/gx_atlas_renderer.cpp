//
// gx_atlas_renderer.cpp
// Harmony
//

#include "gx_atlas_renderer.h"
#include "gx_texture.h"
#include "gl.h"

namespace harmony {
	gx::atlas_renderer::atlas_renderer() : shader_("atlas.vs", "atlas.fs") {
		// The vertices of any given tile.
		vertices_[0][0] = -1.0; vertices_[0][1] = -1.0;
		vertices_[1][0] = -1.0; vertices_[1][1] = +1.0;
		vertices_[2][0] = +1.0; vertices_[2][1] = +1.0;
		vertices_[3][0] = +1.0; vertices_[3][1] = -1.0;
	}
	
	const gl::shader_program & gx::atlas_renderer::shader() const {
		return shader_;
	}
	
	const gl::offscreen_renderer & gx::atlas_renderer::renderer() const {
		return renderer_;
	}
	
	ivec2 gx::atlas_renderer::size_for_tile_count(unsigned count, gl::size_t tile_size) const {
		// This is the minimum size of texture that an OpenGL implementation
		// is required to support.
		ivec2 size(64, 64);
		
		// Iteratively determine a legal size.
		while (tile_count_for_possible_size(size, tile_size) < count) {
			size.set_x(size.x() * 2);
			if (tile_count_for_possible_size(size, tile_size) >= count) break;
			size.set_y(size.y() * 2);
		}
		
		return size;
	}
	
	ivec2 gx::atlas_renderer::next_offset(const ivec2 & offset, const ivec2 & atlas_size, gl::size_t tile_size) const {
		// Advance in the x direction.
		ivec2 new_offset(offset.x() + tile_size, offset.y());
		
		// If needed, go down to a new row.
		if ((new_offset.x() + tile_size) > atlas_size.x()) {
			new_offset.set_x(0);
			new_offset.set_y(offset.y() + tile_size);
		}
		
		return new_offset;
	}
	
	void gx::atlas_renderer::draw(gx::texture & texture, const ivec2 & offset, gl::size_t tile_size) const {
		// Don't really care about efficiency when building a texture
		// atlas, so there's no reason not to submit vertices each time.
		gl::using_vertices active_vertices(4, 2, vertices_, texture.tex_coords());
		
		// Bind the texture.
		gl::using_uniform<gl::texture_ref> active_texture(shader_, "texture", texture.source());
		
		// Draw the tile.
		gl::set_viewport(ivec2(tile_size, tile_size), offset);
		active_vertices.draw(GL_QUADS);
	}
	
	unsigned gx::atlas_renderer::tile_count_for_possible_size(const ivec2 & size, gl::size_t tile_size) const {
		return (size.x() / tile_size) * (size.y() / tile_size);
	}
}
