//
// ai_pathing_node_fwd.h
// Harmony
//

#ifndef HARMONY_AI_PATHING_NODE_FWD_H
#define HARMONY_AI_PATHING_NODE_FWD_H

#include "ai_pathing_step.h"

namespace harmony {
	namespace ai {
		class pathing_node;
		
		// Defines a less-than predicate for pathing nodes.
		struct pathing_node_less_predicate {
			typedef pathing_node * first_argument_type;
			typedef pathing_node * second_argument_type;
			typedef bool result_type;
			
			bool operator()(pathing_node * a, pathing_node * b);
		};
	}
}

#endif // HARMONY_AI_PATHING_NODE_FWD_H
