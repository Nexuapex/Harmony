//
// gx_sprite.cpp
// Harmony
//

#include "gx_sprite.h"

namespace harmony {
	gx::sprite::sprite(const std::string & name, const std::string & suffix,
		gl::size_t width, gl::size_t height)
		: name_(name), suffix_(suffix), width_(width), height_(height)
	{
		// Useful temporaries.
		gl::float_t w = static_cast<gl::float_t>(width) / 2.0f;
		gl::float_t h = static_cast<gl::float_t>(height) / 2.0f;
		
		// The vertices of this sprite.
		vertices_[0][0] = -w; vertices_[0][1] = -h; // Top left.
		vertices_[1][0] = -w; vertices_[1][1] =  h; // Bottom left.
		vertices_[2][0] =  w; vertices_[2][1] =  h; // Bottom right.
		vertices_[3][0] =  w; vertices_[3][1] = -h; // Top right.
	}
	
	std::string gx::sprite::name() const {
		return name_;
	}
	
	std::string gx::sprite::suffix() const {
		return suffix_;
	}
	
	gl::size_t gx::sprite::width() const {
		return width_;
	}
	
	gl::size_t gx::sprite::height() const {
		return height_;
	}
	
	const gl::float_t * gx::sprite::vertices() const {
		return &vertices_[0][0];
	}
	
	const gl::float_t * gx::sprite::tex_coords() const {
		return &tex_coords_[0][0];
	}
	
	void gx::sprite::touch(const gl::texture_ref & texture) {
		// If this is the first texture we've touched, populate the tex coords.
		// Potentially incorrect optimization alert: if multiple textures for
		// one sprite have very different source image sizes, this will fail.
		if (texture_cache_.empty())
			texture->load_tex_coords(tex_coords_);
		
		// Preserve the texture. (Without this, the texture cache, which keeps
		// only weak references to textures, is likely to deallocate it.)
		texture_cache_.insert(texture);
	}
}
