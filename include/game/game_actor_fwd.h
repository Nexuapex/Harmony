//
// game_actor_fwd.h
// Harmony
//

#ifndef HARMONY_GAME_ACTOR_FWD_H
#define HARMONY_GAME_ACTOR_FWD_H

#include <boost/shared_ptr.hpp>

#include "game_mark_fwd.h"

namespace harmony {
	namespace game {
		class actor;
		typedef boost::shared_ptr<actor> actor_ref;
	}
}

#endif // HARMONY_GAME_ACTOR_FWD_H
