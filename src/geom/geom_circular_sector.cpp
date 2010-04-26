//
// geom_circular_sector.cpp
// Harmony
//

#include <stdexcept>

#include "geom_binary_op.h"
#include "geom_circular_sector.h"
#include "geom_rect.h"

namespace harmony {
	geom::shape::kind_t geom::circular_sector::kind() const {
		return shape::circular_sector;
	}
	
	bool geom::circular_sector::intersects(const shape & that) const {
		switch (that.kind()) {
			case shape::circle:
				return intersects(static_cast<const geom::circle &>(that));
			case shape::circular_sector:
				return intersects(static_cast<const circular_sector &>(that));
			case shape::rect:
				return static_cast<const geom::rect &>(that).intersects(*this);
			case shape::binary_op:
				return static_cast<const geom::binary_op &>(that).intersects(*this);
			default:
				throw std::domain_error("intersection not defined");
		}
	}
	
	bool geom::circular_sector::intersects(const geom::circle & that) const {
		return intersects(static_cast<circular_sector>(that));
	}
	
	bool geom::circular_sector::intersects(const circular_sector & that) const {
		if (source.intersects(that.source)) {
			throw std::domain_error("intersection not defined");
		} else {
			return false;
		}
	}
}
