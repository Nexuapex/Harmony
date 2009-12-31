//
// gl_viewport.cpp
// Harmony
//

#include "gl_viewport.h"
#include "gl_library.h"

namespace harmony {
	void gl::set_viewport(gl::size_t width, gl::size_t height) {
		glViewport(0, 0, width, height);
	}
}
