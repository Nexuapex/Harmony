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
}

#endif // HARMONY_MATH_H
