//
// ai_pathing_node.h
// Harmony
//

#ifndef HARMONY_AI_PATHING_NODE_H
#define HARMONY_AI_PATHING_NODE_H

#include "ai_types.h"
#include "ai_pathing_node_fwd.h"
#include "ai_path_fwd.h"
#include "game_lattice_fwd.h"

namespace harmony {
	namespace ai {
		// Represents a specific lattice cell within the pathfinding algorithm.
		class pathing_node : public game::lattice_node {
		public:
			// The path that this node is associated with.
			ai::path & path() const { return *path_; }
			
			// Step that points towards this node's predecessor.
			pathing_step_t step() const { return step_; }
			
			// Distances to the destination node.
			distance_t current_cost() const { return distance_; }
			distance_t estimated_remaining() const { return heuristic_; }
			distance_t estimated_cost() const { return distance_ + heuristic_; }
			
			// If this node is currently in the closed set.
			bool closed() const { return closed_; }
			
			// Gets an adjacent cell in the given direction.
			ivec2 adjacent_cell(pathing_step_t step) const {
				return step->apply(cell());
			}
			
			// Gets an adjacent node in the given direction.
			pathing_node * adjacent(pathing_step_t step, bool create = false) const;
			
			// The node's predecessor.
			pathing_node & predecessor() const;
			
		public:
			// Comparison operators. A node with a smaller estimated cost
			// is considered greater than its fellows.
			bool operator<(const pathing_node & that) const {
				return estimated_cost() > that.estimated_cost();
			}
			bool operator>(const pathing_node & that) const {
				return estimated_cost() < that.estimated_cost();
			}
			bool operator<=(const pathing_node & that) const {
				return !(*this > that);
			}
			bool operator>=(const pathing_node & that) const {
				return !(*this < that);
			}
			
		private:
			friend class game::lattice;
			friend class path;
			
			// Constructor.
			pathing_node(ai::path & path, const ivec2 & cell);
			
			// Setters.
			void set_path(ai::path & path) { path_ = &path; }
			void set_step(pathing_step_t step) { step_ = step; }
			void set_distance(distance_t distance) { distance_ = distance; }
			void set_closed(bool now_closed) { closed_ = now_closed; }
			
		private:
			ai::path * path_;
			pathing_step_t step_;
			distance_t distance_, heuristic_;
			bool closed_;
		};
	}
}

#endif // HARMONY_AI_PATHING_NODE_H
