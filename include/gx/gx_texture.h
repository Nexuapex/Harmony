//
// gx_texture.h
// Harmony
//

#ifndef HARMONY_GX_TEXTURE_H
#define HARMONY_GX_TEXTURE_H

#include "gx_texture_fwd.h"
#include "gx_texture_atlas.h"
#include "gl_types.h"
#include "gl_texture.h"

namespace harmony {
	namespace gx {
		// Represents a gl::texture and associated texture coordinates.
		class texture {
		public:
			texture(const gl::texture_ref & texture);
			
			gl::texture_t name(bool require_loaded = true) const;
			ivec2 size() const;
			const gl::float_t (& tex_coords() const)[4][2];
			
			gl::texture_ref source() const;
			vec2 source_extent() const;
			
			void load() const;
			
		public:
			// Atlases can reassociate the texture.
			friend void texture_atlas::load(atlas_renderer & renderer);
			
		private:
			gl::texture_ref texture_;
			gl::float_t tex_coords_[4][2];
			ivec2 size_;
		};
	}
}

#endif // HARMONY_GX_TEXTURE_H
