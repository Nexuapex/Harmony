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
			circular_sector(const circular_sector & c)
				: shape(c), source(c.source), angular_position(c.angular_position), central_angle(c.central_angle) {}
			circular_sector(const circular_sector & c, const vec2 & displacement)
				: source(c.source, displacement), angular_position(c.angular_position), central_angle(c.central_angle) {}
			circular_sector(const geom::circle & s)
				: source(s), angular_position(0), central_angle(360) {}
			circular_sector(const geom::circle & s, game::angle_t p, game::angle_t c)
				: source(s), angular_position(p), central_angle(c) {}
			circular_sector(coord_t x, coord_t y, ucoord_t r, game::angle_t p, game::angle_t c)
				: source(x, y, r), angular_position(p), central_angle(c) {}
			~circular_sector() {}
			
			kind_t kind() const;
			
			vec2 origin() const { return source.origin; }
			coord_t x() const { return source.x(); }
			coord_t y() const { return source.y(); }
			ucoord_t radius() const { return source.radius; }
			ucoord_t radius_squared() const { return source.radius_squared(); }
			
			bool intersects(const shape & that) const;
			bool intersects(const geom::circle & that) const;
			bool intersects(const circular_sector & that) const;
			
			shape_ref translate(const vec2 & displacement) const;
			geom::rect bounding_rect() const;
			
			void resolve_collision(collision & collision) const;
			
		public:
			geom::circle source;
			game::angle_t angular_position;
			game::angle_t central_angle;
		};
	}
}

#endif // HARMONY_GEOM_CIRCULAR_SECTOR_H
