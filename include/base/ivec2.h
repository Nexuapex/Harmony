//
// ivec2.h
// Harmony
//

#ifndef HARMONY_IVEC2_H
#define HARMONY_IVEC2_H

#include "types.h"
#include "vec2.h"

namespace harmony {
	// A vector containing two integral coordinates.
	class ivec2 {
	public:
		ivec2();
		ivec2(icoord_t x, icoord_t y);
		ivec2(const ivec2 & that);
		explicit ivec2(const vec2 & that);
		
		ivec2 operator+(const ivec2 & that) const;
		ivec2 & operator+=(const ivec2 & that);
		
		ivec2 operator-(const ivec2 & that) const;
		ivec2 & operator-=(const ivec2 & that);
		
		ivec2 operator*(const ivec2 & that) const;
		ivec2 & operator*=(const ivec2 & that);
		
		ivec2 operator*(int scalar) const;
		ivec2 & operator*=(int scalar);
		
		ivec2 operator/(const ivec2 & that) const;
		ivec2 & operator/=(const ivec2 & that);
		
		ivec2 operator/(int scalar) const;
		ivec2 & operator/=(int scalar);
		
		vec2 operator-() const { return (*this) * -1; }
		
		operator vec2() const;
		
		icoord_t x() const { return x_; }
		icoord_t y() const { return y_; }
		
		ucoord_t ux() const { return static_cast<ucoord_t>(x_); }
		ucoord_t uy() const { return static_cast<ucoord_t>(y_); }
		
		coord_t fx() const { return static_cast<coord_t>(x_); }
		coord_t fy() const { return static_cast<coord_t>(y_); }
		
		void set_x(icoord_t x) { x_ = x; }
		void set_y(icoord_t y) { y_ = y; }
		
		void incr_x() { ++x_; }
		void incr_y() { ++y_; }
		
		ucoord_t magnitude_squared() const { return x_ * x_ + y_ * y_; }
		float magnitude() const;
		
		vec2 unit() const { return static_cast<vec2>(*this).unit(); }
		angle_t arc_tangent() const { return static_cast<vec2>(*this).arc_tangent(); }
		
	private:
		icoord_t x_, y_;
	};
}

#endif // HARMONY_IVEC2_H
