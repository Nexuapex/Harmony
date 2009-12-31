//
// game_actor.h
// Harmony
//

#ifndef HARMONY_GAME_ACTOR_H
#define HARMONY_GAME_ACTOR_H

#include <boost/shared_ptr.hpp>

#include "game_types.h"
#include "game_mark.h"
#include "ai_agent_fwd.h"
#include "gx_animation.h"
#include "gx_sprite.h"
#include "gx_sprite_state.h"

namespace harmony {
	namespace game {
		// An actor is a single renderable, movable object in the game world.
		class actor : public mark {
		public:
			// Checking the dynamic type of the actor.
			bool is_actor() const;
			
			// The current velocity of the actor.
			vec2 velocity() const;
			void set_velocity(const vec2 & new_velocity);
			
			// The current heading (facing) of the actor.
			angle_t heading() const;
			void set_heading(angle_t new_heading);
			
			// The agent attached to this actor.
			ai::agent_ref agent() const;
			void set_agent(const ai::agent_ref & new_agent);
			
			// The sprite of this actor.
			gx::sprite_ref sprite() const;
			void set_sprite(const gx::sprite_ref & new_sprite);
			
			// The sprite state used by this actor.
			gx::sprite_state & sprite_state();
			const gx::sprite_state & sprite_state() const;
			
			// Advancing game time.
			void step(elapsed_t elapsed);
			
		private:
			vec2 velocity_;
			angle_t heading_;
			ai::agent_ref agent_;
			gx::sprite_ref sprite_;
			gx::sprite_state sprite_state_;
		};
		
		typedef boost::shared_ptr<actor> actor_ref;
	}
}

#endif // HARMONY_GAME_ACTOR_H
