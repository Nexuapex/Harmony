//
// game_lattice.cpp
// Harmony
//

#include <cmath>
#include <stdexcept>

#include "game_lattice.h"
#include "game_level.h"
#include "game_terrain_layer.h"

namespace harmony {
	game::lattice::lattice(const level_ref & level, game::size_t node_size)
		: level_(level)
		, node_size_(node_size)
	{
		const game::size_t num_layers = level->num_terrain_layers();
		
		if (num_layers == 0) {
			throw std::invalid_argument("no terrain layers associated with level");
		}
		
		// Boundary points.
		ivec2 min = ivec2::max, max = ivec2::min;
		
		// Find the extent of the lattice.
		for (unsigned index = 0; index < num_layers; index++) {
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
		nodes_ = new node_list[size_.x() * size_.y()];
	}
	
	game::lattice::~lattice() {
		delete [] nodes_;
	}
	
	game::level_ref game::lattice::level() const {
		return level_.lock();
	}
	
	game::size_t game::lattice::node_size() const {
		return node_size_;
	}
}
