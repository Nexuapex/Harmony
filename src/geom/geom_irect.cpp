//
// geom_irect.cpp
// Harmony
//

#include <algorithm>
#include <cmath>

#include "geom_irect.h"

namespace harmony {
	ivec2 geom::irect::center() const {
		return origin + size / 2;
	}
	
	ucoord_t geom::irect::area() const {
		return width() * height();
	}
	
	namespace geom {
		irect union_bounding_rect(const irect & a, const irect & b) {
			ivec2 o(
				std::min(a.x1(), b.x1()),
				std::min(a.y1(), b.y1())
			);
			ivec2 s(
				std::max(a.x2(), b.x2()) - o.x(),
				std::max(a.y2(), b.y2()) - o.y()
			);
			return irect(o, s);
		}
		
		irect cell_aligned_bounding_rect(const irect & r, ucoord_t cell_size) {
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
