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
	
	vec2 geom::rect::center() const {
		return origin + static_cast<vec2>(size) / 2.0f;
	}
	
	ucoord_t geom::rect::area() const {
		return width() * height();
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
		vec2 closest = vec2(
			clamp(that.x(), x1(), x2()),
			clamp(that.y(), y1(), y2())
		);
		
		return (that.origin - closest).magnitude_squared() < static_cast<coord_t>(that.radius_squared());
	}
	
	bool geom::rect::intersects(const geom::circular_sector & that) const {
		(void)that;
		throw std::domain_error("intersection not defined");
	}
	
	bool geom::rect::intersects(const rect & that) const {
		return x1() < that.x2() && x2() > that.x1() && y1() < that.y2() && y2() > that.y1();
	}
	
	geom::shape_ref geom::rect::translate(const vec2 & displacement) const {
		shape_ref new_shape(new rect(*this, displacement));
		return new_shape;
	}
	
	geom::rect geom::rect::bounding_rect() const {
		return *this;
	}
	
	void geom::rect::resolve_collision(collision & collision) const {
		kind_t object = collision.object()->kind();
		kind_t obstruction = collision.obstruction()->kind();
		
		if (object == shape::rect && obstruction == shape::rect) {
			// rect hitting rect
			resolve_collision_rect_on_rect(collision);
		} else if (object == shape::binary_op) {
			// binop hitting rect
			collision.object()->resolve_collision(collision);
		} else if (obstruction == shape::binary_op) {
			// rect hitting binop
			collision.obstruction()->resolve_collision(collision);
		} else {
			throw std::domain_error("collision not defined");
		}
	}
	
	void geom::rect::resolve_collision_rect_on_rect(collision & collision) const {
		const rect obj = static_cast<const rect &>(*collision.destination());
		const rect & obs = static_cast<const rect &>(*collision.obstruction());
		
		// Get the motion displacement.
		vec2 displace = collision.displacement();
		coord_t dx = 0, dy = 0;
		
		if (obj.intersects(obs) && collision.apply_collision()) {
			// Minimum x plane.
			if (obs.x1() < obj.x1() && obj.x1() < obs.x2()) {
				dx = obs.x2() - obj.x1();
			}
			
			// Maximum x plane.
			if (obs.x1() < obj.x2() && obj.x2() < obs.x2()) {
				coord_t x = obs.x1() - obj.x2();
				if (std::abs(x) < std::abs(dx)) dx = x;
			}
			
			// Minimum y plane.
			if (obs.y1() < obj.y1() && obj.y1() < obs.y2()) {
				dy = obs.y2() - obj.y1();
			}
			
			// Maximum y plane.
			if (obs.y1() < obj.y2() && obj.y2() < obs.y2()) {
				coord_t y = obs.y1() - obj.y2();
				if (std::abs(y) < std::abs(dy)) dy = y;
			}
			
			// Shunt the object away with whichever change is smaller.
			if (std::abs(dx) < std::abs(dy)) {
				displace.set_x(displace.x() + dx);
			} else {
				displace.set_y(displace.y() + dy);
			}
		}
		
		// Apply the final displacement.
		collision.set_displacement(displace);
	}
	
	namespace geom {
		rect union_bounding_rect(const rect & a, const rect & b) {
			vec2 o(
				std::min(a.x1(), b.x1()),
				std::min(a.y1(), b.y1())
			);
			ivec2 s(
				static_cast<icoord_t>(std::max(a.x2(), b.x2()) - o.x()),
				static_cast<icoord_t>(std::max(a.y2(), b.y2()) - o.y())
			);
			return rect(o, s);
		}
		
		irect cell_aligned_bounding_rect(const rect & r, ucoord_t cell_size) {
			float size = static_cast<float>(cell_size);
			ivec2 o(
				static_cast<icoord_t>(std::floor(r.x1() / size)),
				static_cast<icoord_t>(std::floor(r.y1() / size))
			);
			ivec2 s(
				static_cast<icoord_t>(std::ceil(r.x2() / size) - o.x() + 1),
				static_cast<icoord_t>(std::ceil(r.y2() / size) - o.y() + 1)
			);
			return irect(o, s);
		}
	}
}
