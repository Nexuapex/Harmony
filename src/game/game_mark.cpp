//
// game_mark.cpp
// Harmony
//

#include "game_mark.h"
#include "game_level.h"

namespace harmony {
	game::mark::mark() {}
	game::mark::~mark() {}
	
	bool game::mark::is_mark() const {
		return !is_actor();
	}
	
	bool game::mark::is_actor() const {
		return false;
	}
	
	void game::mark::set_position(const vec2 & new_position) {
		set_position(level_, new_position);
	}
	
	void game::mark::set_position(const level_ref & new_level, const vec2 & new_position) {
		if (level_ != new_level) {
			// Prevent possible deallocations during the course of this method.
			mark_ref this_ref = shared_from_this();
			
			// If we formerly belonged to a level, remove that association.
			if (level_) level_->marks_.erase(this_ref);
			
			// Change the current level.
			level_ = new_level;
			
			// Associate ourselves with the new level.
			if (new_level) new_level->marks_.insert(this_ref);
		}
		
		// Update the position vector.
		if (new_level)
			position_ = new_position;
		else
			position_ = vec2();
	}
	
	void game::mark::remove_from_level() {
		set_position(level_ref(), vec2());
	}
}
