//
// ai_pathing_step.cpp
// Harmony
//

#include <boost/math/constants/constants.hpp>

#include "ai_pathing_step.h"

namespace harmony {
	ai::pathing_step::pathing_step(const ivec2 & d, bool diag, pathing_step_t rev)
		: delta(d), diagonal(diag), reverse(rev), angle(d.arc_tangent())
		, cost(diag ? boost::math::constants::root_two<distance_t>() : 1.0f) {}
	
	namespace ai {
		const pathing_step pathing_steps[8] = {
			pathing_step(ivec2(+1,  0), false, &pathing_steps[4]),
			pathing_step(ivec2(+1, +1), true,  &pathing_steps[5]),
			pathing_step(ivec2( 0, +1), false, &pathing_steps[6]),
			pathing_step(ivec2(-1, +1), true,  &pathing_steps[7]),
			pathing_step(ivec2(-1,  0), false, &pathing_steps[0]),
			pathing_step(ivec2(-1, -1), true,  &pathing_steps[1]),
			pathing_step(ivec2( 0, -1), false, &pathing_steps[2]),
			pathing_step(ivec2(+1, -1), true,  &pathing_steps[3])
		};
	}
}
