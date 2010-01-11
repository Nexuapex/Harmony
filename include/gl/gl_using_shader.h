//
// gl_using_shader.h
// Harmony
//

#ifndef HARMONY_GL_USING_SHADER_H
#define HARMONY_GL_USING_SHADER_H

#include "gl_library.h"
#include "gl_shader_program.h"

namespace harmony {
	namespace gl {
		// Activates an OpenGL shader program.
		class using_shader {
		public:
			using_shader(const shader_program & shader) {
				if (GLEE_VERSION_2_0)
					glUseProgram(shader.name());
			}
			
			~using_shader() {
				if (GLEE_VERSION_2_0)
					glUseProgram(0);
			}
		};
	}
}

#endif // HARMONY_GL_USING_SHADER_H
