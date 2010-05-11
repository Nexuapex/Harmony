//
// game_lattice_fwd.h
// Harmony
//

#ifndef HARMONY_GAME_LATTICE_FWD_H
#define HARMONY_GAME_LATTICE_FWD_H

#include <boost/shared_ptr.hpp>
#include <boost/intrusive/list.hpp>

#include "ivec2.h"

namespace harmony {
	namespace game {
		class lattice;
		typedef boost::shared_ptr<lattice> lattice_ref;
		
		// Base class for nodes that participate in a lattice.
		class lattice_node : public boost::intrusive::list_base_hook<> {
		public:
			// Constructors/destructors.
			lattice_node() {}
			explicit lattice_node(const ivec2 & cell) : cell_(cell) {}
			virtual ~lattice_node();
			
			// The node's current location in the lattice.
			ivec2 cell() const { return cell_; }
			
		protected:
			friend class lattice;
			
			// Setter.
			void set_cell(const ivec2 & new_cell) { cell_ = new_cell; }
			
		private:
			ivec2 cell_;
		};
	}
}

#endif // HARMONY_GAME_LATTICE_FWD_H
