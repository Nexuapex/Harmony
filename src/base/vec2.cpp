//
// vec2.cpp
// Harmony
//

#include <cmath>
#include <boost/math/constants/constants.hpp>

#include "vec2.h"
#include "ivec2.h"
#include "mathfunc.h"

namespace harmony {
	vec2::vec2() : x_(0.0f), y_(0.0f) {}
	vec2::vec2(coord_t x, coord_t y) : x_(x), y_(y) {}
	vec2::vec2(const vec2 & that) : x_(that.x_), y_(that.y_) {}
	
	bool vec2::operator==(const vec2 & that) const {
		return x_ == that.x_ && y_ == that.y_;
	}
	
	bool vec2::operator!=(const vec2 & that) const {
		return !(*this == that);
	}
	
	vec2 vec2::operator+(const vec2 & that) const {
		return vec2(x_ + that.x_, y_ + that.y_);
	}
	
	vec2 & vec2::operator+=(const vec2 & that) {
		x_ += that.x_;
		y_ += that.y_;
		return *this;
	}
	
	vec2 vec2::operator-(const vec2 & that) const {
		return vec2(x_ - that.x_, y_ - that.y_);
	}
	
	vec2 & vec2::operator-=(const vec2 & that) {
		x_ -= that.x_;
		y_ -= that.y_;
		return *this;
	}
	
	vec2 vec2::operator*(const vec2 & that) const {
		return vec2(x_ * that.x_, y_ * that.y_);
	}
	
	vec2 & vec2::operator*=(const vec2 & that) {
		x_ *= that.x_;
		y_ *= that.y_;
		return *this;
	}
	
	vec2 vec2::operator*(float scalar) const {
		return vec2(x_ * scalar, y_ * scalar);
	}
	
	vec2 & vec2::operator*=(float scalar) {
		x_ *= scalar;
		y_ *= scalar;
		return *this;
	}
	
	vec2 vec2::operator/(const vec2 & that) const {
		return vec2(x_ / that.x_, y_ / that.y_);
	}
	
	vec2 & vec2::operator/=(const vec2 & that) {
		x_ /= that.x_;
		y_ /= that.y_;
		return *this;
	}
	
	vec2 vec2::operator/(float scalar) const {
		return vec2(x_ / scalar, y_ / scalar);
	}
	
	vec2 & vec2::operator/=(float scalar) {
		x_ /= scalar;
		y_ /= scalar;
		return *this;
	}
	
	float vec2::magnitude() const {
		return std::sqrt(magnitude_squared());
	}
	
	ivec2 vec2::round() const {
		return ivec2(harmony::round(x_), harmony::round(y_));
	}
	
	vec2 vec2::unit() const {
		float magn = magnitude();
		return vec2(x_ / magn, y_ / magn);
	}
	
	angle_t vec2::arc_tangent() const {
		return std::atan2(y_, x_) * (180.0f / boost::math::constants::pi<float>());
	}
	
	vec2 unit_from_angle(angle_t angle) {
		const float deg_to_rad = boost::math::constants::pi<float>() / 180.0f;
		return vec2(std::cos(angle * deg_to_rad), std::sin(angle * deg_to_rad));
	}
	
	const vec2 vec2::min(
		std::numeric_limits<coord_t>::min(), 
		std::numeric_limits<coord_t>::min()
	);
	
	const vec2 vec2::max(
		std::numeric_limits<coord_t>::max(), 
		std::numeric_limits<coord_t>::max()
	);
}
