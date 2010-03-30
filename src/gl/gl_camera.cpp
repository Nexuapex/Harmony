//
// gl_camera.cpp
// Harmony
//

#include "gl_camera.h"
#include "gl_library.h"

namespace harmony {
	void gl::set_camera_projection(ivec2 viewport) {
		// Even when OpenGL is set up to correspond directly to pixels on the
		// screen, there can be problems. Specifically, OpenGL coordinates begin
		// at the center of a pixel (0.5, 0.5). So points and lines should start
		// from the center of a pixel. However, quads and rects should use
		// normal integral coordinates, so for our purposes nothing special
		// needs to happen.
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, viewport.x(), viewport.y(), 0);
		glMatrixMode(GL_MODELVIEW);
	}
	
	void gl::set_camera_position(ivec2 position) {
		// Reset the modelview matrix.
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		// Set the camera's position.
		glTranslated(
			static_cast<GLdouble>(-position.x()),
			static_cast<GLdouble>(-position.y()),
			0.0
		);
	}
}
