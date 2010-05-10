//
// geom_shape.h
// Harmony
//

#ifndef HARMONY_GEOM_SHAPE_H
#define HARMONY_GEOM_SHAPE_H

#include "vec2.h"
#include "geom_shape_fwd.h"
#include "geom_rect_fwd.h"
#include "geom_collision.h"

namespace harmony {
	namespace geom {
		// Abstract base class for all two-dimensional shapes.
		class shape {
		public:
			typedef enum {
				binary_op,
				circle,
				circular_sector,
				rect
			} kind_t;
			
		public:
			// Destructor.
			virtual ~shape() {}
			
			// Type introspection.
			virtual kind_t kind() const = 0;
			
			// Tests if this shape intersects another shape.
			virtual bool intersects(const shape & that) const = 0;
			
			// Translates the origin of the shape.
			virtual shape_ref translate(const vec2 & displacement) const = 0;
			
			// Rectangle that completely surrounds this shape.
			virtual geom::rect bounding_rect() const = 0;
			
			// Performs collision detection.
			virtual void resolve_collision(collision & collision) const = 0;
		};
	}
}

#endif // HARMONY_GEOM_SHAPE_H
