//
// geom_rect.cpp
// Harmony
//

#include <algorithm>
#include <cmath>
#include <stdexcept>

#include "geom_binary_op.h"
#include "geom_rect.h"
#include "mathfunc.h"

namespace harmony {
	geom::shape::kind_t geom::rect::kind() const {
		return shape::rect;
	}
	
	bool geom::rect::intersects(const shape & that) const {
		switch (that.kind()) {
			case shape::binary_op:
				return static_cast<const geom::binary_op &>(that).intersects(*this);
			case shape::circle:
				return intersects(static_cast<const geom::circle &>(that));
			case shape::circular_sector:
				return intersects(static_cast<const geom::circular_sector &>(that));
			case shape::rect:
				return intersects(static_cast<const rect &>(that));
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
