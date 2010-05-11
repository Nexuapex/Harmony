//
// game_actor.h
// Harmony
//

#ifndef HARMONY_GAME_ACTOR_H
#define HARMONY_GAME_ACTOR_H

#include "glue.h"
#include "game_types.h"
#include "game_actor_fwd.h"
#include "game_mark.h"
#include "game_lattice_fwd.h"
#include "geom_irect.h"
#include "geom_shape_fwd.h"
#include "ai_agent_fwd.h"
#include "gx.h"

namespace harmony {
	namespace game {
		// An actor is a single renderable, mobile object in the game world.
		class actor : public mark {
		private:
			// The number of pixels by which to expand the borders of tiles for
			// the purpose of keeping them within the collision working set.
			static const icoord_t tile_collision_slop = 4;
			
		public:
			// Constructor/destructor.
			actor();
			~actor();
			
			// Checking the dynamic type of the actor.
			bool is_actor() const;
			
			// The current velocity of the actor.
			vec2 velocity() const;
			void set_velocity(const vec2 & new_velocity);
			
			// The current heading (facing) of the actor.
			angle_t heading() const;
			void set_heading(angle_t new_heading);
			
			// The collision shape used by this actor.
			geom::shape_ref collision_shape() const;
			void set_collision_shape(const geom::shape_ref & new_shape);
			
			// Considering this actor to be at the center of its lattice cell,
			// the pathing slop is the number of additional cells around it on
			// each side that must be reserved for the actor's bulk.
			const ivec2 & pathing_slop() const;
			
			// The agent attached to this actor.
			ai::agent_ref agent() const;
			void set_agent(const ai::agent_ref & new_agent);
			
			// The sprite used to render this actor.
			gx::sprite_ref sprite() const;
			void set_sprite(const gx::sprite_ref & new_sprite);
			
			// The sprite state used by this actor.
			gx::sprite_state & sprite_state();
			const gx::sprite_state & sprite_state() const;
			
			// Advancing game time.
			void step(elapsed_t elapsed);
			
			// Override mark::set_position().
			void set_position(const level_ref & new_level, const vec2 & new_position);
			
		protected:
			// Advancing the actor's movement.
			void movement_step(elapsed_t elapsed);
			
			// Handling collisions between actors and terrain. The passed shape
			// reference is always a rectangle, and is already translated to be
			// relative to the actor's collision shape.
			void collide(geom::collision & collision,
				const terrain_tile_ref & tile, const geom::irect & tile_rect);
			
			// Handling collisions between actors and other actors.
			void collide(geom::collision & collision, const actor_ref & actor);
			
		public:
			// Represents a specific cell of the actor within a lattice.
			class collision_node : public lattice_node {
			public:
				// The actor associated with this node.
 				actor_ref actor() const { return actor_; }
				
				// If this node is currently active (in the lattice) or not.
				bool active() const { return active_; }
				
			private:
				friend class actor;
				friend class lattice;
				
				// Constructor.
				collision_node() : active_(false) {}
				
				// Setters.
				void set_actor(const actor_ref & new_actor) { actor_ = new_actor; }
				void set_active(bool now_active) { active_ = now_active; }
				
			private:
				actor_ref actor_;
				bool active_;
			};
			
		private:
			// Get a pointer to the node in a specified array.
			static collision_node & collision_node_at(const ivec2 & cell,
				const boost::scoped_array<collision_node> & array,
				const geom::irect & context_rect)
			{
				return array[cell.y() * context_rect.width() + cell.x()];
			}
			
			// Get a pointer to the node in the current array.
			collision_node & collision_node_at(const ivec2 & cell) const
			{
				return collision_node_at(cell, collision_nodes_, collision_nodes_rect_);
			}
			
			// All collision nodes are offset by the negation of this.
			ivec2 collision_nodes_offset(lattice & lattice) const;
			
			// Updates the size of the array of collision nodes. If the size
			// changes, the list of old nodes is returned by reference.
			void update_collision_nodes_shape(boost::scoped_array<collision_node> & old_nodes);
			
			// Update the set of collision nodes and their connection to the lattice.
			void update_collision_nodes(bool should_update_shape, const level_ref & old_level = level_ref());
			
#ifdef HARMONY_DRAW_COLLISION_NODES
		public:
			// Used by the actor renderer to draw the collision nodes.
			ivec2 collision_nodes_size() const;
			bool collision_node_active_at(const ivec2 & cell) const;
			geom::rect collision_node_rect_at(const ivec2 & cell) const;
#endif // HARMONY_DRAW_COLLISION_NODES
			
		private:
			vec2 velocity_;
			angle_t heading_;
			geom::shape_ref collision_shape_;
			boost::scoped_array<collision_node> collision_nodes_;
			geom::irect collision_nodes_rect_;
			ivec2 pathing_slop_;
			ai::agent_ref agent_;
			gx::sprite_ref sprite_;
			gx::sprite_state sprite_state_;
		};
	}
}

#endif // HARMONY_GAME_ACTOR_H
