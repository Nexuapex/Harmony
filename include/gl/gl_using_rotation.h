//
// gl_using_rotation.h
// Harmony
//

#ifndef HARMONY_GL_USING_ROTATION_H
#define HARMONY_GL_USING_ROTATION_H

#include "gl_library.h"

namespace harmony {
	namespace gl {
		// Pushes a rotation matrix onto the OpenGL stack.
		class using_rotation {
		public:
			using_rotation(angle_t rotation) {
				glPushMatrix();
				glRotatef(rotation, 0.0f, 0.0f, 1.0f);
			}
			
			~using_rotation() {
				glPopMatrix();
			}
		};
	}
}

#endif // HARMONY_GL_USING_ROTATION_H
