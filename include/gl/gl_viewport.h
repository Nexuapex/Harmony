//
// gl_viewport.h
// Harmony
//

#ifndef HARMONY_GL_VIEWPORT_H
#define HARMONY_GL_VIEWPORT_H

#include "gl_types.h"

namespace harmony {
	namespace gl {
		// Set the size of the OpenGL viewport.
		void set_viewport(size_t width, size_t height);
	}
}

#endif // HARMONY_GL_VIEWPORT_H
