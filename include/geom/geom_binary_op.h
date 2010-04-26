//
// geom_binary_op.h
// Harmony
//

#ifndef HARMONY_GEOM_BINARY_OP_H
#define HARMONY_GEOM_BINARY_OP_H

#include "geom_shape.h"

namespace harmony {
	namespace geom {
		// An operation applied to two other shapes.
		class binary_op : public shape {
		public:
			typedef enum {
				op_union,
				op_intersection,
				op_subtraction
			} op_t;
			
		public:
			binary_op() : op(op_union) {}
			binary_op(op_t o, shape_ref l, shape_ref r) : op(o), left(l), right(r) {}
			~binary_op() {}
			
			kind_t kind() const;
			
			bool intersects(const shape & that) const;
			
			ivec2 collision_displacement(collision & collision, const shape & that) const;
			
			shape_ref translate(const ivec2 & displacement) const;
			
		public:
			op_t op;
			shape_ref left, right;
		};
	}
}

#endif // HARMONY_GEOM_BINARY_OP_H
