//
// gl_color.h
// Harmony
//

#ifndef HARMONY_GL_COLOR_H
#define HARMONY_GL_COLOR_H

#include "gl_types.h"

namespace harmony {
	namespace gl {
		// A color, without associated alpha value.
		class color {
		public:
			color();
			color(float_t r, float_t g, float_t b);
			
			float_t r() const { return r_; }
			float_t g() const { return g_; }
			float_t b() const { return b_; }
			
		private:
			float_t r_, g_, b_;
		};
	}
}

#endif // HARMONY_GL_COLOR_H
