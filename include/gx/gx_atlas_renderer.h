//
// gx_atlas_renderer.h
// Harmony
//

#ifndef HARMONY_GX_ATLAS_RENDERER_H
#define HARMONY_GX_ATLAS_RENDERER_H

#include "gl_shader_program.h"
#include "gl_offscreen_renderer.h"

namespace harmony {
	namespace gx {
		class atlas_renderer {
		public:
			// Constructor.
			atlas_renderer();
			
			// Access the useful components of the renderer.
			const gl::shader_program & shader() const;
			const gl::offscreen_renderer & renderer() const;
			
		private:
			gl::shader_program shader_;
			gl::offscreen_renderer renderer_;
		};
	}
}

#endif // HARMONY_GX_ATLAS_RENDERER_H
