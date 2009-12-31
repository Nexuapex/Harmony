//
// gl_texture.h
// Harmony
//

#ifndef HARMONY_GL_TEXTURE_H
#define HARMONY_GL_TEXTURE_H

#include <string>
#include <boost/shared_ptr.hpp>

#include "gl_types.h"

namespace harmony {
	namespace gl {
		// Represents a single OpenGL texture, which may or may not be loaded
		// into the OpenGL system proper.
		class texture {
		public:
			// Constructors.
			explicit texture(const std::string & filename);
			~texture();
			
			// A reference to the texture itself, to be used with OpenGL calls.
			// Can optionally require the texture to be loaded first.
			texture_t name(bool require_loaded = true);
			
			// The size of the texture, in pixels.
			size_t width() const;
			size_t height() const;
			
			// The area, from 0 to 1, of the texture that is actually filled
			// by the source image. May not be 1 on systems where texture
			// dimensions must be powers of 2.
			float_t width_ratio() const;
			float_t height_ratio() const;
			
			// Load the texture coordinates representing the full extent of this
			// texture into the given array.
			void load_tex_coords(float (& tex_coords)[4][2]) const;
			
			// Force the texture to be loaded into OpenGL. Has no effect if the
			// texture is already loaded.
			void load();
			
		private:
			texture_t name_;
			bool loaded_;
			size_t width_, height_;
			float_t width_ratio_, height_ratio_;
			void * data_;
		};
		
		typedef boost::shared_ptr<texture> texture_ref;
	}
}

#endif // HARMONY_GL_TEXTURE_H
