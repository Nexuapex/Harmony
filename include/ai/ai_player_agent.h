//
// ai_player_agent.h
// Harmony
//

#ifndef HARMONY_AI_PLAYER_AGENT_H
#define HARMONY_AI_PLAYER_AGENT_H

#include "ivec2.h"
#include "ai_agent.h"

namespace harmony {
	namespace ai {
		// An agent that obtains input from the user and directs the actor.
		// There is only one of these, managed by the game engine. It also
		// keeps track of the camera bias (used to center the camera on the
		// actor) and the mouse position.
		class player_agent : public agent {
		public:
			// The position of the mouse, in window coordinates.
			ivec2 mouse_position() const;
			void set_mouse_position(const ivec2 & position);
			
			// The offset applied to the camera's position.
			ivec2 camera_bias() const;
			void set_camera_bias(const ivec2 & new_bias);
			
			// Advance game time for a given actor.
			void step(const game::actor_ref & actor, game::elapsed_t elapsed);
			
		private:
			ivec2 mouse_position_;
			ivec2 camera_bias_;
		};
	}
}

#endif // HARMONY_AI_PLAYER_AGENT_H
