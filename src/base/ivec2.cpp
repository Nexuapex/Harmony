//
// ivec2.cpp
// Harmony
//

#include <cmath>
#include <limits>

#include "ivec2.h"

namespace harmony {
	ivec2::ivec2() : x_(0L), y_(0L) {}
	ivec2::ivec2(icoord_t x, icoord_t y) : x_(x), y_(y) {}
	ivec2::ivec2(const ivec2 & that) : x_(that.x_), y_(that.y_) {}
	ivec2::ivec2(const vec2 & that)
		: x_(static_cast<icoord_t>(that.x()))
		, y_(static_cast<icoord_t>(that.y())) {}
	
	bool ivec2::operator==(const ivec2 & that) const {
		return x_ == that.x_ && y_ == that.y_;
	}
	
	bool ivec2::operator!=(const ivec2 & that) const {
		return !(*this == that);
	}
	
	ivec2 ivec2::operator+(const ivec2 & that) const {
		return ivec2(x_ + that.x_, y_ + that.y_);
	}
	
	ivec2 & ivec2::operator+=(const ivec2 & that) {
		x_ += that.x_;
		y_ += that.y_;
		return *this;
	}
	
	ivec2 ivec2::operator-(const ivec2 & that) const {
		return ivec2(x_ - that.x_, y_ - that.y_);
	}
	
	ivec2 & ivec2::operator-=(const ivec2 & that) {
		x_ -= that.x_;
		y_ -= that.y_;
		return *this;
	}
	
	ivec2 ivec2::operator*(const ivec2 & that) const {
		return ivec2(x_ * that.x_, y_ * that.y_);
	}
	
	ivec2 & ivec2::operator*=(const ivec2 & that) {
		x_ *= that.x_;
		y_ *= that.y_;
		return *this;
	}
	
	ivec2 ivec2::operator*(int scalar) const {
		return ivec2(x_ * scalar, y_ * scalar);
	}
	
	ivec2 & ivec2::operator*=(int scalar) {
		x_ *= scalar;
		y_ *= scalar;
		return *this;
	}
	
	ivec2 ivec2::operator/(const ivec2 & that) const {
		return ivec2(x_ / that.x_, y_ / that.y_);
	}
	
	ivec2 & ivec2::operator/=(const ivec2 & that) {
		x_ /= that.x_;
		y_ /= that.y_;
		return *this;
	}
	
	ivec2 ivec2::operator/(int scalar) const {
		return ivec2(x_ / scalar, y_ / scalar);
	}
	
	ivec2 & ivec2::operator/=(int scalar) {
		x_ /= scalar;
		y_ /= scalar;
		return *this;
	}
	
	ivec2::operator vec2() const {
		return vec2(static_cast<coord_t>(x_), static_cast<coord_t>(y_));
	}
	
	float ivec2::magnitude() const {
		return std::sqrt(static_cast<float>(magnitude_squared()));
	}
	
	const ivec2 ivec2::min(
		std::numeric_limits<icoord_t>::min(), 
		std::numeric_limits<icoord_t>::min()
	);
	
	const ivec2 ivec2::max(
		std::numeric_limits<icoord_t>::max(), 
		std::numeric_limits<icoord_t>::max()
	);
}
