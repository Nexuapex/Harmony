//
// vec2.cpp
// Harmony
//

#include <cmath>
#include <boost/math/constants/constants.hpp>

#include "vec2.h"

namespace harmony {
	vec2::vec2() : x_(0.0f), y_(0.0f) {}
	vec2::vec2(coord_t x, coord_t y) : x_(x), y_(y) {}
	vec2::vec2(const vec2 & that) : x_(that.x_), y_(that.y_) {}
	
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
	
	vec2 vec2::operator*(float scalar) const {
		return vec2(x_ * scalar, y_ * scalar);
	}
	
	vec2 & vec2::operator*=(float scalar) {
		x_ *= scalar;
		y_ *= scalar;
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
		return std::sqrt(x_ * x_ + y_ * y_);
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
}
