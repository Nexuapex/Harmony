//
// geom_binary_op.cpp
// Harmony
//

#include <stdexcept>

#include "geom_binary_op.h"
#include "geom_rect.h"

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
	
	geom::shape_ref geom::binary_op::translate(const ivec2 & displacement) const {
		shape_ref new_shape(new binary_op(op, left->translate(displacement), right->translate(displacement)));
		return new_shape;
	}
	
	geom::rect geom::binary_op::bounding_rect() const {
		return union_bounding_rect(left->bounding_rect(), right->bounding_rect());
	}
	
	void geom::binary_op::resolve_collision(collision & collision) const {
		kind_t object = collision.object()->kind();
		kind_t obstruction = collision.obstruction()->kind();
		
		if (op != op_union) {
			throw std::domain_error("operation not defined");
		}
		
		if (object == shape::binary_op) {
			resolve_collision_as_object(collision);
		} else if (obstruction == shape::binary_op) {
			resolve_collision_as_obstruction(collision);
		} else {
			throw std::logic_error("misdispatched collision resolution");
		}
	}
	
	void geom::binary_op::resolve_collision_as_object(collision & collision) const {
		const binary_op & obj = static_cast<const binary_op &>(*collision.object());
		shape_ref obs = collision.obstruction();
		
		collision.set_object(obj.left);
		collision.object()->resolve_collision(collision);
		collision.set_object(obj.right);
		collision.object()->resolve_collision(collision);
	}
	
	void geom::binary_op::resolve_collision_as_obstruction(collision & collision) const {
		shape_ref obj = collision.object();
		const binary_op & obs = static_cast<const binary_op &>(*collision.obstruction());
		
		collision.set_obstruction(obs.left);
		obj->resolve_collision(collision);
		collision.set_obstruction(obs.right);
		obj->resolve_collision(collision);
	}
}
