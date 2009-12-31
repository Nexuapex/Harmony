//
// gx_sprite_tag.cpp
// Harmony
//

#include <sstream>

#include "gx_sprite_tag.h"

namespace harmony {
	gx::sprite_tag::sprite_tag(const std::string & name, const animation_ref & animation)
		: name_(name), animation_(animation) {}
	
	gx::sprite_tag::sprite_tag(const sprite_tag & that)
	: name_(that.name_), animation_(that.animation_) {}
	
	gx::sprite_tag & gx::sprite_tag::operator=(const sprite_tag & that) {
		if (this != &that) {
			name_ = that.name_;
			animation_ = that.animation_;
		}
		return *this;
	}
	
	bool gx::sprite_tag::operator==(const sprite_tag & that) const {
		return name_ == that.name_;
	}
	
	bool gx::sprite_tag::operator!=(const sprite_tag & that) const {
		return !(*this == that);
	}
	
	std::string gx::sprite_tag::name() const {
		return name_;
	}
	
	std::string gx::sprite_tag::animated_name() const {
		if (animation_.is_animated()) {
			std::stringstream result;
			result << name_ << static_cast<unsigned>(animation_);
			return result.str();
		} else {
			return name_;
		}
	}
	
	void gx::sprite_tag::step(game::elapsed_t elapsed) {
		animation_.step(elapsed);
	}
}
