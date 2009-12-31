//
// vec2.h
// Harmony
//

#ifndef HARMONY_VEC2_H
#define HARMONY_VEC2_H

#include "types.h"

namespace harmony {
	// A vector containing two floating-point coordinates.
	class vec2 {
	public:
		vec2();
		vec2(coord_t x, coord_t y);
		vec2(const vec2 & that);
		
		vec2 operator+(const vec2 & that) const;
		vec2 & operator+=(const vec2 & that);
		
		vec2 operator-(const vec2 & that) const;
		vec2 & operator-=(const vec2 & that);
		
		vec2 operator*(float scalar) const;
		vec2 & operator*=(float scalar);
		
		coord_t x() const { return x_; }
		coord_t y() const { return y_; }
		
		void set_x(coord_t x) { x_ = x; }
		void set_y(coord_t y) { y_ = y; }
		
		void incr_x() { ++x_; }
		void incr_y() { ++y_; }
		
		vec2 unit() const;
		angle_t arc_tangent() const;
		
	private:
		coord_t x_, y_;
	};
	
	vec2 unit_from_angle(angle_t angle);
}

#endif // HARMONY_VEC2_H
