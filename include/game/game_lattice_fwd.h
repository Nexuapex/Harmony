//
// game_lattice_fwd.h
// Harmony
//

#ifndef HARMONY_GAME_LATTICE_FWD_H
#define HARMONY_GAME_LATTICE_FWD_H

#include <boost/shared_ptr.hpp>
#include <boost/intrusive/list.hpp>

namespace harmony {
	namespace game {
		class lattice;
		typedef boost::shared_ptr<lattice> lattice_ref;
		
		// Base class for nodes that participate in a lattice.
		class lattice_node : public boost::intrusive::list_base_hook<> {
		public:
			virtual ~lattice_node();
		};
	}
}

#endif // HARMONY_GAME_LATTICE_FWD_H
