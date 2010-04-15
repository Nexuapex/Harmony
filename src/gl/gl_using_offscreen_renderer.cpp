//
// gl_using_offscreen_renderer.cpp
// Harmony
//

#include "gl_using_offscreen_renderer.h"

namespace harmony {
	gl::using_offscreen_renderer::using_offscreen_renderer(
			const offscreen_renderer & renderer, const texture_ref & texture) {
		if (GLEE_EXT_framebuffer_object) {
			// Bind the framebuffer.
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, renderer.framebuffer());
			
			// Bind the texture.
			glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,
				GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, texture->name(), 0);
			
			// Set up the viewport.
			ivec2 size = texture->size();
			glPushAttrib(GL_VIEWPORT_BIT);
			glViewport(0, 0, size.x(), size.y());
			
			// Set up the modelview and projection matrices.
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();
		}
	}
	
	gl::using_offscreen_renderer::~using_offscreen_renderer() {
		if (GLEE_EXT_framebuffer_object) {
			// Reset the matrices.
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
			
			// Reset everything else.
			glPopAttrib();
			glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,
				GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, 0, 0);
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		}
	}
}
