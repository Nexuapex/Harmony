//
// geom_rect.cpp
// Harmony
//

#include <algorithm>
#include <cmath>

#include "geom_rect.h"

namespace harmony {
	geom::rect geom::rect::intersect(const geom::rect & that) const {
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
	
	geom::rect geom::rect::tile_bounding_rect(ucoord_t tile_size) const {
		float size = static_cast<float>(tile_size);
		ivec2 o(
			static_cast<icoord_t>(std::floor(x1() / size)),
			static_cast<icoord_t>(std::floor(y1() / size))
		);
		ivec2 s(
			static_cast<icoord_t>(std::ceil(x2() / size) - o.x() + 1),
			static_cast<icoord_t>(std::ceil(y2() / size) - o.y() + 1)
		);
		return rect(o, s);
	}
}
