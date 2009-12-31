//
// gl_error.h
// Harmony
//

#ifndef HARMONY_GL_ERROR_H
#define HARMONY_GL_ERROR_H

#include <string>

namespace harmony {
	namespace gl {
		// Return the last OpenGL error message.
		std::string error();
	}
}

#endif // HARMONY_GL_ERROR_H
