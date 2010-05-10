//
// geom_rect.h
// Harmony
//

#ifndef HARMONY_GEOM_RECT_H
#define HARMONY_GEOM_RECT_H

#include "vec2.h"
#include "geom_irect.h"
#include "geom_shape.h"
#include "geom_binary_op.h"
#include "geom_circle.h"
#include "geom_circular_sector.h"

namespace harmony {
	namespace geom {
		// A two-dimensional axis-aligned rectangle.
		class rect : public shape {
		public:
			rect() {}
			rect(const rect & r)
				: shape(r), origin(r.origin), size(r.size) {}
			explicit rect(const irect & r)
				: origin(r.origin), size(r.size) {}
			rect(const rect & r, const vec2 & displacement)
				: origin(r.origin + displacement), size(r.size) {}
			rect(const vec2 & o, const ivec2 & s)
				: origin(o), size(s) {}
			rect(coord_t x, coord_t y, ucoord_t width, ucoord_t height)
				: origin(x, y), size(width, height) {}
			~rect() {}
			
			kind_t kind() const;
			
			coord_t x1() const { return origin.x(); }
			coord_t y1() const { return origin.y(); }
			coord_t x2() const { return x1() + width(); }
			coord_t y2() const { return y1() + height(); }
			ucoord_t width() const { return size.x(); }
			ucoord_t height() const { return size.y(); }
			
			vec2 center() const;
			ucoord_t area() const;
			
			bool intersects(const shape & that) const;
			bool intersects(const geom::circle & that) const;
			bool intersects(const geom::circular_sector & that) const;
			bool intersects(const rect & that) const;
			
			shape_ref translate(const vec2 & displacement) const;
			rect bounding_rect() const;
			
			void resolve_collision(collision & collision) const;
			
		private:
			void resolve_collision_rect_on_rect(collision & collision) const;
			
		public:
			vec2 origin;
			ivec2 size;
		};
		
		rect union_bounding_rect(const rect & a, const rect & b);
		irect cell_aligned_bounding_rect(const rect & r, ucoord_t cell_size);
	}
}

#endif // HARMONY_GEOM_RECT_H
