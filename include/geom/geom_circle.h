//
// geom_circle.h
// Harmony
//

#ifndef HARMONY_GEOM_CIRCLE_H
#define HARMONY_GEOM_CIRCLE_H

#include "vec2.h"
#include "geom_shape.h"

namespace harmony {
	namespace geom {
		// A two-dimensional circle.
		class circle : public shape {
		public:
			circle() : radius(0) {}
			circle(const circle & c)
				: shape(c), origin(c.origin), radius(c.radius) {}
			circle(const circle & c, const vec2 & displacement)
				: origin(c.origin + displacement), radius(c.radius) {}
			circle(const vec2 & o, ucoord_t r)
				: origin(o), radius(r) {}
			circle(coord_t x, coord_t y, ucoord_t r)
				: origin(x, y), radius(r) {}
			~circle() {}
			
			kind_t kind() const;
			
			coord_t x() const { return origin.x(); }
			coord_t y() const { return origin.y(); }
			ucoord_t radius_squared() const { return radius * radius; }
			
			bool intersects(const shape & that) const;
			bool intersects(const circle & that) const;
			
			shape_ref translate(const vec2 & displacement) const;
			geom::rect bounding_rect() const;
			
			void resolve_collision(collision & collision) const;
			
		public:
			vec2 origin;
			ucoord_t radius;
		};
	}
}

#endif // HARMONY_GEOM_CIRCLE_H
