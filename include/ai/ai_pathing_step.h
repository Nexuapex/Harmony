//
// ai_pathing_step.h
// Harmony
//

#ifndef HARMONY_AI_PATHING_STEP_H
#define HARMONY_AI_PATHING_STEP_H

#include "ai_types.h"
#include "ivec2.h"

namespace harmony {
	namespace ai {
		// The value type that is passed around.
		struct pathing_step;
		typedef const pathing_step * pathing_step_t;
		
		// A cardinal or ordinal pathfinding direction.
		struct pathing_step {
		public:
			pathing_step(const ivec2 & d, bool diag, pathing_step_t rev);
			
			ivec2 apply(const ivec2 & cell) const {
				return cell + delta;
			}
			
		public:
			ivec2 delta;
			bool diagonal;
			pathing_step_t reverse;
			angle_t angle;
			distance_t cost;
		};
		
		// All the available directions.
		extern const pathing_step pathing_steps[8];
	}
}

#endif // HARMONY_AI_PATHING_STEP_H
