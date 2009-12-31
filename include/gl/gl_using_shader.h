//
// gl_using_shader.h
// Harmony
//

#ifndef HARMONY_GL_USING_SHADER_H
#define HARMONY_GL_USING_SHADER_H

#include "gl_library.h"
#include "gl_types.h"
#include "gl_color.h"
#include "gl_shader_program.h"
#include "gl_texture.h"

namespace harmony {
	namespace gl {
		// Activates an OpenGL shader program.
		class using_shader {
		public:
			using_shader(const shader_program & shader) : shader_program_(shader) {
				if (GLEE_VERSION_2_0)
					glUseProgram(shader.name());
			}
			
			~using_shader() {
				if (GLEE_VERSION_2_0)
					glUseProgram(0);
			}
			
			void set_uniform(const char * name, int_t value) const {
				set_uniform(shader_program_.uniform_location(name), value);
			}
			
			void set_uniform(const char * name, bool value) const {
				set_uniform(shader_program_.uniform_location(name), value);
			}
			
			void set_uniform(const char * name, texture & value) const {
				set_uniform(shader_program_.uniform_location(name), value);
			}
			
			void set_uniform(const char * name, const color & value) const {
				set_uniform(shader_program_.uniform_location(name), value);
			}
			
			void set_uniform(uniform_t location, int_t value) const {
				glUniform1i(location, value);
			}
			
			void set_uniform(uniform_t location, bool value) const {
				glUniform1i(location, static_cast<int_t>(value));
			}
			
			void set_uniform(uniform_t location, texture & value) const {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, value.name());
				set_uniform(location, 0);
			}
			
			void set_uniform(uniform_t location, const color & value) const {
				glUniform3f(location, value.r(), value.g(), value.b());
			}

		protected:
			// Assignment operator to satisfy MSVC++.
			using_shader & operator=(const using_shader & that) {
				(void)that;
				return *this;
			}
			
		private:
			const shader_program & shader_program_;
		};
	}
}

#endif // HARMONY_GL_USING_SHADER_H
