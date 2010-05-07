//
// geom_collision.cpp
// Harmony
//

#include "geom_collision.h"
#include "geom_shape.h"

namespace harmony {
	geom::collision::collision(const shape_ref & object, const vec2 & displacement)
		: initial_(object), object_(object)
		, displacement_(displacement), ricochet_count_(16) {}
	
	geom::collision::~collision() {}
	
	geom::shape_ref geom::collision::initial() const {
		return initial_;
	}
	
	vec2 geom::collision::displacement() const {
		return displacement_;
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
		return object_->translate(static_cast<ivec2>(displacement_));
	}
	
	bool geom::collision::apply_collision() {
		if (ricochet_count_ > 0) {
			--ricochet_count_;
			return true;
		} else {
			return false;
		}
	}
	
	void geom::collision::resolve() {
		object_->resolve_collision(*this);
	}
}
