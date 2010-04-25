//
// gx_texture_atlas.h
// Harmony
//

#ifndef HARMONY_GX_TEXTURE_ATLAS_H
#define HARMONY_GX_TEXTURE_ATLAS_H

#include <boost/unordered_set.hpp>

#include "gl_types.h"
#include "gl_texture_fwd.h"
#include "gx_atlas_renderer.h"
#include "gx_texture_fwd.h"

namespace harmony {
	namespace gx {
		class texture_atlas {
		private:
			typedef boost::unordered_set<texture_ref> texture_set;
			
		public:
			// Constructor.
			texture_atlas(gl::size_t tile_size);
			
			// Adds a texture to the atlas.
			void add_texture(const texture_ref & texture);
			
			// If necessary, create the atlas texture.
			void load(atlas_renderer & renderer);
			
			// Reassociates a texture to reference this atlas. Used by load().
			void associate_texture(texture & texture, vec2 offset, vec2 size) const;
			
		private:
			gl::size_t tile_size_;
			texture_set textures_;
			gl::texture_ref atlas_;
		};
	}
}

#endif // HARMONY_GX_TEXTURE_ATLAS_H
