//
// game_level.h
// Harmony
//

#ifndef HARMONY_GAME_LEVEL_H
#define HARMONY_GAME_LEVEL_H

#include <boost/unordered_set.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iterator>
#include <vector>

#include "game_level_fwd.h"
#include "game_terrain_layer.h"
#include "game_mark.h"
#include "game_actor.h"

namespace harmony {
	namespace game {
		// A single game level.
		class level : public boost::enable_shared_from_this<level> {
		private:
			typedef boost::unordered_set<mark_ref> mark_set;
			
		public:
			// Creates a mark on this level at a given position.
			mark_ref create_mark(const vec2 & position);
			
			// The number of terrain layers associated with the level.
			size_t num_terrain_layers() const;
			
			// Get the terrain layer at a given index.
			terrain_layer & terrain_layer_at(unsigned index) const;
			
			// Add a new terrain layer to the level.
			void add_terrain_layer(const terrain_layer_ref & layer);
			
		public:
			// When a mark changes levels, it needs to be able to change the
			// levels' references to it.
			friend void mark::set_position(const level_ref & new_level, const vec2 & new_position);
			
		private:
			mark_set marks_;
			std::vector<terrain_layer_ref> terrain_layers_;
			
		public:
			// Iterates through actors attached to a given level.
			class actor_iterator : public std::iterator<std::forward_iterator_tag, actor_ref> {
			public:
				// Construction.
				actor_iterator() {}
				actor_iterator(const actor_iterator & that)
					: iter_(that.iter_), set_(that.set_) {}
				explicit actor_iterator(level & level)
					: iter_(level.marks_.begin()), set_(&level.marks_)
					{ advance_to_acceptable(); }
				actor_iterator & operator=(const actor_iterator & that) {
					if (this != &that) {
						iter_ = that.iter_;
						set_ = that.set_;
					}
					return *this;
				}
				
				// Advancing.
				actor_iterator & operator++() {
					++iter_;
					advance_to_acceptable();
					return *this;
				}
				actor_iterator operator++(int) {
					actor_iterator result = *this;
					++(*this);
					return result;
				}
				
				// Comparision.
				bool operator==(const actor_iterator & that) const {
					return this->iter_ == that.iter_;
				}
				bool operator!=(const actor_iterator & that) const {
					return !(*this == that);
				}
				
				// Value access.
				operator bool() const { return iter_ != set_->end(); }
				value_type operator*() const { return boost::dynamic_pointer_cast<actor>(*iter_); }
				value_type operator->() const { return **this; }
				
			private:
				void advance_to_acceptable() {
					while (iter_ != set_->end() && !acceptable()) ++iter_;
				}
				
				bool acceptable() const { return (*iter_)->is_actor(); }
				
			private:
				mark_set::iterator iter_;
				mark_set * set_;
			};
		};
	}
}

#endif // HARMONY_GAME_LEVEL_H
