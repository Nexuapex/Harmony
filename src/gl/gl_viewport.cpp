//
// gl_viewport.cpp
// Harmony
//

#include "gl_viewport.h"
#include "gl_library.h"

namespace harmony {
	void gl::set_viewport(ivec2 size, ivec2 offset) {
		glViewport(offset.ux(), offset.uy(), size.x(), size.y());
	}
}
