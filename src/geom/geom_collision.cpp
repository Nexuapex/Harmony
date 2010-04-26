//
// geom_collision.cpp
// Harmony
//

#include "geom_collision.h"
#include "geom_shape.h"

namespace harmony {
	geom::collision::collision(const shape_ref & origin, const vec2 & displacement)
		: initial_(origin) , origin_(origin)
		, destination_(origin->translate(static_cast<ivec2>(displacement)))
		, displacement_(displacement) , ricochet_count_(16) {}
	
	geom::collision::~collision() {}
	
	geom::shape_ref geom::collision::origin() const {
		return origin_;
	}
	
	vec2 geom::collision::displacement() const {
		return displacement_;
	}
	
	geom::shape_ref geom::collision::destination() const {
		return destination_;
	}
	
	void geom::collision::apply_obstruction(const shape & obstruction) {
		apply_displacement(origin_->collision_displacement(*this, obstruction));
	}
	
	bool geom::collision::apply_collision() {
		if (ricochet_count_ > 0) {
			--ricochet_count_;
			return true;
		} else {
			return false;
		}
	}
	
	void geom::collision::apply_displacement(const vec2 & displacement) {
		if (displacement_ != displacement) {
			displacement_ = displacement;
			destination_ = origin_->translate(static_cast<ivec2>(displacement));
		}
	}
}
