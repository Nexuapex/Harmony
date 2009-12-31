//
// gl_camera.h
// Harmony
//

#ifndef HARMONY_GL_CAMERA_H
#define HARMONY_GL_CAMERA_H

#include "gl_types.h"

namespace harmony {
	namespace gl {
		// Set up the camera projection matrix.
		void set_camera_projection(size_t width, size_t height);
		
		// Set up the camera modelview matrix, looking at a given position.
		void set_camera_position(ivec2 position);
	}
}

#endif
