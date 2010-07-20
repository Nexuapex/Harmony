//
// ai_path.h
// Harmony
//

#ifndef HARMONY_AI_PATH_H
#define HARMONY_AI_PATH_H

#include <vector>
#include <boost/unordered_set.hpp>

#include "ai_types.h"
#include "ai_path_fwd.h"
#include "ai_pathing_node_fwd.h"
#include "game_lattice_fwd.h"
#include "game_actor_fwd.h"

namespace harmony {
	namespace ai {
		// Represents the state of a pathfinding algorithm.
		class path  {
		private:
			// Definition of a priority queue of node pointers.
			typedef std::vector<pathing_node *> open_set_type;
			
			// Definition of a set of node pointers.
			typedef boost::unordered_set<pathing_node *> closed_set_type;
			
		public:
			// Constructor/destructor.
			path(const game::lattice_ref & lattice, const ivec2 & initial, const ivec2 & goal);
			~path();
			
			// The default number of steps taken.
			unsigned steps_per_tick() const;
			void set_steps_per_tick(unsigned new_count);
			
			// The lattice that this path works within.
			const game::lattice_ref & lattice() const;
			
			// The destination node.
			const ivec2 & goal() const;
			
			// Heuristic function.
			distance_t heuristic_distance_from(const ivec2 & cell) const;
			
			// Makes a series of processing steps.
			void step(const game::actor_ref & actor, unsigned count = 0);
			
		private:
			// Make a single processing step.
			bool step_once(const game::actor_ref & actor);
			
			// Process a neighbor node.
			void process_adjacent(pathing_node * current, pathing_step_t step,
				pathing_node * adjacent);
			
		private:
			unsigned step_count_;
			game::lattice_ref lattice_;
			ivec2 goal_;
			pathing_node * goal_node_;
			open_set_type open_set_;
			closed_set_type closed_set_;
		};
	}
}

#endif // HARMONY_AI_PATH_H
