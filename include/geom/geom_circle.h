//
// geom_circle.h
// Harmony
//

#ifndef HARMONY_GEOM_CIRCLE_H
#define HARMONY_GEOM_CIRCLE_H

#include "ivec2.h"
#include "geom_shape.h"

namespace harmony {
	namespace geom {
		// A two-dimensional circle.
		class circle : public shape {
		public:
			circle() : radius(0) {}
			circle(const ivec2 & o, ucoord_t r) : origin(o), radius(r) {}
			circle(icoord_t x, icoord_t y, ucoord_t r) : origin(x, y), radius(r) {}
			
			kind_t kind() const;
			
			icoord_t x() const { return origin.x(); }
			icoord_t y() const { return origin.y(); }
			ucoord_t radius_squared() const { return radius * radius; }
			
			bool intersects(const shape & that) const;
			bool intersects(const circle & that) const;
			
		public:
			ivec2 origin;
			ucoord_t radius;
		};
	}
}

#endif // HARMONY_GEOM_CIRCLE_H
