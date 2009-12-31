//
// gx_animation.h
// Harmony
//

#ifndef HARMONY_GX_ANIMATION_H
#define HARMONY_GX_ANIMATION_H

#include <boost/shared_ptr.hpp>

#include "game_types.h"

namespace harmony {
	namespace gx {
		// Describes a single animation class.
		template <typename T>
		class animation {
		public:
			// Shared pointer type.
			typedef boost::shared_ptr< animation<T> > ref;
			
		public:
			// Creating an animation that transitions between two points.
			animation(const T & begin, const T & end, const T & speed)
				: begin_(begin), end_(end), speed_(speed) {}
			
			// The starting and ending points of the animation.
			T begin() const { return begin_; }
			T end() const { return end_; }
			
			// The speed factor of the animation.
			T speed() const { return speed_; }
			
		private:
			T begin_, end_, speed_;
		};
		
		// A variable that is animated.
		template <typename T>
		class animated {
		public:
			// Shared pointer type for the animation object.
			typedef typename animation<T>::ref animation_ref;
			
		public:
			// Construction.
			animated() {}
			explicit animated(const animation_ref & animation)
				: animation_(animation), value_(animation->begin()) {}
			animated(const animated<T> & that)
				: animation_(that.animation_), value_(that.value_) {}
			animated<T> & operator=(const animated<T> & that) {
				if (this != &that) {
					animation_ = that.animation_;
					value_ = that.value_;
				}
				return *this;
			}
			
			// True if the variable is connected to an animation.
			bool is_animated() const { return animation_; }
			
			// Advance the animation.
			void step(game::elapsed_t elapsed) {
				if (animation_) {
					// Get the ending value.
					const T end = animation_->end();
					
					// Advance the animation.
					value_ += (elapsed / 1000.0f) * animation_->speed();
					
					// Loop back to the beginning.
					while (value_ >= end) {
						value_ = value_ - end + animation_->begin();
					}
				}
			}
			
			// Obtaining the value.
			operator T() const { return value_; }
			
			// Obtaining the animation.
			animation_ref animation() const { return animation_; }
			
		private:
			animation_ref animation_;
			T value_;
		};
	}
}

#endif // HARMONY_GX_ANIMATION_H
