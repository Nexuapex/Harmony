//
// geom_circle.cpp
// Harmony
//

#include <stdexcept>

#include "geom_binary_op.h"
#include "geom_circle.h"
#include "geom_circular_sector.h"
#include "geom_rect.h"

namespace harmony {
	geom::shape::kind_t geom::circle::kind() const {
		return shape::circle;
	}
	
	bool geom::circle::intersects(const shape & that) const {
		switch (that.kind()) {
			case shape::circle:
				return intersects(static_cast<const circle &>(that));
			case shape::circular_sector:
				return static_cast<const geom::circular_sector &>(that).intersects(*this);
			case shape::rect:
				return static_cast<const geom::rect &>(that).intersects(*this);
			case shape::binary_op:
				return static_cast<const geom::binary_op &>(that).intersects(*this);
			default:
				throw std::domain_error("intersection not defined");
		}
	}
	
	bool geom::circle::intersects(const circle & that) const {
		const ucoord_t radii = radius + that.radius;
		return (that.origin - origin).magnitude_squared() < static_cast<coord_t>(radii * radii);
	}
	
	geom::shape_ref geom::circle::translate(const vec2 & displacement) const {
		shape_ref new_shape(new circle(*this, displacement));
		return new_shape;
	}
	
	geom::rect geom::circle::bounding_rect() const {
		const coord_t r = static_cast<coord_t>(radius);
		return geom::rect(origin - vec2(r, r), ivec2(radius * 2, radius * 2));
	}
	
	void geom::circle::resolve_collision(collision & collision) const {
		(void)collision;
		throw std::domain_error("collision not defined");
	}
}
