//
// geom_irect.h
// Harmony
//

#ifndef HARMONY_GEOM_IRECT_H
#define HARMONY_GEOM_IRECT_H

#include "ivec2.h"

namespace harmony {
	namespace geom {
		// A two-dimensional axis-aligned rectangle with integral coordinates.
		class irect {
		public:
			irect() {}
			irect(const irect & r)
				: origin(r.origin), size(r.size) {}
			irect(const irect & r, const ivec2 & displacement)
				: origin(r.origin + displacement), size(r.size) {}
			irect(const ivec2 & o, const ivec2 & s)
				: origin(o), size(s) {}
			irect(icoord_t x, icoord_t y, ucoord_t width, ucoord_t height)
				: origin(x, y), size(width, height) {}
			
			icoord_t x1() const { return origin.x(); }
			icoord_t y1() const { return origin.y(); }
			icoord_t x2() const { return x1() + width(); }
			icoord_t y2() const { return y1() + height(); }
			ucoord_t width() const { return size.x(); }
			ucoord_t height() const { return size.y(); }
			
			ivec2 center() const;
			ucoord_t area() const;
			
		public:
			ivec2 origin, size;
		};
		
		irect union_bounding_rect(const irect & a, const irect & b);
		irect cell_aligned_bounding_rect(const irect & r, ucoord_t cell_size);
	}
}

#endif // HARMONY_GEOM_IRECT_H
