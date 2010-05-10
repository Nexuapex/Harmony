//
// game_lattice.h
// Harmony
//

#ifndef HARMONY_GAME_LATTICE_H
#define HARMONY_GAME_LATTICE_H

#include <boost/scoped_array.hpp>

#include "game_types.h"
#include "game_lattice_fwd.h"
#include "game_level_fwd.h"
#include "geom_rect_fwd.h"
#include "game_actor.h"

namespace harmony {
	namespace game {
		// Spatial partitioning, dividing a level into a lattice of nodes, each
		// of which can contain terrain tiles, actors, and/or pathing nodes.
		class lattice {
		private:
			typedef boost::intrusive::list<lattice_node> node_list;
			
		public:
			// Constructor.
			lattice(const level_ref & level, game::size_t node_size);
			
			// The associated level.
			level_ref level() const;
			
			// The origin point of this lattice, in world coordinates.
			ivec2 origin() const { return origin_; }
			
			// The size of this layer, in cell coordinates.
			ivec2 size() const { return size_; }
			
			// The size, in pixels, of a node in this lattice.
			game::size_t node_size() const;
			
			// Translates world coordinates into lattice coordinates.
			ivec2 node_at(const ivec2 & position) const;
			
			// The rectangle associated with a node (lattice coordinates).
			geom::rect node_rect(const ivec2 & cell) const;
			
			// Updates one of an actor's associated collision nodes in the
			// lattice. Changes the node's activity and, if active, its position
			// (given in lattice coordinates).
			void set_collision_node_active(actor::collision_node & node,
				bool now_active, const ivec2 & new_cell);
			
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
			boost::scoped_array<node_list> nodes_;
		};
		
		// Comparison operators.
		bool operator==(const lattice_node & a, const lattice_node & b);
		bool operator!=(const lattice_node & a, const lattice_node & b);
	}
}

#endif // HARMONY_GAME_LATTICE_H
