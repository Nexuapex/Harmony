//
// geom_circle.cpp
// Harmony
//

#include <stdexcept>

#include "geom_circle.h"
#include "geom_rect.h"

namespace harmony {
	geom::shape::kind_t geom::circle::kind() const {
		return shape::circle;
	}
	
	bool geom::circle::intersects(const shape & that) const {
		switch (that.kind()) {
			case shape::circle:
				return intersects(static_cast<const circle &>(that));
			case shape::rect:
				return static_cast<const geom::rect &>(that).intersects(*this);
			default:
				throw std::domain_error("intersection not defined");
		}
	}
	
	bool geom::circle::intersects(const circle & that) const {
		const coord_t radii = radius + that.radius;
		return (that.origin - origin).magnitude_squared() < radii * radii;
	}
}
