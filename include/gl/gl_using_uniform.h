//
// gl_using_uniform.h
// Harmony
//

#ifndef HARMONY_GL_USING_UNIFORM_H
#define HARMONY_GL_USING_UNIFORM_H

#include "gl_library.h"
#include "gl_types.h"
#include "gl_color.h"
#include "gl_shader_program.h"
#include "gl_texture.h"

namespace harmony {
	namespace gl {
		// Tracks a shader uniform and its current value, sending updates to
		// OpenGL only when necessary.
		template <typename T>
		class using_uniform_base {
		public:
			// Child constructors should probably call update().
			using_uniform_base(const shader_program & shader,
				const char * uniform, const T & initial_value)
				: uniform_(shader.uniform_location(uniform))
				, value_(initial_value) {}
			
			// Update the uniform, checking if we actually need to first.
			void set(const T & new_value) {
				if (value_ != new_value) {
					value_ = new_value;
					update();
				}
			}
			
		protected:
			// Actually update the shader.
			virtual void update() const = 0;
			
			// Assignment operator to satisfy MSVC++.
			using_uniform_base & operator=(const using_uniform_base & that) {
				(void)that;
				return *this;
			}
			
		protected:
			const uniform_t uniform_;
			T value_;
		};
		
		// Generic specialization (casts to int_t).
		template <typename T>
		class using_uniform : public using_uniform_base<T> {
		public:
			using_uniform(const shader_program & shader,
				const char * uniform, const T & initial_value)
				: using_uniform_base<T>(shader, uniform, initial_value)
			{
				update();
			}
			
		protected:
			void update() const {
				glUniform1i(
					using_uniform_base<T>::uniform_,
					static_cast<int_t>(using_uniform_base<T>::value_)
				);
			}
		};
		
		// Color uniforms.
		template <>
		class using_uniform<color> : public using_uniform_base<color> {
		public:
			using_uniform(const shader_program & shader,
				const char * uniform, const color & initial_value)
				: using_uniform_base<color>(shader, uniform, initial_value)
			{
				update();
			}
			
		protected:
			void update() const {
				glUniform3f(uniform_, value_.r(), value_.g(), value_.b());
			}
		};
		
		// Texture uniforms.
		template <>
		class using_uniform<texture_ref> : public using_uniform_base<texture_ref> {
		public:
			using_uniform(const shader_program & shader,
				const char * uniform, const texture_ref & initial_value)
				: using_uniform_base<texture_ref>(shader, uniform, initial_value)
			{
				update();
			}
			
		protected:
			void update() const {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, value_->name());
				glUniform1i(uniform_, 0);
			}
		};
	}
}

#endif // HARMONY_GL_USING_UNIFORM_H
