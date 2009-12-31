//
// gl_shader_program.h
// Harmony
//

#ifndef HARMONY_GL_SHADER_PROGRAM_H
#define HARMONY_GL_SHADER_PROGRAM_H

#include <string>

#include "gl_types.h"

namespace harmony {
	namespace gl {
		// Represents a vertex and fragment shader.
		class shader_program {
		public:
			shader_program(const std::string & vertex, const std::string & fragment);
			~shader_program();
			
			shader_t name() const;
			uniform_t uniform_location(const char * name) const;
			
		private:
			shader_t program_;
			shader_t vertexShader_, fragmentShader_;
		};
	}
}

#endif // HARMONY_GL_SHADER_PROGRAM_H
