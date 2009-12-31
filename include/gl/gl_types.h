//
// gl_types.h
// Harmony
//

#ifndef HARMONY_GL_TYPES_H
#define HARMONY_GL_TYPES_H

#include "types.h"
#include "ivec2.h"
#include "gl_library.h"

namespace harmony {
	namespace gl {
		typedef ::GLint int_t;
		typedef ::GLuint uint_t;
		typedef ::GLfloat float_t;
		typedef ::GLenum enum_t;
		typedef ::GLsizei size_t;
		typedef float_t angle_t;
		typedef int_t uniform_t;
		typedef uint_t shader_t;
		typedef uint_t texture_t;
	}
}

#endif // HARMONY_GL_TYPES_H
