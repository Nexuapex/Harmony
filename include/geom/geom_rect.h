//
// geom_rect.h
// Harmony
//

#ifndef HARMONY_GEOM_RECT_H
#define HARMONY_GEOM_RECT_H

#include "ivec2.h"

namespace harmony {
	namespace geom {
		struct rect {
			ivec2 origin, size;
			
			rect() {}
			rect(ivec2 o, ivec2 s) : origin(o), size(s) {}
			rect(icoord_t x, icoord_t y, ucoord_t width, ucoord_t height)
				: origin(ivec2(x, y)), size(ivec2(width, height)) {}
			
			icoord_t x1() const { return origin.x(); }
			icoord_t y1() const { return origin.y(); }
			icoord_t x2() const { return x1() + width(); }
			icoord_t y2() const { return y1() + height(); }
			ucoord_t width() const { return size.x(); }
			ucoord_t height() const { return size.y(); }
			
			bool intersects(const rect & that) const {
				return !(x1() > that.x2() || x2() < that.x1()
					|| y1() > that.y2() || y2() < that.y1());
			}
			
			rect intersect(const rect & that) const;
			
			rect tile_bounding_rect(ucoord_t tile_size) const;
		};
	}
}

#endif // HARMONY_GEOM_RECT_H
