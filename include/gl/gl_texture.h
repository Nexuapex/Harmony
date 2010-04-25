//
// gl_texture.h
// Harmony
//

#ifndef HARMONY_GL_TEXTURE_H
#define HARMONY_GL_TEXTURE_H

#include <string>

#include "gl_types.h"
#include "gl_texture_fwd.h"

namespace harmony {
	namespace gl {
		// Represents a single OpenGL texture, which may or may not be loaded
		// into the OpenGL system proper.
		class texture {
		public:
			// Constructors.
			explicit texture(const std::string & filename);
			explicit texture(const ivec2 & size);
			~texture();
			
			// A reference to the texture itself, to be used with OpenGL calls.
			// Can optionally require the texture to be loaded first.
			texture_t name(bool require_loaded = true);
			
			// The full size of the texture, in pixels.
			ivec2 size() const;
			
			// On systems where texture dimensions are not necessarily powers of
			// 2, the image might not occupy the entire texture. When displaying
			// the full texture, filled_portion() describes the portion of the
			// texture, starting at (0, 0) and going to filled_size(), that
			// actually contains the image.
			ivec2 filled_size() const;
			vec2 filled_portion() const;
			
			// Load the texture coordinates representing the full extent of this
			// texture into the given array.
			void copy_tex_coords(quad_t & tex_coords) const;
			
			// Force the texture to be loaded into OpenGL. Has no effect if the
			// texture is already loaded.
			void load();
			
		private:
			texture_t name_;
			bool loaded_;
			ivec2 size_, filled_size_;
			void * data_;
		};
	}
}

#endif // HARMONY_GL_TEXTURE_H
