//
// game_engine.cpp
// Harmony
//

#include "game_engine.h"
#include "game.h"
#include "ai_player_agent.h"
#include "lua_vector.h"
#include "lua_level.h"
#include "lua_mark.h"
#include "lua_sprite.h"

namespace harmony {

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4355 )
#endif

	game::engine::engine() : lua_engine_(this), player_agent_(new ai::player_agent)
	{
		// Register Lua API functions.
		lua::register_vector_library(lua_engine_);
		lua::register_level_library(lua_engine_);
		lua::register_mark_library(lua_engine_);
		lua::register_sprite_library(lua_engine_);
		
		// DEMO: Load the initial level.
		current_level_ = lua::load_level(lua_engine_, "survival.lua");
		
		// DEMO: Set up the player's walking animation.
		gx::animated<float>::animation_ref walking_animation(new gx::animation<float>(1.0f, 3.0f, 5.0f));
		gx::sprite_tag walking_tag("walk", 0, walking_animation);
		
		// DEMO: Set up the player.
		actor_ref player;
		for (game::level::actor_iterator iter(*current_level_); iter; ++iter) player = *iter;
		set_followed_actor(player);
		player_agent_->set_speed(96.0f);
		player->set_agent(player_agent_);
		player->sprite_state().add_tag(walking_tag);
	}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

	game::level & game::engine::current_level() const {
		return *current_level_;
	}
	
	game::actor_ref game::engine::followed_actor() const {
		return followed_actor_;
	}
	
	void game::engine::set_followed_actor(const actor_ref & new_followed) {
		followed_actor_ = new_followed;
	}
	
	ivec2 game::engine::camera_origin() const {
		return static_cast<ivec2>(followed_actor()->position()) - camera_bias();
	}
	
	geom::rect game::engine::viewport() const {
		return geom::rect(
			camera_origin(),
			viewport_size()
		);
	}
	
	ivec2 game::engine::viewport_size() const {
		return player_agent_->viewport_size();
	}
	
	void game::engine::set_viewport_size(const ivec2 & new_size) {
		player_agent_->set_viewport_size(new_size);
	}
	
	ivec2 game::engine::camera_bias() const {
		return player_agent_->camera_bias();
	}
	
	void game::engine::set_camera_bias(const ivec2 & new_bias) {
		player_agent_->set_camera_bias(new_bias);
	}
	
	void game::engine::input_state_changed(bool_state_t state, bool new_value) {
		(void)state;
		(void)new_value;
	}
	
	ivec2 game::engine::mouse_position() const {
		return player_agent_->mouse_position();
	}
	
	void game::engine::set_mouse_position(const ivec2 & position) {
		player_agent_->set_mouse_position(position);
	}
	
	lua::engine & game::engine::lua_engine() {
		return lua_engine_;
	}
	
	gx::texture_cache & game::engine::texture_cache() {
		return texture_cache_;
	}
	
	gx::actor_renderer & game::engine::actor_renderer() {
		return actor_renderer_;
	}
	
	gx::atlas_renderer & game::engine::atlas_renderer() {
		return atlas_renderer_;
	}
	
	gx::tile_renderer & game::engine::tile_renderer() {
		return tile_renderer_;
	}
	
	ai::player_agent_ref game::engine::player_agent() const {
		return player_agent_;
	}
	
	void game::engine::step(game::elapsed_t elapsed) {
		for (game::level::actor_iterator iter(*current_level_); iter; ++iter)
			(*iter)->step(elapsed);
	}
}
