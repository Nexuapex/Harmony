//
// ai_path.cpp
// Harmony
//

#include <algorithm>
#include <cmath>
#include <boost/math/constants/constants.hpp>

#include "ai_path.h"
#include "ai_pathing_node.h"
#include "game_lattice.h"

#ifdef _WIN32
#undef min
#undef max
#endif

namespace harmony {
	ai::path::path(const game::lattice_ref & lattice, const ivec2 & initial,
		const ivec2 & destination)
		: step_count_(64)
		, lattice_(lattice)
		, destination_(destination)
	{
		// Create the initial node.
		pathing_node * start = lattice->pathing_node_at(initial, *this, true);
		start->set_distance(0.0f);
		
		// Add the initial node to the open set.
		open_set_.push(start);
	}
	
	ai::path::~path() {
		// Remove all nodes in the open set.
		while (!open_set_.empty()) {
			lattice_->remove_pathing_node(open_set_.top()->cell(), *this);
			open_set_.pop();
		}
		
		// Remove all nodes in the closed set.
		for (closed_set_type::iterator iter = closed_set_.begin(); iter != closed_set_.end(); ++iter) {
			lattice_->remove_pathing_node((*iter)->cell(), *this);
		}
	}
	
	unsigned ai::path::steps_per_tick() const {
		return step_count_;
	}
	
	void ai::path::set_steps_per_tick(unsigned new_count) {
		if (new_count == 0)
			step_count_ = 1;
		else
			step_count_ = new_count;
	}
	
	const game::lattice_ref & ai::path::lattice() const {
		return lattice_;
	}
	
	ai::distance_t ai::path::heuristic_distance_from(const ivec2 & cell) const {
		const icoord_t dx = std::abs(destination_.x() - cell.x());
		const icoord_t dy = std::abs(destination_.y() - cell.y());
		
		return (boost::math::constants::root_two<distance_t>() - 2.0f)
			* std::min(dx, dy) + dx + dy;
	}
	
	// Makes a series of processing steps.
	void ai::path::step(unsigned count) {
		unsigned remaining_steps = (count == 0) ? step_count_ : count;
		while (remaining_steps-- > 0 && !step_once()) {}
	}
	
	// Make a single processing step.
	bool ai::path::step_once() {
		return false;
	}
}
