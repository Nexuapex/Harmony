//
// game_lattice_fwd.h
// Harmony
//

#ifndef HARMONY_GAME_LATTICE_FWD_H
#define HARMONY_GAME_LATTICE_FWD_H

#include <boost/shared_ptr.hpp>

namespace harmony {
	namespace game {
		class lattice;
		typedef boost::shared_ptr<lattice> lattice_ref;
		
		class lattice_node;
	}
}

#endif // HARMONY_GAME_LATTICE_FWD_H
