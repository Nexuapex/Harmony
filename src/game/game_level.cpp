//
// game_level.cpp
// Harmony
//

#include "game_level.h"
#include "game_terrain_layer.h"
#include "game_mark.h"
#include "game_actor.h"
#include "game_lattice.h"

namespace harmony {
	game::mark_ref game::level::create_mark(const vec2 & position) {
		mark_ref new_mark(new game::mark);
		new_mark->set_position(shared_from_this(), position);
		return new_mark;
	}
	
	game::level::actor_iterator game::level::begin() const {
		return actor_iterator(actor_filter_iterator(marks_.cbegin(), marks_.cend()));
	}
	
	game::level::actor_iterator game::level::end() const {
		return actor_iterator(actor_filter_iterator(marks_.cend(), marks_.cend()));
	}
	
	game::size_t game::level::num_terrain_layers() const {
		return terrain_layers_.size();
	}
	
	game::terrain_layer & game::level::terrain_layer_at(unsigned index) const {
		return *terrain_layers_[index];
	}
	
	void game::level::add_terrain_layer(const terrain_layer_ref & layer) {
		lattice_.reset();
		terrain_layers_.push_back(layer);
	}
	
	game::lattice_ref game::level::lattice() {
		if (!lattice_) {
			lattice_ref new_lattice(new game::lattice(shared_from_this(), lattice_size));
			lattice_ = new_lattice;
		}
		
		return lattice_;
	}
}
