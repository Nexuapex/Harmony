//
// gl_clear.cpp
// Harmony
//

#include "gl_clear.h"
#include "gl_library.h"

namespace harmony {
	void gl::clear(const color & bg_color) {
		glClearColor(bg_color.r(), bg_color.g(), bg_color.b(), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}
