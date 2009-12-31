//
// game_actor.cpp
// Harmony
//

#include "game_actor.h"
#include "ai_agent.h"

namespace harmony {
	bool game::actor::is_actor() const {
		return true;
	}
	
	vec2 game::actor::velocity() const {
		return velocity_;
	}
	
	void game::actor::set_velocity(const vec2 & new_velocity) {
		velocity_ = new_velocity;
	}
	
	game::angle_t game::actor::heading() const {
		return heading_;
	}
	
	void game::actor::set_heading(angle_t new_heading) {
		heading_ = new_heading;
	}
	
	ai::agent_ref game::actor::agent() const {
		return agent_;
	}
	
	void game::actor::set_agent(const ai::agent_ref & new_agent) {
		agent_ = new_agent;
	}
	
	gx::sprite_ref game::actor::sprite() const {
		return sprite_;
	}
	
	void game::actor::set_sprite(const gx::sprite_ref & new_sprite) {
		sprite_ = new_sprite;
	}
	
	gx::sprite_state & game::actor::sprite_state() {
		return sprite_state_;
	}
	
	const gx::sprite_state & game::actor::sprite_state() const {
		return sprite_state_;
	}
	
	void game::actor::step(elapsed_t elapsed) {
		// Invoke AI for this step.
		if (agent_) agent_->step(boost::dynamic_pointer_cast<actor>(shared_from_this()), elapsed);
		
		// Move the actor for this step.
		set_position(position() + (velocity_ * (elapsed / 1000.0f)));
	}
}
