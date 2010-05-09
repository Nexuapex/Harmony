//
// game_level_fwd.h
// Harmony
//

#ifndef HARMONY_GAME_LEVEL_FWD_H
#define HARMONY_GAME_LEVEL_FWD_H

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace harmony {
	namespace game {
		class level;
		typedef boost::shared_ptr<level> level_ref;
		typedef boost::weak_ptr<level> level_weak;
	}
}

#endif // HARMONY_GAME_LEVEL_FWD_H
