//
// gl_color.cpp
// Harmony
//

#include "gl_color.h"

namespace harmony {
	gl::color::color() : r_(0.0f), g_(0.0f), b_(0.0f) {}
	
	gl::color::color(float_t r, float_t g, float_t b) : r_(r), g_(g), b_(b) {}
}
