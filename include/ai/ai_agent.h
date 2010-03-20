//
// ai_agent.h
// Harmony
//

#ifndef HARMONY_AI_AGENT_H
#define HARMONY_AI_AGENT_H

#include "ai_agent_fwd.h"
#include "ai_types.h"
#include "game_types.h"
#include "game_actor_fwd.h"

namespace harmony {
	namespace ai {
		// An agent directs the actions and provides the behaviors of the actor
		// or actors to which it is attached. An actor without an agent will
		// generally be entirely inert.
		class agent {
		public:
			// The speed at which attached actors move.
			speed_t speed() const;
			virtual void set_speed(speed_t new_speed);
			
			// Advance game time for a given actor.
			virtual void step(const game::actor_ref & actor, game::elapsed_t elapsed);
			
		protected:
			// Utility function to alter an actor's velocity, according to the
			// agent's speed and the actor's heading.
			void set_velocity_instantly(const game::actor_ref & actor) const;
			
		private:
			speed_t speed_;
		};
	}
}

#endif // HARMONY_AI_AGENT_H
