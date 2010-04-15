//
// mathfunc.cpp
// Harmony
//

#include <algorithm>

#include "mathfunc.h"

namespace harmony {
	icoord_t clamp(icoord_t value, icoord_t min, icoord_t max) {
		return std::max(min, std::min(max, value));
	}
}
