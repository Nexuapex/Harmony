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
			collision(const shape_ref & object, const vec2 & displacement);
			virtual ~collision();
			
			shape_ref initial() const;
			
			vec2 displacement() const;
			void set_displacement(const vec2 & displacement);
			
			shape_ref object() const;
			void set_object(const shape_ref & object);
			
			shape_ref obstruction() const;
			void set_obstruction(const shape_ref & obstruction);
			
			shape_ref destination() const;
			
			virtual bool apply_collision();
			
			void resolve();
			
		private:
			shape_ref initial_, object_, destination_;
			shape_ref obstruction_;
			vec2 displacement_;
			unsigned ricochet_count_;
		};
	}
}

#endif // HARMONY_GEOM_COLLISION_H
