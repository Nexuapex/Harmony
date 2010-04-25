//
// gx_atlas_renderer.h
// Harmony
//

#ifndef HARMONY_GX_ATLAS_RENDERER_H
#define HARMONY_GX_ATLAS_RENDERER_H

#include "gl_shader_program.h"
#include "gl_offscreen_renderer.h"
#include "gx_texture_fwd.h"

namespace harmony {
	namespace gx {
		class atlas_renderer {
		public:
			// Constructor.
			atlas_renderer();
			
			// Creating an atlas.
			ivec2 size_for_tile_count(unsigned count, gl::size_t tile_size) const;
			ivec2 next_offset(const ivec2 & offset, const ivec2 & atlas_size, gl::size_t tile_size) const;
			void draw(gx::texture & texture, const ivec2 & offset, gl::size_t tile_size) const;
			
			// Access the useful components of the renderer.
			const gl::shader_program & shader() const;
			const gl::offscreen_renderer & renderer() const;
			
		private:
			unsigned tile_count_for_possible_size(const ivec2 & size, gl::size_t tile_size) const;
			
		private:
			gl::shader_program shader_;
			gl::offscreen_renderer renderer_;
			gl::float_t vertices_[4][2];
		};
	}
}

#endif // HARMONY_GX_ATLAS_RENDERER_H
