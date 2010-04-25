//
// geom_rect.h
// Harmony
//

#ifndef HARMONY_GEOM_RECT_H
#define HARMONY_GEOM_RECT_H

#include "ivec2.h"
#include "geom_shape.h"
#include "geom_circle.h"
#include "geom_circular_sector.h"

namespace harmony {
	namespace geom {
		// A two-dimensional axis-aligned rectangle.
		class rect : public shape {
		public:
			rect() {}
			rect(const ivec2 & o, const ivec2 & s) : origin(o), size(s) {}
			rect(icoord_t x, icoord_t y, ucoord_t width, ucoord_t height)
				: origin(x, y), size(width, height) {}
			~rect() {}
			
			kind_t kind() const;
			
			icoord_t x1() const { return origin.x(); }
			icoord_t y1() const { return origin.y(); }
			icoord_t x2() const { return x1() + width(); }
			icoord_t y2() const { return y1() + height(); }
			ucoord_t width() const { return size.x(); }
			ucoord_t height() const { return size.y(); }
			
			bool intersects(const shape & that) const;
			bool intersects(const geom::circle & that) const;
			bool intersects(const geom::circular_sector & that) const;
			bool intersects(const rect & that) const;
			
			rect intersect(const rect & that) const;
			
		public:
			ivec2 origin, size;
		};
		
		rect tile_aligned_bounding_rect(const rect & r, ucoord_t tile_size);
	}
}

#endif // HARMONY_GEOM_RECT_H
