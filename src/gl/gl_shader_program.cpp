//
// gl_shader_program.cpp
// Harmony
//

#include <cstdlib>

#include "gl_shader_program.h"
#include "gl_library.h"
#include "plat_interface.h"

namespace harmony {
	static gl::shader_t load_shader(gl::shader_t program, gl::enum_t type, const std::string & filename) {
		// Create the shader.
		gl::shader_t shader = glCreateShader(type);
		
		// Copy over the source code.
		std::string path = "shader/" + filename;
		char * source = hplat_read_text_file(path.c_str());
		glShaderSource(shader, 1, const_cast<const char **>(&source), NULL);
		free(source);
		
		// Compile the shader.
		glCompileShader(shader);
		
		// Attach the shader to the program.
		glAttachShader(program, shader);
		
		// Return the new shader's index.
		return shader;
	}
	
	gl::shader_program::shader_program(const std::string & vertex, const std::string & fragment) {
		if (GLEE_VERSION_2_0) {
			// Create the program (manages the shaders).
			program_ = glCreateProgram();
			
			// Load both shaders.
			vertex_shader_ = load_shader(program_, GL_VERTEX_SHADER, vertex);
			fragment_shader_ = load_shader(program_, GL_FRAGMENT_SHADER, fragment);
			
			// Compile and link the shader program.
			glLinkProgram(program_);
		}
	}
	
	gl::shader_program::~shader_program() {
		if (fragment_shader_) {
			glDetachShader(program_, fragment_shader_);
			glDeleteShader(fragment_shader_);
		}
		
		if (vertex_shader_) {
			glDetachShader(program_, vertex_shader_);
			glDeleteShader(vertex_shader_);
		}
		
		if (program_) {
			glDeleteProgram(program_);
		}
	}
	
	gl::shader_t gl::shader_program::name() const {
		return program_;
	}
	
	gl::uniform_t gl::shader_program::uniform_location(const char * name) const {
		if (GLEE_VERSION_2_0)
			return glGetUniformLocation(program_, name);
		else
			return -1;
	}
}
