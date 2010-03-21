//
// game_engine.h
// Harmony
//

#ifndef HARMONY_GAME_ENGINE_H
#define HARMONY_GAME_ENGINE_H

#include "game_types.h"
#include "game_level.h"
#include "game_actor_fwd.h"
#include "game_interface.h"
#include "lua_engine.h"
#include "gl_texture_cache.h"
#include "gx_actor_renderer.h"
#include "gx_tile_renderer.h"
#include "ai_player_agent_fwd.h"

namespace harmony {
	namespace game {
		// The engine is the main class. It manages pretty much everything.
		class engine {
		public:
			// Constructor.
			engine();
			
			// The current game level.
			level & current_level() const;
			
			// The actor being followed by the camera.
			actor_ref followed_actor() const;
			void set_followed_actor(const actor_ref & new_followed);
			
			// The viewable area.
			irect viewport() const;
			
			// The size of the viewable area.
			ivec2 viewport_size() const;
			void set_viewport_size(const ivec2 & new_size);
			
			// The offset applied to the camera's position.
			ivec2 camera_bias() const;
			void set_camera_bias(const ivec2 & bias);
			
			// Apply a boolean input state change (for example, a mouse click).
			void input_state_changed(bool_state_t state, bool new_value);
			
			// The position of the mouse, in window coordinates.
			ivec2 mouse_position() const;
			void set_mouse_position(const ivec2 & position);
			
			// The various subsystems.
			lua::engine & lua_engine();
			gl::texture_cache & texture_cache();
			gx::actor_renderer & actor_renderer();
			gx::tile_renderer & tile_renderer();
			ai::player_agent_ref player_agent() const;
			
			// Advance game time.
			void step(elapsed_t elapsed);
			
		private:
			lua::engine lua_engine_;
			gl::texture_cache texture_cache_;
			gx::actor_renderer actor_renderer_;
			gx::tile_renderer tile_renderer_;
			ai::player_agent_ref player_agent_;
			level_ref current_level_;
			actor_ref followed_actor_;
		};
	}
}

#endif // HARMONY_GAME_ENGINE_H
