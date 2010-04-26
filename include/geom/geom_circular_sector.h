//
// geom_circular_sector.h
// Harmony
//

#ifndef HARMONY_GEOM_CIRCULAR_SECTOR_H
#define HARMONY_GEOM_CIRCULAR_SECTOR_H

#include "game_types.h"
#include "geom_shape.h"
#include "geom_circle.h"

namespace harmony {
	namespace geom {
		// A section of a two-dimensional circle.
		class circular_sector : public shape {
		public:
			circular_sector()
				: angular_position(0), central_angle(0) {}
			circular_sector(const geom::circle & s)
				: source(s), angular_position(0), central_angle(360) {}
			circular_sector(const geom::circle & s, game::angle_t p, game::angle_t c)
				: source(s), angular_position(p), central_angle(c) {}
			circular_sector(icoord_t x, icoord_t y, ucoord_t r, game::angle_t p, game::angle_t c)
				: source(x, y, r), angular_position(p), central_angle(c) {}
			~circular_sector() {}
			
			kind_t kind() const;
			
			ivec2 origin() const { return source.origin; }
			icoord_t x() const { return source.x(); }
			icoord_t y() const { return source.y(); }
			ucoord_t radius() const { return source.radius; }
			ucoord_t radius_squared() const { return source.radius_squared(); }
			
			bool intersects(const shape & that) const;
			bool intersects(const geom::circle & that) const;
			bool intersects(const circular_sector & that) const;
			
		public:
			geom::circle source;
			game::angle_t angular_position;
			game::angle_t central_angle;
		};
	}
}

#endif // HARMONY_GEOM_CIRCULAR_SECTOR_H
