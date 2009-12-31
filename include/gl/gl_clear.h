//
// gl_clear.h
// Harmony
//

#ifndef HARMONY_GL_CLEAR_H
#define HARMONY_GL_CLEAR_H

#include "gl_color.h"

namespace harmony {
	namespace gl {
		// Clear the OpenGL viewport.
		void clear(const color & bg_color = color());
	}
}

#endif // HARMONY_GL_CLEAR_H
