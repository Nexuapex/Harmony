//
// ai_path.h
// Harmony
//

#ifndef HARMONY_AI_PATH_H
#define HARMONY_AI_PATH_H

#include <queue>
#include <vector>
#include <boost/unordered_set.hpp>

#include "ai_types.h"
#include "ai_path_fwd.h"
#include "ai_pathing_node_fwd.h"
#include "game_lattice_fwd.h"

namespace harmony {
	namespace ai {
		// Represents the state of a pathfinding algorithm.
		class path  {
		private:
			// Definition of a priority queue of node pointers.
			typedef std::priority_queue<
				pathing_node *,
				std::vector<pathing_node *>,
				pathing_node_less_predicate
			> open_set_type;
			
			// Definition of a set of node pointers.
			typedef boost::unordered_set<pathing_node *> closed_set_type;
			
		public:
			// Constructor/destructor.
			path(const game::lattice_ref & lattice, const ivec2 & initial, const ivec2 & destination);
			~path();
			
			// The default number of steps taken.
			unsigned steps_per_tick() const;
			void set_steps_per_tick(unsigned new_count);
			
			// The lattice that this path works within.
			const game::lattice_ref & lattice() const;
			
			// Heuristic function.
			distance_t heuristic_distance_from(const ivec2 & cell) const;
			
			// Makes a series of processing steps.
			void step(unsigned count = 0);
			
		private:
			// Make a single processing step.
			bool step_once();
			
		private:
			unsigned step_count_;
			game::lattice_ref lattice_;
			ivec2 destination_;
			open_set_type open_set_;
			closed_set_type closed_set_;
		};
	}
}

#endif // HARMONY_AI_PATH_H
