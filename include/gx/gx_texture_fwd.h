//
// gx_texture_fwd.h
// Harmony
//

#ifndef HARMONY_GX_TEXTURE_FWD_H
#define HARMONY_GX_TEXTURE_FWD_H

#include <boost/shared_ptr.hpp>

#include "gl_texture.h"

namespace harmony {
	namespace gx {
		class texture;
		typedef boost::shared_ptr<texture> texture_ref;
	}
}

#endif // HARMONY_GX_TEXTURE_FWD_H
