//
// gl_offscreen_renderer.h
// Harmony
//

#ifndef HARMONY_GL_OFFSCREEN_RENDERER_H
#define HARMONY_GL_OFFSCREEN_RENDERER_H

#include "types.h"
#include "gl_types.h"

namespace harmony {
	namespace gl {
		class offscreen_renderer {
		public:
			// Constructors.
			offscreen_renderer();
			~offscreen_renderer();
			
			// The OpenGL names of the renderer.
			framebuffer_t framebuffer() const;
			
		private:
			framebuffer_t framebuffer_;
		};
	}
}

#endif // HARMONY_GL_OFFSCREEN_RENDERER_H
