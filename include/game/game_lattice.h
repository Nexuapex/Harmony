//
// game_lattice.h
// Harmony
//

#ifndef HARMONY_GAME_LATTICE_H
#define HARMONY_GAME_LATTICE_H

#include <boost/intrusive/list.hpp>

#include "game_types.h"
#include "game_lattice_fwd.h"
#include "game_level_fwd.h"

namespace harmony {
	namespace game {
		// Base class for nodes that participate in a lattice.
		class lattice_node : public boost::intrusive::list_base_hook<> {
			
		};
		
		// Spatial partitioning, dividing a level into a lattice of nodes, each
		// of which can contain terrain tiles, actors, and/or pathing nodes.
		class lattice {
		private:
			typedef boost::intrusive::list<lattice_node> node_list;
			
		public:
			// Constructor/destructor.
			lattice(const level_ref & level, game::size_t node_size);
			~lattice();
			
			// The associated level.
			level_ref level() const;
			
			// The origin point of this lattice, in world coordinates.
			ivec2 origin() const { return origin_; }
			
			// The size of this layer, in cell coordinates.
			ivec2 size() const { return size_; }
			
			// The size, in pixels, of a node in this lattice.
			game::size_t node_size() const;
			
		protected:
			// Subscript operator to provide access to a cell.
			node_list & operator[](const ivec2 & cell) {
				return nodes_[cell.y() * size_.x() + cell.x()];
			}
			
			// The const version of the subscript operator.
			const node_list & operator[](const ivec2 & cell) const {
				return nodes_[cell.y() * size_.x() + cell.x()];
			}
			
		private:
			level_weak level_;
			ivec2 origin_, size_;
			game::size_t node_size_;
			node_list * nodes_;
		};
	}
}

#endif // HARMONY_GAME_LATTICE_H
