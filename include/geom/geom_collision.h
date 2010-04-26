//
// geom_collision.h
// Harmony
//

#ifndef HARMONY_GEOM_COLLISION_H
#define HARMONY_GEOM_COLLISION_H

#include "vec2.h"
#include "ivec2.h"
#include "geom_shape_fwd.h"

namespace harmony {
	namespace geom {
		class collision {
		public:
			collision(const shape_ref & origin, const vec2 & displacement);
			virtual ~collision();
			
			void apply_obstruction(const shape & obstruction);
			
			shape_ref origin() const;
			vec2 displacement() const;
			shape_ref destination() const;
			
			virtual bool apply_collision();
			void apply_displacement(const vec2 & displacement);
			
		private:
			shape_ref initial_, origin_, destination_;
			vec2 displacement_;
			unsigned ricochet_count_;
		};
	}
}

#endif // HARMONY_GEOM_COLLISION_H
