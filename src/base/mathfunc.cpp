//
// mathfunc.cpp
// Harmony
//

#include <algorithm>

#include "mathfunc.h"

namespace harmony {
	icoord_t clamp(icoord_t value, icoord_t min, icoord_t max) {
		if (min > max) std::swap(min, max);
		return std::max(min, std::min(max, value));
	}
	
	coord_t clamp(coord_t value, coord_t min, coord_t max) {
		if (min > max) std::swap(min, max);
		return std::max(min, std::min(max, value));
	}
	
	icoord_t round(coord_t value) {
		return static_cast<icoord_t>((value < 0) ? value - 0.5f : value + 0.5f);
	}
}
