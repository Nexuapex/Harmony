//
// gx_texture_cache.cpp
// Harmony
//

#include "gx_texture_cache.h"
#include "gx_texture.h"
#include "gl_texture.h"

namespace harmony {
	gx::texture_ref gx::texture_cache::get(const std::string & filename)
	{
		{
			// Find an existing texture.
			cache_map::const_iterator ref = cache_.find(filename);
			
			// If the texture exists, then return it.
			if (ref != cache_.end() && !ref->second.expired())
				return ref->second.lock();
		}
		
		{
			// Otherwise, load the texture.
			gl::texture_ref new_texture(new gl::texture(filename));
			texture_ref new_texture_wrapper(new gx::texture(new_texture));
			texture_weak weak_ref(new_texture_wrapper);
			
			// Insert it into the cache.
			cache_[filename] = weak_ref;
			
			// Return the new texture.
			return new_texture_wrapper;
		}
	}
}
