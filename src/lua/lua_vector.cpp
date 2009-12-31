//
// lua_vector.cpp
// Harmony
//

#include "lua_vector.h"
#include "lua_interface.h"
#include "game.h"

namespace harmony {
	const char * lua::vec2_class = "vec2";
	const char * lua::ivec2_class = "ivec2";
	
	const vec2 vec2_empty;
	const ivec2 ivec2_empty;
	
	vec2 lua::to_vec2(const engine & engine, index_t index) {
		return engine.to_proxy(vec2_class, index, vec2_empty);
	}
	
	vec2 lua::check_vec2(const engine & engine, index_t index) {
		return *reinterpret_cast<vec2 *>(
			luaL_checkudata(engine, index, vec2_class)
		);
	}
	
	vec2 lua::opt_vec2(const engine & engine, index_t index, const vec2 & default_value) {
		return lua_isnoneornil(engine, index)
			? default_value : check_vec2(engine, index);
	}
	
	ivec2 lua::to_ivec2(const engine & engine, index_t index) {
		return engine.to_proxy(ivec2_class, index, ivec2_empty);
	}
	
	ivec2 lua::check_ivec2(const engine & engine, index_t index) {
		return *reinterpret_cast<ivec2 *>(
			luaL_checkudata(engine, index, ivec2_class)
		);
	}
	
	ivec2 lua::opt_ivec2(const engine & engine, index_t index, const ivec2 & default_value) {
		return lua_isnoneornil(engine, index)
			? default_value : check_ivec2(engine, index);
	}
	
	static int vec2_create(lua_State * state) {
		game::engine & engine = lua::get_game_engine(state);
		
		// Create the vector.
		coord_t x = static_cast<coord_t>(luaL_optnumber(state, 1, 0.0));
		coord_t y = static_cast<coord_t>(luaL_optnumber(state, 2, 0.0));
		vec2 vec(x, y);
		
		// Create and return the userdata proxy.
		engine.lua_engine().push_vector(vec);
		return 1;
	}
	
	static int ivec2_create(lua_State * state) {
		game::engine & engine = lua::get_game_engine(state);
		
		// Create the vector.
		icoord_t x = luaL_optinteger(state, 1, 0);
		icoord_t y = luaL_optinteger(state, 2, 0);
		ivec2 vec(x, y);
		
		// Create and return the userdata proxy.
		engine.lua_engine().push_vector(vec);
		return 1;
	}
	
	static luaL_Reg vector_library[] = {
		{"vec2", vec2_create},
		{"ivec2", ivec2_create},
		{NULL, NULL}
	};
	
	void lua::register_vector_library(const engine & engine) {
		// Register the Lua API.
		engine.register_library(NULL, vector_library);
		
		// Register the vec2 userdata type.
		if (engine.push_metatable(vec2_class)) {
			// Metamethods for vec2.
		}
		lua_pop(engine, 1);
		
		// Register the ivec2 userdata type.
		if (engine.push_metatable(ivec2_class)) {
			// Metamethods for ivec2.
		}
		lua_pop(engine.state(), 1);
	}
}
