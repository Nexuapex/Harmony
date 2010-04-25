//
// game_level.cpp
// Harmony
//

#include "game_level.h"
#include "game_terrain_layer.h"
#include "game_mark.h"
#include "game_actor.h"

namespace harmony {
	game::mark_ref game::level::create_mark(const vec2 & position) {
		mark_ref new_mark(new game::mark);
		new_mark->set_position(shared_from_this(), position);
		return new_mark;
	}
	
	game::size_t game::level::num_terrain_layers() const {
		return terrain_layers_.size();
	}
	
	game::terrain_layer & game::level::terrain_layer_at(unsigned index) const {
		return *terrain_layers_[index];
	}
	
	void game::level::add_terrain_layer(const terrain_layer_ref & layer) {
		terrain_layers_.push_back(layer);
	}
}
