//
// game_lattice.h
// Harmony
//

#ifndef HARMONY_GAME_LATTICE_H
#define HARMONY_GAME_LATTICE_H

#include <boost/scoped_array.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>

#include "game_types.h"
#include "game_lattice_fwd.h"
#include "game_level_fwd.h"
#include "game_terrain_layer_fwd.h"
#include "game_terrain_tile_fwd.h"
#include "geom_rect_fwd.h"
#include "game_actor.h"

namespace harmony {
	namespace game {
		// Spatial partitioning, dividing a level into a lattice of nodes, each
		// of which can contain terrain tiles, actors, and/or pathing nodes.
		class lattice {
		private:
			typedef boost::intrusive::list<lattice_node> node_list;
			
			// Used as part of the definition of collision_node_iterator.
			struct is_collision_node_predicate {
				bool operator()(const lattice_node & item) {
					return !!dynamic_cast<const actor::collision_node *>(&item);
				}
			};
			struct collision_node_cast_function {
				typedef actor_ref result_type;
				result_type operator()(const lattice_node & item) const {
					return static_cast<const actor::collision_node &>(item).actor();
				}
			};
			typedef boost::filter_iterator<is_collision_node_predicate,
				node_list::const_iterator> actor_filter_iterator;
			
		public:
			// Iterates through actors residing in a specific cell.
			typedef boost::transform_iterator<collision_node_cast_function,
				actor_filter_iterator> actor_iterator;
			
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
			ivec2 node_at(const vec2 & position) const;
			
			// The rectangle associated with a node (lattice coordinates).
			geom::rect node_rect(const ivec2 & cell) const;
			
			// The terrain tile at a given cell (lattice coordinates) for a
			// specific terrain layer. Returns the tile rect by reference.
			terrain_tile_ref tile_at(const ivec2 & cell,
				const terrain_layer & layer, geom::irect & tile_rect) const;
			
			// Iterating through collision nodes at a given cell.
			actor_iterator begin_actors_at(const ivec2 & cell) const;
			actor_iterator end_actors_at(const ivec2 & cell) const;
			
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
