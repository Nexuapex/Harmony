//
// gl_viewport.h
// Harmony
//

#ifndef HARMONY_GL_VIEWPORT_H
#define HARMONY_GL_VIEWPORT_H

#include "gl_types.h"

namespace harmony {
	namespace gl {
		// Alter the OpenGL viewport.
		void set_viewport(ivec2 size, ivec2 offset = ivec2());
	}
}

#endif // HARMONY_GL_VIEWPORT_H
