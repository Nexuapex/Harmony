//
// geom_shape.h
// Harmony
//

#ifndef HARMONY_GEOM_SHAPE_H
#define HARMONY_GEOM_SHAPE_H

namespace harmony {
	namespace geom {
		// Abstract base class for all two-dimensional shapes.
		class shape {
		public:
			typedef enum {
				circle,
				rect
			} kind_t;
			
		public:
			// Type introspection.
			virtual kind_t kind() const = 0;
			
			// Tests if this shape intersects another shape.
			virtual bool intersects(const shape & that) const = 0;
		};
	}
}

#endif // HARMONY_GEOM_SHAPE_H
