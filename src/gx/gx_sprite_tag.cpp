//
// gx_sprite_tag.cpp
// Harmony
//

#include <sstream>

#include "gx_sprite_tag.h"

namespace harmony {
	gx::sprite_tag::sprite_tag(const std::string & name, int priority, const animation_ref & animation)
		: name_(name), priority_(priority), animation_(animation) {}
	
	gx::sprite_tag::sprite_tag(const sprite_tag & that)
		: name_(that.name_), priority_(that.priority_), animation_(that.animation_) {}
	
	gx::sprite_tag & gx::sprite_tag::operator=(const sprite_tag & that) {
		if (this != &that) {
			name_ = that.name_;
			priority_ = that.priority_;
			animation_ = that.animation_;
		}
		return *this;
	}
	
	bool gx::sprite_tag::operator==(const sprite_tag & that) const {
		return priority_ == that.priority_ && name_ == that.name_;
	}
	
	bool gx::sprite_tag::operator!=(const sprite_tag & that) const {
		return !(*this == that);
	}
	
	bool gx::sprite_tag::operator<(const sprite_tag & that) const {
		if (priority_ != that.priority_)
			return priority_ < that.priority_;
		else
			return name_ < that.name_;
	}
	
	bool gx::sprite_tag::operator>(const sprite_tag & that) const {
		if (priority_ != that.priority_)
			return priority_ > that.priority_;
		else
			return name_ > that.name_;
	}
	
	bool gx::sprite_tag::operator<=(const sprite_tag & that) const {
		return !(*this > that);
	}
	
	bool gx::sprite_tag::operator>=(const sprite_tag & that) const {
		return !(*this < that);
	}
	
	std::string gx::sprite_tag::name() const {
		return name_;
	}
	
	int gx::sprite_tag::priority() const {
		return priority_;
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
