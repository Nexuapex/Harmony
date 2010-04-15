//
// gl_offscreen_renderer.cpp
// Harmony
//

#include "gl_offscreen_renderer.h"

#include <iostream>

namespace harmony {
	gl::offscreen_renderer::offscreen_renderer() {
		if (GLEE_EXT_framebuffer_object)
			glGenFramebuffersEXT(1, &framebuffer_);
	}
	
	gl::offscreen_renderer::~offscreen_renderer() {
		if (GLEE_EXT_framebuffer_object)
			glDeleteFramebuffersEXT(1, &framebuffer_);
	}
	
	gl::framebuffer_t gl::offscreen_renderer::framebuffer() const {
		return framebuffer_;
	}
}
