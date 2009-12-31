//
// gl_error.cpp
// Harmony
//

#include "gl_error.h"
#include "gl_types.h"
#include "gl_library.h"

namespace harmony {
	std::string gl::error() {
		enum_t err = glGetError();
		if (err == GL_NO_ERROR)
			return "";
		else
			return reinterpret_cast<const char *>(gluErrorString(err));
	}
}
