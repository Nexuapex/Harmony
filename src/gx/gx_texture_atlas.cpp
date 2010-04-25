//
// gx_texture_atlas.cpp
// Harmony
//

#include "gx_texture_atlas.h"
#include "gx_texture.h"
#include "gl.h"

namespace harmony {
	gx::texture_atlas::texture_atlas(gl::size_t tile_size) : tile_size_(tile_size) {}
	
	void gx::texture_atlas::add_texture(const texture_ref & texture) {
		textures_.insert(texture);
	}
	
	void gx::texture_atlas::load(atlas_renderer & renderer) {
		if (!atlas_) {
			if (!textures_.empty()) {
				// Create the atlas texture.
				ivec2 size = renderer.size_for_tile_count(textures_.size(), tile_size_);
				gl::texture_ref atlas_texture(new gl::texture(size));
				atlas_ = atlas_texture;
				
				// Draw into the texture.
				gl::using_offscreen_renderer active_renderer(renderer.renderer(), atlas_texture);
				gl::using_shader active_shader(renderer.shader());
				gl::clear();
				
				// Draw all the textures.
				ivec2 offset(0, 0);
				for (texture_set::const_iterator iter = textures_.begin(); iter != textures_.end(); ++iter) {
					// Draw the tile itself.
					renderer.draw(**iter, offset, tile_size_);
					
					// Associate the texture with the atlas.
					associate_texture(**iter, static_cast<vec2>(offset), static_cast<vec2>(size));
					
					// Update the current offset.
					offset = renderer.next_offset(offset, size, tile_size_);
				}				
			}			
		}
	}
	
	void gx::texture_atlas::associate_texture(texture & texture, vec2 offset, vec2 size) const {
		// Vector size of a tile.
		const ivec2 tile_size_vec(tile_size_, tile_size_);
		
		// Reassociate the texture.
		texture.texture_ = atlas_;
		texture.size_ = tile_size_vec;
		
		// Calculate the lower-left and upper-right texture coordinates.
		vec2 ll = offset / size;
		vec2 ur = (offset + tile_size_vec) / size;
		
		// Update the texture coordinates.
		texture.tex_coords_[0][0] = ll.x(); texture.tex_coords_[0][1] = ll.y();
		texture.tex_coords_[1][0] = ll.x(); texture.tex_coords_[1][1] = ur.y();
		texture.tex_coords_[2][0] = ur.x(); texture.tex_coords_[2][1] = ur.y();
		texture.tex_coords_[3][0] = ur.x(); texture.tex_coords_[3][1] = ll.y();
	}
}
