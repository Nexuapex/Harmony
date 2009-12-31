//
// ai_agent_fwd.h
// Harmony
//

#ifndef HARMONY_AI_AGENT_FWD_H
#define HARMONY_AI_AGENT_FWD_H

#include <boost/shared_ptr.hpp>

namespace harmony {
	namespace ai {
		class agent;
		typedef boost::shared_ptr<agent> agent_ref;
	}
}

#endif // HARMONY_AI_AGENT_FWD_H
