//
// gx_sprite_state.cpp
// Harmony
//

#include <algorithm>
#include <sstream>

#include "gx_sprite_state.h"
#include "gx_sprite.h"

namespace harmony {
	void gx::sprite_state::add_tag(const sprite_tag & tag) {
		tags_.insert(tag);
	}
	
	void gx::sprite_state::remove_tag(const sprite_tag & tag) {
		tags_.erase(tag);
	}
	
	std::string gx::sprite_state::path_for(const sprite & sprite) const {
		// The iterator type.
		typedef std::set<sprite_tag>::const_iterator iterator;
		
		// The buffer containing the output.
		std::stringstream path;
		
		// The texture's base name.
		path << sprite.name();
		
		// The names of each associated tag.
		for (iterator iter = tags_.begin(); iter != tags_.end(); ++iter)
			path << '/' << iter->animated_name();
		
		// The texture's path suffix.
		path << sprite.suffix();
		
		return path.str();
	}
	
	void gx::sprite_state::step(game::elapsed_t elapsed) {
		std::set<sprite_tag>::iterator iter = tags_.begin();
		
		// Rebuild the set of tags.
		while (iter != tags_.end()) {
			sprite_tag new_tag = *iter;
			new_tag.step(elapsed);
			tags_.erase(iter++);
			tags_.insert(new_tag);
		}
	}
}
