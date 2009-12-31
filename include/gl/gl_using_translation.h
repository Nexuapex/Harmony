//
// gl_using_translation.h
// Harmony
//

#ifndef HARMONY_GL_USING_TRANSLATION_H
#define HARMONY_GL_USING_TRANSLATION_H

#include "gl_library.h"

namespace harmony {
	namespace gl {
		// Pushes a translation matrix onto the OpenGL stack.
		class using_translation {
		public:
			using_translation(const vec2 & translation) {
				glPushMatrix();
				glTranslatef(translation.x(), translation.y(), 0.0f);
			}
			
			~using_translation() {
				glPopMatrix();
			}
		};
	}
}

#endif // HARMONY_GL_USING_TRANSLATION_H
