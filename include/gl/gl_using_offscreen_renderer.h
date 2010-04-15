//
// gl_using_offscreen_renderer.h
// Harmony
//

#ifndef HARMONY_GL_USING_OFFSCREEN_RENDERER_H
#define HARMONY_GL_USING_OFFSCREEN_RENDERER_H

#include "gl_offscreen_renderer.h"
#include "gl_texture.h"

namespace harmony {
	namespace gl {
		class using_offscreen_renderer {
		public:
			using_offscreen_renderer(const offscreen_renderer & renderer,
				const texture_ref & texture);
			~using_offscreen_renderer();
		};
	}
}

#endif // HARMONY_GL_USING_OFFSCREEN_RENDERER_H
