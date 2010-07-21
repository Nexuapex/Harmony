//
// lua_interface.cpp
// Harmony
//

#include "lua_interface.h"
#include "lua_engine.h"

namespace harmony {
	game::engine & lua::get_game_engine(lua_State * state) {
		// <engine context>
		lua_getfield(state, LUA_REGISTRYINDEX, engine_context_registry_key);
		
		// Get the engine pointer.
		void * context = lua_touserdata(state, -1);
		game::engine * engine = reinterpret_cast<game::engine *>(context);
		
		// empty stack
		lua_pop(state, 1);
		
		// Return the engine reference.
		return *engine;
	}
}
