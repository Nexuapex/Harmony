//
// gl_texture_fwd.h
// Harmony
//

#ifndef HARMONY_GL_TEXTURE_FWD_H
#define HARMONY_GL_TEXTURE_FWD_H

#include <boost/shared_ptr.hpp>

namespace harmony {
	namespace gl {
		class texture;
		typedef boost::shared_ptr<texture> texture_ref;
	}
}

#endif // HARMONY_GL_TEXTURE_FWD_H
