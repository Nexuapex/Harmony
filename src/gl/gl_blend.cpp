//
// gl_blend.cpp
// Harmony
//

#include "gl_blend.h"
#include "gl_library.h"

namespace harmony {
	void gl::set_blending_enabled(bool enabled) {
		if (enabled) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		} else {
			glDisable(GL_BLEND);
		}
	}
}
