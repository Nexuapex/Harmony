//
// game_mark.h
// Harmony
//

#ifndef HARMONY_GAME_MARK_H
#define HARMONY_GAME_MARK_H

#include <boost/enable_shared_from_this.hpp>

#include "vec2.h"
#include "game_mark_fwd.h"
#include "game_level_fwd.h"

namespace harmony {
	namespace game {
		// An invisible, intangible point in the game world. Also the base
		// class of actors.
		class mark : public boost::enable_shared_from_this<mark> {
		public:
			// Constructor/destructor.
			mark();
			virtual ~mark();
			
			// Checking the dynamic type of the mark.
			bool is_mark() const;
			virtual bool is_actor() const;
			
			// Existence predicate.
			bool exists_in_level() const;
			
			// The level and position where this mark resides.
			level_ref level() const { return level_; }
			vec2 position() const { return position_; }
			
			// Change the position of the mark.
			void set_position(const vec2 & new_position);
			virtual void set_position(const level_ref & new_level, const vec2 & new_position);
			void remove_from_level();
			
		private:
			level_ref level_;
			vec2 position_;
		};
	}
}

#endif // HARMONY_GAME_MARK_H
