//
// gx_sprite.h
// Harmony
//

#ifndef HARMONY_GX_SPRITE_H
#define HARMONY_GX_SPRITE_H

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/unordered_set.hpp>

#include "gl_types.h"
#include "gl_texture.h"

namespace harmony {
	namespace gx {
		// A sprite is a class of textures that contribute to a single visual effect.
		class sprite {
		private:
			typedef boost::unordered_set<gl::texture_ref> cache_set;
			
		public:
			// Create a sprite.
			sprite(const std::string & name, const std::string & suffix,
				gl::size_t width, gl::size_t height);
			
			// The base name of the sprite.
			std::string name() const;
			
			// The path suffix of the sprite.
			std::string suffix() const;
			
			// The dimensions of the sprite.
			gl::size_t width() const;
			gl::size_t height() const;
			
			// The vertex array and texture coordinates of this sprite.
			const gl::float_t * vertices() const;
			const gl::float_t * tex_coords() const;
			
			// Lets a sprite know that a specific texture is representing it.
			// Used to populate the array of texture coordinates. Also keeps
			// the texture from being deallocated for an unspecified amount of
			// time (currently the lifespan of the sprite).
			void touch(const gl::texture_ref & texture);
			
		private:
			std::string name_, suffix_;
			gl::size_t width_, height_;
			gl::float_t vertices_[4][2];
			gl::float_t tex_coords_[4][2];
			cache_set texture_cache_;
		};
		
		typedef boost::shared_ptr<sprite> sprite_ref;
	}
}

#endif // HARMONY_GX_SPRITE_H
