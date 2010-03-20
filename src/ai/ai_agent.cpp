//
// ai_agent.cpp
// Harmony
//

#include "ai_agent.h"
#include "game_actor.h"

namespace harmony {
	ai::speed_t ai::agent::speed() const {
		return speed_;
	}
	
	void ai::agent::set_speed(speed_t new_speed) {
		speed_ = new_speed;
	}
	
	void ai::agent::step(const game::actor_ref & actor, game::elapsed_t elapsed) {
		(void)actor;
		(void)elapsed;
	}
	
	void ai::agent::set_velocity_instantly(const game::actor_ref & actor) const {
		actor->set_velocity(unit_from_angle(actor->heading()) * speed_);
	}
}
