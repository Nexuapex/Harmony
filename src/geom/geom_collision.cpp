//
// geom_collision.cpp
// Harmony
//

#include "geom_collision.h"
#include "geom_shape.h"

namespace harmony {
	geom::collision::collision(const shape_ref & object, const vec2 & displacement)
		: object_(object), collision_count_(16), displacement_(displacement) {}
	
	geom::collision::~collision() {}
	
	vec2 geom::collision::displacement() const {
		if (collision_count_ > 0)
			return displacement_;
		else
			return vec2();
	}
	
	void geom::collision::set_displacement(const vec2 & displacement) {
		displacement_ = displacement;
	}
	
	geom::shape_ref geom::collision::object() const {
		return object_;
	}
	
	void geom::collision::set_object(const shape_ref & object) {
		object_ = object;
	}
	
	geom::shape_ref geom::collision::obstruction() const {
		return obstruction_;
	}
	
	void geom::collision::set_obstruction(const shape_ref & obstruction) {
		obstruction_ = obstruction;
	}
	
	geom::shape_ref geom::collision::destination() const {
		return object_->translate(displacement());
	}
	
	unsigned geom::collision::remaining_collisions() const {
		return collision_count_;
	}
	
	bool geom::collision::apply_collision() {
		if (collision_count_ > 0) {
			--collision_count_;
			return true;
		} else {
			return false;
		}
	}
	
	void geom::collision::resolve() {
		object_->resolve_collision(*this);
	}
}
