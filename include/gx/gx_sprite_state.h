//
// gx_sprite_state.h
// Harmony
//

#ifndef HARMONY_GX_SPRITE_STATE_H
#define HARMONY_GX_SPRITE_STATE_H

#include <string>
#include <set>

#include "game_types.h"
#include "gx_sprite_fwd.h"
#include "gx_sprite_tag.h"

namespace harmony {
	namespace gx {
		// A sprite state keeps track of visual character elements. Not tied to
		// a sprite; you can change an actor's sprite without losing anything
		// in their sprite state.
		class sprite_state {
		public:
			void add_tag(const sprite_tag & tag);
			void remove_tag(const sprite_tag & tag);
			
			std::string path_for(const sprite & sprite) const;
			
			void step(game::elapsed_t elapsed);
			
		private:
			std::set<sprite_tag> tags_;
		};
	}
}

#endif // HARMONY_GX_SPRITE_STATE_H
