//
// gl_texture_cache.h
// Harmony
//

#ifndef HARMONY_GL_TEXTURE_CACHE_H
#define HARMONY_GL_TEXTURE_CACHE_H

#include <boost/weak_ptr.hpp>
#include <boost/unordered_map.hpp>

#include "gl_texture.h"

namespace harmony {
	namespace gl {
		// Maintains a weakly-referenced cache of textures.
		class texture_cache {
		private:
			typedef boost::weak_ptr<texture> texture_weak;
			typedef boost::unordered_map<std::string, texture_weak> cache_map;
			
		public:
			texture_ref get(const std::string & filename);
			
		private:
			cache_map cache_;
		};
	}
}

#endif // HARMONY_GL_TEXTURE_CACHE_H
