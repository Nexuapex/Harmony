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
}
