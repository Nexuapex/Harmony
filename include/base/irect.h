//
// irect.h
// Harmony
//

#ifndef HARMONY_IRECT_H
#define HARMONY_IRECT_H

#include "ivec2.h"

namespace harmony {
	struct irect {
		ivec2 origin, size;
		
		irect() {}
		irect(ivec2 o, ivec2 s) : origin(o), size(s) {}
		irect(icoord_t x, icoord_t y, ucoord_t width, ucoord_t height)
			: origin(ivec2(x, y)), size(ivec2(width, height)) {}
		
		icoord_t x1() const { return origin.x(); }
		icoord_t y1() const { return origin.y(); }
		icoord_t x2() const { return x1() + width(); }
		icoord_t y2() const { return y1() + height(); }
		ucoord_t width() const { return size.x(); }
		ucoord_t height() const { return size.y(); }
		
		bool intersects(const irect & that) const {
			return !(x1() > that.x2() || x2() < that.x1()
				|| y1() > that.y2() || y2() < that.y1());
		}
		
		irect intersect(const irect & that) const;
		
		irect tile_bounding_rect(ucoord_t tile_size) const;
	};
}

#endif // HARMONY_IRECT_H
