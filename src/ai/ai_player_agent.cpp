//
// ai_player_agent.cpp
// Harmony
//

#include "vec2.h"
#include "ai_player_agent.h"
#include "game_actor.h"

namespace harmony {
	ivec2 ai::player_agent::mouse_position() const {
		return mouse_position_;
	}
	
	void ai::player_agent::set_mouse_position(const ivec2 & position) {
		mouse_position_ = position;
	}
	
	ivec2 ai::player_agent::camera_bias() const {
		return camera_bias_;
	}
	
	void ai::player_agent::set_camera_bias(const ivec2 & new_bias) {
		camera_bias_ = new_bias;
	}
	
	void ai::player_agent::step(const game::actor_ref & actor, game::elapsed_t elapsed) {
		// Standard agent update.
		agent::step(actor, elapsed);
		
		// Update the heading of the player.
		vec2 heading = mouse_position_ - camera_bias_;
		if (heading.x() != 0.0f || heading.y() != 0.0f)
			actor->set_heading(heading.arc_tangent());
		
		// Update the velocity of the player.
		set_velocity_instantly(actor);
	}
}
