//
// gx_texture.h
// Harmony
//

#ifndef HARMONY_GX_TEXTURE_H
#define HARMONY_GX_TEXTURE_H

#include "gx_texture_fwd.h"
#include "gx_texture_atlas.h"
#include "gl_types.h"
#include "gl_texture_fwd.h"

namespace harmony {
	namespace gx {
		// Represents a gl::texture and associated texture coordinates.
		class texture {
		public:
			texture(const gl::texture_ref & texture);
			
			gl::texture_t name(bool require_loaded = true) const;
			ivec2 size() const;
			const gl::quad_t & tex_coords() const;
			void copy_tex_coords(gl::quad_t & tex_coords) const;
			
			gl::texture_ref source() const;
			vec2 source_extent() const;
			
			void load() const;
			
		public:
			// Atlases can reassociate the texture.
			friend void texture_atlas::associate_texture(texture & texture, vec2 offset, vec2 size) const;
			
		private:
			gl::texture_ref texture_;
			gl::quad_t tex_coords_;
			ivec2 size_;
		};
	}
}

#endif // HARMONY_GX_TEXTURE_H
