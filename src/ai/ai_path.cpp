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
		const ivec2 & goal)
		: step_count_(64)
		, lattice_(lattice)
		, goal_(goal)
		, goal_node_(NULL)
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
	
	const ivec2 & ai::path::goal() const {
		return goal_;
	}
	
	ai::distance_t ai::path::heuristic_distance_from(const ivec2 & cell) const {
		const icoord_t dx = std::abs(goal_.x() - cell.x());
		const icoord_t dy = std::abs(goal_.y() - cell.y());
		
		return (boost::math::constants::root_two<distance_t>() - 2.0f)
			* std::min(dx, dy) + dx + dy;
	}
	
	// Makes a series of processing steps.
	void ai::path::step(const game::actor_ref & actor, unsigned count) {
		unsigned remaining_steps = (count == 0) ? step_count_ : count;
		while (remaining_steps-- > 0 && !step_once(actor)) {}
	}
	
	// Make a single processing step.
	bool ai::path::step_once(const game::actor_ref & actor) {
		// If we're there, there's nothing to do.
		if (goal_node_) return true;
		
		// Pop the lowest node from the open set and move it to the closed set.
		pathing_node * const current = open_set_.top();
		open_set_.pop();
		current->set_closed(true);
		closed_set_.insert(current);
		
		// Check if the current node is the goal.
		if (current->cell() == goal_) {
			goal_node_ = current;
			return true;
		}
		
		// Loop through all adjacent nodes.
		for (unsigned index = 0; index < sizeof(pathing_steps) / sizeof(pathing_step); ++index) {
			// Get the adjacent cell.
			const pathing_step_t step = &pathing_steps[index];
			const ivec2 cell = current->adjacent_cell(step);
			
			// Check if the cell is passable. If so, process it.
			if (lattice_->node_passable_for(cell, actor)) {
				process_adjacent(current, step, lattice_->pathing_node_at(cell, *this, true));
			}
		}
		
		// Still more work to do.
		return false;
	}
	
	void ai::path::process_adjacent(pathing_node * current,
		pathing_step_t step, pathing_node * adjacent) 
	{
		// Cost to reach this node.
		distance_t cost = current->current_cost() + step->cost;
		
		// In the closed set if the node is marked as such.
		bool is_closed = adjacent->closed();
		
		// In the open set unless closed or new (no predecessor).
		bool is_open = !is_closed && adjacent->step() != NULL;
		
		// Check if this step leads to a shorter path.
		if (cost < adjacent->current_cost()) {
			if (is_open) {
				// This is where I need to remove the node from the open set,
				// no matter where it is. Neither STL nor Boost supply a
				// priority queue that can do this.
				is_open = false;
			} else {
				// Remove the node; we found a shorter path.
				closed_set_.erase(adjacent);
				adjacent->set_closed(false);
				is_closed = false;
			}
		}
		
		// If the node isn't in a set, add it to the open set.
		if (!is_open && !is_closed) {
			adjacent->set_step(step->reverse);
			adjacent->set_distance(cost);
			open_set_.push(adjacent);
		}
	}
}
