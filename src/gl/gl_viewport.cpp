//
// gl_viewport.cpp
// Harmony
//

#include "gl_viewport.h"
#include "gl_library.h"

namespace harmony {
	void gl::set_viewport(ivec2 viewport) {
		glViewport(0, 0, viewport.x(), viewport.y());
	}
}
