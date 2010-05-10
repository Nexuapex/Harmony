//
// mathfunc.h
// Harmony
//

#ifndef HARMONY_MATH_H
#define HARMONY_MATH_H

#include "types.h"

namespace harmony {
	icoord_t clamp(icoord_t value, icoord_t min, icoord_t max);
	coord_t clamp(coord_t value, coord_t min, coord_t max);
	icoord_t round(coord_t value);
	
	template <typename T>
	T signum(T value) {
		if (value == 0)
			return 0;
		else
			return (value < 0) ? T(-1) : T(1);
	}
}

#endif // HARMONY_MATH_H
