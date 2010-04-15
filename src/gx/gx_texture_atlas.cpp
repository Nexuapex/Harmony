//
// gx_texture_atlas.cpp
// Harmony
//

#include "gx_texture_atlas.h"
#include "gx_texture.h"
#include "gl.h"

namespace harmony {
	gx::texture_atlas::texture_atlas(gl::size_t tile_size)
		: tile_size_(tile_size)
	{
		// The vertices of any given tile.
		vertices_[0][0] = -1.0; vertices_[0][1] = -1.0;
		vertices_[1][0] = -1.0; vertices_[1][1] = +1.0;
		vertices_[2][0] = +1.0; vertices_[2][1] = +1.0;
		vertices_[3][0] = +1.0; vertices_[3][1] = -1.0;
	}
	
	void gx::texture_atlas::add_texture(const texture_ref & texture) {
		textures_.insert(texture);
	}
	
	void gx::texture_atlas::load(atlas_renderer & renderer) {
		if (!atlas_) {
			// Preliminary work for creating an atlas.
			unsigned tile_count = textures_.size();
			if (tile_count == 0) return;
			ivec2 tile_size_vec(tile_size_, tile_size_);
			ivec2 size(64, 64);
			
			// Iteratively determine a potential size.
			while (tiles_for_possible_size(size) < tile_count) {
				size.set_x(size.x() * 2);
				if (tiles_for_possible_size(size) >= tile_count) break;
				size.set_y(size.y() * 2);
			}
			
			// Create the atlas texture.
			gl::texture_ref atlas_texture(new gl::texture(size));
			atlas_ = atlas_texture;
			
			// Draw into the texture.
			gl::using_offscreen_renderer active_renderer(renderer.renderer(), atlas_);
			gl::clear();
			
			// Activate the shader program.
			gl::using_shader active_shader(renderer.shader());
			
			// Draw all the textures.
			ivec2 offset(0, 0);
			for (texture_set::const_iterator iter = textures_.begin(); iter != textures_.end(); ++iter) {
				texture & tex = **iter;
				
				// Don't really care about efficiency when building a texture
				// atlas, so there's no reason not to submit vertices each time.
				gl::using_vertices active_vertices(4, 2, &vertices_[0][0], &(tex.tex_coords())[0][0]);
				
				// Bind the texture.
				gl::using_uniform<gl::texture_ref> active_texture(
					renderer.shader(), "texture", tex.source()
				);
				
				// Draw the tile.
				gl::set_viewport(tile_size_vec, offset);
				active_vertices.draw(GL_QUADS);
				
				// Reassociate the texture.
				tex.texture_ = atlas_;
				tex.size_ = tile_size_vec;
				
				// Calculate the lower-left and upper-right texture coordinates.
				vec2 ll(
					offset.fx() / size.fx(),
					offset.fy() / size.fy()
				);
				vec2 ur(
					(offset.fx() + tile_size_) / size.fx(),
					(offset.fy() + tile_size_) / size.fy()
				);
				
				// Update the texture coordinates.
				tex.tex_coords_[0][0] = ll.x(); tex.tex_coords_[0][1] = ll.y();
				tex.tex_coords_[1][0] = ll.x(); tex.tex_coords_[1][1] = ur.y();
				tex.tex_coords_[2][0] = ur.x(); tex.tex_coords_[2][1] = ur.y();
				tex.tex_coords_[3][0] = ur.x(); tex.tex_coords_[3][1] = ll.y();
				
				// Update the current offset.
				offset.set_x(offset.x() + tile_size_);
				if ((offset.x() + tile_size_) > size.x()) {
					offset.set_x(0);
					offset.set_y(offset.y() + tile_size_);
				}
			}
		}
	}
	
	unsigned gx::texture_atlas::tiles_for_possible_size(const ivec2 & size) const {
		return (size.x() / tile_size_) * (size.y() / tile_size_);
	}
}
