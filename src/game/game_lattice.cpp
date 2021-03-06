//
// game_lattice.cpp
// Harmony
//

#include <cmath>
#include <stdexcept>

#include "game_lattice.h"
#include "game_level.h"
#include "game_terrain_tile.h"
#include "game_terrain_layer.h"
#include "ai_path.h"
#include "ai_pathing_node.h"

namespace harmony {
	game::lattice::lattice(const level_ref & level, game::size_t node_size)
		: level_(level), node_size_(node_size)
	{
		const game::size_t num_layers = level->num_terrain_layers();
		
		if (num_layers == 0) {
			throw std::invalid_argument("no terrain layers associated with level");
		}
		
		// Boundary points.
		ivec2 min = ivec2::max, max = ivec2::min;
		
		// Find the extent of the lattice.
		for (unsigned index = 0; index < num_layers; ++index) {
			const terrain_layer & layer = level->terrain_layer_at(index);
			
			// Check the layer's tile size.
			if (layer.tile_size() % node_size != 0) {
				throw std::domain_error("terrain layer does not align to lattice");
			}
			
			// Translate the layer boundaries into world coordinates.
			ivec2 layer_min = layer.cell_origin(layer.origin());
			ivec2 layer_max = layer.cell_origin(layer.origin() + layer.size());
			
			// Check if any of the coordinates are new extrema.
			if (layer_min.x() < min.x()) min.set_x(layer_min.x());
			if (layer_min.y() < min.y()) min.set_y(layer_min.y());
			if (layer_max.x() > max.x()) max.set_x(layer_max.x());
			if (layer_max.y() > max.y()) max.set_y(layer_max.y());
		}
		
		// Scale to the appropriate coordinate system.
		origin_.set_x(static_cast<icoord_t>(std::floor(min.fx() / node_size)) * node_size);
		origin_.set_y(static_cast<icoord_t>(std::floor(min.fy() / node_size)) * node_size);
		size_.set_x(static_cast<icoord_t>(std::ceil(max.fx() / node_size)) - origin_.x());
		size_.set_y(static_cast<icoord_t>(std::ceil(max.fy() / node_size)) - origin_.y());
		
		// Create the lattice.
		nodes_.reset(new node_list[size_.x() * size_.y()]);
	}
	
	game::level_ref game::lattice::level() const {
		return level_.lock();
	}
	
	game::size_t game::lattice::node_size() const {
		return node_size_;
	}
	
	ivec2 game::lattice::node_at(const vec2 & position) const {
		// Integer division doesn't necessarily truncate towards negative
		// infinity, so that needs to be corrected for negative coordinates.
		const float size = static_cast<float>(node_size_);
		return static_cast<ivec2>(
			vec2(std::floor(position.x() / size), std::floor(position.y() / size))
		);
	}
	
	geom::rect game::lattice::node_rect(const ivec2 & cell) const {
		const coord_t size = static_cast<coord_t>(node_size_);
		return geom::rect(cell.x() * size, cell.y() * size, node_size_, node_size_);
	}
	
	game::terrain_tile_ref game::lattice::tile_at(const ivec2 & cell,
		const terrain_layer & layer, geom::irect & tile_rect) const
	{
		// Translate the vector to the layer's origin point, scaled to world coordinates.
		ivec2 pt = cell * node_size_ + origin_ - layer.origin() * layer.tile_size();
		
		// Check the minimum boundary.
		if (pt.x() >= 0 && pt.y() >= 0) {
			// Scale the point to layer coordinates.
			pt /= layer.tile_size();
			
			// Check the maximum boundary.
			if (pt.x() < layer.size().x() && pt.y() < layer.size().y()) {
				// Found a tile.
				tile_rect = layer.cell_rect(pt);
				return layer.tile(pt);
			}
		}
		
		// Out of bounds.
		return terrain_tile_ref();
	}
	
	game::lattice::actor_iterator game::lattice::begin_actors_at(const ivec2 & cell) const {
		const node_list & list = (*this)[cell];
		return actor_iterator(actor_filter_iterator(list.cbegin(), list.cend()));
	}
	
	game::lattice::actor_iterator game::lattice::end_actors_at(const ivec2 & cell) const {
		const node_list & list = (*this)[cell];
		return actor_iterator(actor_filter_iterator(list.cend(), list.cend()));
	}
	
	ai::pathing_node * game::lattice::pathing_node_at(const ivec2 & cell,
		ai::path & path, bool create)
	{
		// If the cell doesn't exist, then there is no node there.
		if (!node_exists(cell))
			return NULL;
		
		// Get the list of nodes.
		node_list & list = (*this)[cell];
		
		// Try to find an existing node.
		typedef ai::pathing_node * ai_node;
		for (node_list::iterator iter = list.begin(); iter != list.end(); ++iter) {
			if (ai_node node = dynamic_cast<ai_node>(&(*iter))) {
				if (&(node->path()) == &path) {
					// Found it.
					return node;
				}
			}
		}
		
		if (create) {
			// Create a new node.
			ai_node new_node = new ai::pathing_node(path, cell);
			
			// Add it to the list.
			list.push_front(*new_node);
			
			// Return the new node.
			return new_node;
		} else {
			// No node was found.
			return NULL;
		}
	}
	
	void game::lattice::remove_pathing_node(const ivec2 & cell, ai::path & path) {
		// Get the list of nodes.
		node_list & list = (*this)[cell];
		
		// Search for the existing node.
		typedef const ai::pathing_node * ai_node;
		for (node_list::iterator iter = list.begin(); iter != list.end(); ++iter) {
			if (ai_node node = dynamic_cast<ai_node>(&(*iter))) {
				if (&(node->path()) == &path) {
					// Erase the node.
					list.erase(iter);
					
					// Delete the node.
					delete node;
					
					// Short-circuit.
					return;
				}
			}
		}
	}
	
	bool game::lattice::node_passable(const ivec2 & cell, const actor_ref & actor) const {
		// Cells that don't exist are impassable.
		if (!node_exists(cell))
			return false;
		
		// Various variables.
		geom::irect tile_rect;
		const level_ref lvl = level();
		const size_t num_layers = lvl->num_terrain_layers();
		
		// Search through all terrain tiles at that cell.
		for (unsigned index = 0; index < num_layers; ++index)
			if (terrain_tile_ref tile = tile_at(cell, lvl->terrain_layer_at(index), tile_rect))
				if (tile && !tile->passable())
					return false;
		
		// Get the list of nodes.
		const node_list & list = (*this)[cell];
		
		// Search through all nodes at that cell.
		typedef const actor::collision_node * collision;
		for (node_list::const_iterator iter = list.cbegin(); iter != list.cend(); ++iter)
			if (collision node = dynamic_cast<collision>(&(*iter)))
				if (node->actor() != actor)
					return false;
		
		// Found nothing blocking.
		return true;
	}
	
	bool game::lattice::node_passable_for(const ivec2 & cell, const actor_ref & actor) const {
		const ivec2 & slop = actor->pathing_slop();
		const icoord_t y_max = cell.y() + slop.y(), x_max = cell.x() + slop.x();
		
		// Check every cell around the given cell.
		for (ivec2 c = cell - slop; c.y() < y_max; c.incr_y())
			for (c.set_x(cell.x() - slop.x()); c.x() < x_max; c.incr_x())
				if (!node_passable(c, actor))
					return false;
		
		// Found nothing blocking.
		return true;
	}
	
	void game::lattice::set_collision_node_active(actor::collision_node & node,
		bool now_active, const ivec2 & new_cell)
	{
		// Check if the node needs to change cells.
		bool cell_changed = now_active && node.active() && node.cell() != new_cell;
		
		// Check if removing from a previous node is necessary.
		if (cell_changed || (node.active() && !now_active)) {
			(*this)[node.cell()].remove(node);
		}
		
		if (node_exists(new_cell)) {
			// Check if adding to a new node is necessary.
			if (cell_changed || (!node.active() && now_active)) {
				(*this)[new_cell].push_front(node);
			}
			
			// Change the node's properties.
			node.set_active(now_active);
			node.set_cell(new_cell);
		} else {
			// New cell is offscreen.
			node.set_active(false);
		}
	}
	
	bool game::operator==(const lattice_node & a, const lattice_node & b) {
		// Typedef for the node classes.
		typedef const actor::collision_node * collision;
		typedef const ai::pathing_node * ai_node;
		
		// Check if we're comparing two collision nodes.
		if (collision c = dynamic_cast<collision>(&a))
			if (collision d = dynamic_cast<collision>(&b))
				return c->actor() == d->actor() && c->cell() == d->cell();
		
		// Check if we're comparing two pathing nodes.
		if (ai_node c = dynamic_cast<ai_node>(&a))
			if (ai_node d = dynamic_cast<ai_node>(&b))
				return &(c->path()) == &(d->path()) && c->cell() == d->cell();
		
		// Not comparing two nodes of the same type.
		return false;
	}
	
	bool game::operator!=(const lattice_node & a, const lattice_node & b) {
		return !(a == b);
	}
	
	game::lattice_node::~lattice_node() {}
}
