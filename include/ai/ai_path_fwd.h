//
// ai_path_fwd.h
// Harmony
//

#ifndef HARMONY_AI_PATH_FWD_H
#define HARMONY_AI_PATH_FWD_H

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace harmony {
	namespace ai {
		class path;
		typedef boost::shared_ptr<path> path_ref;
		typedef boost::weak_ptr<path> path_weak;
	}
}

#endif // HARMONY_AI_PATH_FWD_H
