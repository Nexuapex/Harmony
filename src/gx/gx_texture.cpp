//
// gx_texture.cpp
// Harmony
//

#include <cstring>

#include "gx_texture.h"
#include "gl_texture.h"

namespace harmony {
	gx::texture::texture(const gl::texture_ref & texture)
		: texture_(texture)
		, size_(texture->filled_size())
	{
		texture->copy_tex_coords(tex_coords_);
	}
	
	gl::texture_t gx::texture::name(bool require_loaded) const {
		return texture_->name(require_loaded);
	}
	
	ivec2 gx::texture::size() const {
		return size_;
	}
	
	const gl::quad_t & gx::texture::tex_coords() const {
		return tex_coords_;
	}
	
	void gx::texture::copy_tex_coords(gl::quad_t & tex_coords) const {
		memcpy(&tex_coords, &tex_coords_, sizeof(tex_coords));
	}
	
	gl::texture_ref gx::texture::source() const {
		return texture_;
	}
	
	vec2 gx::texture::source_extent() const {
		return static_cast<vec2>(texture_->size()) / static_cast<vec2>(size_);
	}
	
	void gx::texture::load() const {
		texture_->load();
	}
}
