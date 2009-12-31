//
// gl_texture_cache.cpp
// Harmony
//

#include "gl_texture_cache.h"

namespace harmony {
	gl::texture_ref gl::texture_cache::get(const std::string & filename) {
		{
			// Find an existing texture.
			cache_map::const_iterator ref = cache_.find(filename);
			
			// If the texture exists, then return it.
			if (ref != cache_.end() && !ref->second.expired())
				return ref->second.lock();
		}
		
		{
			// Otherwise, load the texture.
			texture_ref new_texture(new gl::texture(filename));
			texture_weak weak_ref(new_texture);
			
			// Insert it into the cache.
			cache_[filename] = weak_ref;
			
			// Return the new texture.
			return new_texture;
		}
	}
}
