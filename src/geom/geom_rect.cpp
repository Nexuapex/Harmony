//
// geom_rect.cpp
// Harmony
//

#include <algorithm>
#include <cmath>
#include <stdexcept>

#include "geom_rect.h"
#include "geom_binary_op.h"
#include "mathfunc.h"

namespace harmony {
	geom::shape::kind_t geom::rect::kind() const {
		return shape::rect;
	}
	
	bool geom::rect::intersects(const shape & that) const {
		switch (that.kind()) {
			case shape::circle:
				return intersects(static_cast<const geom::circle &>(that));
			case shape::circular_sector:
				return intersects(static_cast<const geom::circular_sector &>(that));
			case shape::rect:
				return intersects(static_cast<const rect &>(that));
			case shape::binary_op:
				return static_cast<const geom::binary_op &>(that).intersects(*this);
			default:
				throw std::domain_error("intersection not defined");
		}
	}
	
	bool geom::rect::intersects(const geom::circle & that) const {
		ivec2 closest = ivec2(
			clamp(that.x(), x1(), x2()),
			clamp(that.y(), y1(), y2())
		);
		
		return (that.origin - closest).magnitude_squared() < that.radius_squared();
	}
	
	bool geom::rect::intersects(const geom::circular_sector & that) const {
		(void)that;
		throw std::domain_error("intersection not defined");
	}
	
	bool geom::rect::intersects(const rect & that) const {
		return !(x1() > that.x2() || x2() < that.x1() || y1() > that.y2() || y2() < that.y1());
	}
	
	ivec2 geom::rect::collision_displacement(collision & collision, const shape & that) const {
		switch (that.kind()) {
			case shape::binary_op:
				return collision_displacement(collision, static_cast<const geom::binary_op &>(that));
			case shape::rect:
				return collision_displacement(collision, static_cast<const rect &>(that));
			default:
				throw std::domain_error("collision not defined");
		}
	}
	
	ivec2 geom::rect::collision_displacement(collision & collision, const geom::binary_op & that) const {
		collision.apply_displacement(collision_displacement(collision, *that.left));
		return collision_displacement(collision, *that.right);
	}
	
	ivec2 geom::rect::collision_displacement(collision & collision, const rect & that) const {
		// Get the initial displacement.
		vec2 displace = collision.displacement();
		
		if (collision.destination()->intersects(that) && collision.apply_collision()) {
			// Limit the x component of the displacement.
			if (displace.x() != 0) {
				displace.set_x((displace.x() > 0)
					? std::min(static_cast<coord_t>(that.x1() - x2()), displace.x())
					: std::max(static_cast<coord_t>(that.x2() - x1()), displace.x())
				);
			}
			
			// Limit the y component of the displacement.
			if (displace.y() != 0) {
				displace.set_y((displace.y() > 0)
					? std::min(static_cast<coord_t>(that.y1() - y2()), displace.y())
					: std::max(static_cast<coord_t>(that.y2() - y1()), displace.y())
				);
			}
		}
		
		// Return the final displacement.
		return static_cast<ivec2>(displace);
	}
	
	geom::shape_ref geom::rect::translate(const ivec2 & displacement) const {
		shape_ref new_shape(new rect(*this, displacement));
		return new_shape;
	}
	
	geom::rect geom::rect::intersect(const rect & that) const {
		if (intersects(that)) {
			ivec2 o(
				std::max(x1(), that.x1()),
				std::max(y1(), that.y1())
			);
			ivec2 s(
				std::min(x2(), that.x2()) - o.x(),
				std::min(y2(), that.y2()) - o.y()
			);
			return rect(o, s);
		} else {
			return rect();
		}
	}
	
	namespace geom {
		rect tile_aligned_bounding_rect(const rect & r, ucoord_t tile_size) {
			float size = static_cast<float>(tile_size);
			ivec2 o(
				static_cast<icoord_t>(std::floor(r.x1() / size)),
				static_cast<icoord_t>(std::floor(r.y1() / size))
			);
			ivec2 s(
				static_cast<icoord_t>(std::ceil(r.x2() / size) - o.x() + 1),
				static_cast<icoord_t>(std::ceil(r.y2() / size) - o.y() + 1)
			);
			return rect(o, s);
		}
	}
}
