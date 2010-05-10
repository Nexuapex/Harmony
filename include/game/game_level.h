//
// game_level.h
// Harmony
//

#ifndef HARMONY_GAME_LEVEL_H
#define HARMONY_GAME_LEVEL_H

#include <boost/unordered_set.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <vector>

#include "game_level_fwd.h"
#include "game_lattice_fwd.h"
#include "game_terrain_layer_fwd.h"
#include "game_mark_fwd.h"
#include "game_actor.h"

namespace harmony {
	namespace game {
		// A single game level.
		class level : public boost::enable_shared_from_this<level> {
		private:
			typedef boost::unordered_set<mark_ref> mark_set;
			
			// Used as part of the definition of actor_iterator.
			struct is_actor_predicate {
				bool operator()(const mark_ref & item) const {
					return item->is_actor();
				}
			};
			struct actor_cast_function {
				typedef actor_ref result_type;
				result_type operator()(const mark_ref & item) const {
					return boost::static_pointer_cast<actor>(item);
				}
			};
			typedef boost::filter_iterator<is_actor_predicate,
				mark_set::const_iterator> actor_filter_iterator;
			
		public:
			// Iterates through actors attached to a given level.
			typedef boost::transform_iterator<actor_cast_function,
				actor_filter_iterator> actor_iterator;
			
		public:
			// The size of the level's associated lattice. Doesn't have to be
			// constant, but it does have to be a factor of every terrain
			// layer's tile size.
			static const game::size_t lattice_size = 24;
			
		public:
			// Creates a mark on this level at a given position.
			mark_ref create_mark(const vec2 & position);
			
			// Iterating through the actors on this level.
			actor_iterator begin() const;
			actor_iterator end() const;
			
			// The number of terrain layers associated with the level.
			size_t num_terrain_layers() const;
			
			// Get the terrain layer at a given index.
			terrain_layer & terrain_layer_at(unsigned index) const;
			
			// Add a new terrain layer to the level.
			void add_terrain_layer(const terrain_layer_ref & layer);
			
			// Return the associated spatial lattice.
			lattice_ref lattice();
			
		public:
			// When a mark changes levels, it needs to be able to change the
			// levels' references to it.
			friend void mark::set_position(const level_ref & new_level, const vec2 & new_position);
			
		private:
			lattice_ref lattice_;
			mark_set marks_;
			std::vector<terrain_layer_ref> terrain_layers_;
			
			/*class actor_iterator : public std::iterator<std::forward_iterator_tag, actor_ref> {
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
			};*/
		};
	}
}

#endif // HARMONY_GAME_LEVEL_H
