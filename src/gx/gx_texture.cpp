//
// gx_texture.cpp
// Harmony
//

#include "gx_texture.h"

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
	
	const gl::float_t (& gx::texture::tex_coords() const)[4][2] {
		return tex_coords_;
	}
	
	gl::texture_ref gx::texture::source() const {
		return texture_;
	}
	
	vec2 gx::texture::source_extent() const {
		return vec2(
			texture_->size().fx() / size_.fx(),
			texture_->size().fy() / size_.fy()
		);
	}
	
	void gx::texture::load() const {
		texture_->load();
	}
}
