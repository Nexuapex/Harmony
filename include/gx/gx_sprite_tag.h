//
// gx_sprite_tag.h
// Harmony
//

#ifndef HARMONY_GX_SPRITE_TAG_H
#define HARMONY_GX_SPRITE_TAG_H

#include <string>

#include "game_types.h"
#include "gl_types.h"
#include "gx_animation.h"

namespace harmony {
	namespace gx {
		// A sprite tag is a single element that modifies a sprite.
		class sprite_tag {
		private:
			typedef animated<float>::animation_ref animation_ref;
			
		public:
			sprite_tag(const std::string & name, int priority,
				const animation_ref & animation = animation_ref());
			sprite_tag(const sprite_tag & that);
			sprite_tag & operator=(const sprite_tag & that);
			
			bool operator==(const sprite_tag & that) const;
			bool operator!=(const sprite_tag & that) const;
			bool operator< (const sprite_tag & that) const;
			bool operator<=(const sprite_tag & that) const;
			bool operator> (const sprite_tag & that) const;
			bool operator>=(const sprite_tag & that) const;
			
			std::string name() const;
			int priority() const;
			std::string animated_name() const;
			
			void step(game::elapsed_t elapsed);
			
		private:
			std::string name_;
			int priority_;
			animated<float> animation_;
		};
	}
}

#endif // HARMONY_GX_SPRITE_TAG_H
