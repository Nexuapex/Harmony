//
// geom_binary_op.cpp
// Harmony
//

#include <stdexcept>

#include "geom_binary_op.h"

namespace harmony {
	geom::shape::kind_t geom::binary_op::kind() const {
		return shape::binary_op;
	}
	
	bool geom::binary_op::intersects(const shape & that) const {
		switch (op) {
			case op_union:
				return left->intersects(that) || right->intersects(that);
			case op_intersection:
				return left->intersects(that) && right->intersects(that);
			case op_subtraction:
				return left->intersects(that) && !right->intersects(that);
			default:
				throw std::domain_error("operation not defined");
		}
	}
	
	ivec2 geom::binary_op::collision_displacement(collision & collision, const shape & that) const {
		collision.apply_displacement(left->collision_displacement(collision, that));
		return right->collision_displacement(collision, that);
	}
	
	geom::shape_ref geom::binary_op::translate(const ivec2 & displacement) const {
		shape_ref new_shape(new binary_op(op, left->translate(displacement), right->translate(displacement)));
		return new_shape;
	}
}
