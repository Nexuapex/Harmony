//
// geom_shape.h
// Harmony
//

#ifndef HARMONY_GEOM_SHAPE_H
#define HARMONY_GEOM_SHAPE_H

#include <boost/shared_ptr.hpp>

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
			// Constructor/destructor.
			shape() {}
			virtual ~shape() {}
			
			// Type introspection.
			virtual kind_t kind() const = 0;
			
			// Tests if this shape intersects another shape.
			virtual bool intersects(const shape & that) const = 0;
		};
		
		typedef boost::shared_ptr<const shape> shape_ref;
	}
}

#endif // HARMONY_GEOM_SHAPE_H
