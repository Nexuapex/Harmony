//
// ai_pathing_node.cpp
// Harmony
//

#include <limits>

#include "ai_pathing_node.h"
#include "ai_path.h"
#include "game_lattice.h"

#ifdef _WIN32
#undef min
#undef max
#endif

namespace harmony {
	ai::pathing_node::pathing_node(ai::path & path, const ivec2 & cell)
		: lattice_node(cell)
		, path_(&path)
		, step_(NULL)
		, distance_(std::numeric_limits<distance_t>::max())
		, heuristic_(path.heuristic_distance_from(cell)) {}
	
	ai::pathing_node * ai::pathing_node::adjacent(pathing_step_t step, bool create) const {
		return path_->lattice()->pathing_node_at(step->apply(cell()), *path_, create);
	}
	
	ai::pathing_node & ai::pathing_node::predecessor() const {
		return *adjacent(step_, false);
	}
	
	bool ai::pathing_node_less_predicate::operator()(pathing_node * a, pathing_node * b) {
		return *a < *b;
	}
}
