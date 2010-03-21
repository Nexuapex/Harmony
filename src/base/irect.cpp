//
// irect.cpp
// Harmony
//

#include <algorithm>
#include <cmath>

#include "irect.h"

namespace harmony {
	irect irect::intersect(const irect & that) const {
		if (intersects(that)) {
			ivec2 o(
				std::max(x1(), that.x1()),
				std::max(y1(), that.y1())
			);
			ivec2 s(
				std::min(x2(), that.x2()) - o.x(),
				std::min(y2(), that.y2()) - o.y()
			);
			return irect(o, s);
		} else {
			return irect();
		}
	}
	
	irect irect::tile_bounding_rect(ucoord_t tile_size) const {
		float size = static_cast<float>(tile_size);
		ivec2 o(
			static_cast<icoord_t>(std::floor(x1() / size)),
			static_cast<icoord_t>(std::floor(y1() / size))
		);
		ivec2 s(
			static_cast<icoord_t>(std::ceil(x2() / size) - o.x() + 1),
			static_cast<icoord_t>(std::ceil(y2() / size) - o.y() + 1)
		);
		return irect(o, s);
	}
}
