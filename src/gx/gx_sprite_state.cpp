//
// gx_sprite_state.cpp
// Harmony
//

#include <algorithm>
#include <sstream>

#include "gx_sprite_state.h"

namespace harmony {
	void gx::sprite_state::add_tag(const sprite_tag & tag) {
		tags_.push_back(tag);
	}
	
	void gx::sprite_state::remove_tag(const sprite_tag & tag) {
		std::vector<sprite_tag>::iterator found = std::find(tags_.begin(), tags_.end(), tag);
		if (found != tags_.end())
			tags_.erase(found);
	}
	
	std::string gx::sprite_state::path_for(const sprite & sprite) const {
		std::stringstream path;
		
		// The texture's base name.
		path << sprite.name();
		
		// The names of each associated tag.
		for (unsigned index = 0; index < tags_.size(); ++index)
			path << '/' << tags_[index].animated_name();
		
		// The texture's path suffix.
		path << sprite.suffix();
		
		return path.str();
	}
	
	void gx::sprite_state::step(game::elapsed_t elapsed) {
		for (unsigned index = 0; index < tags_.size(); ++index)
			tags_[index].step(elapsed);
	}
}
