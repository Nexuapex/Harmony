//
// ai_player_agent_fwd.h
// Harmony
//

#ifndef HARMONY_AI_PLAYER_AGENT_FWD_H
#define HARMONY_AI_PLAYER_AGENT_FWD_H

#include <boost/shared_ptr.hpp>

#include "ai_agent_fwd.h"

namespace harmony {
	namespace ai {
		class player_agent;
		typedef boost::shared_ptr<player_agent> player_agent_ref;
	}
}

#endif // HARMONY_AI_PLAYER_AGENT_FWD_H
