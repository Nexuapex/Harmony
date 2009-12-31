//
// ai_agent.h
// Harmony
//

#ifndef HARMONY_AI_AGENT_H
#define HARMONY_AI_AGENT_H

#include "ai_agent_fwd.h"
#include "ai_types.h"
#include "game_types.h"
#include "game_actor.h"

namespace harmony {
	namespace ai {
		// An agent directs the actions of an attached actor.
		class agent {
		public:
			// The speed at which the attached actor moves.
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
