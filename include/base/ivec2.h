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
		
		ivec2 operator+(const ivec2 & that) const;
		ivec2 & operator+=(const ivec2 & that);
		
		ivec2 operator-(const ivec2 & that) const;
		ivec2 & operator-=(const ivec2 & that);
		
		ivec2 operator*(int scalar) const;
		ivec2 & operator*=(int scalar);
		
		operator vec2() const;
		
		icoord_t x() const { return x_; }
		icoord_t y() const { return y_; }
		
		ucoord_t ux() const { return static_cast<ucoord_t>(x_); }
		ucoord_t uy() const { return static_cast<ucoord_t>(y_); }
		
		void set_x(icoord_t x) { x_ = x; }
		void set_y(icoord_t y) { y_ = y; }
		
		void incr_x() { ++x_; }
		void incr_y() { ++y_; }
		
		float magnitude() const;
		
	private:
		icoord_t x_, y_;
	};
}

#endif // HARMONY_IVEC2_H
