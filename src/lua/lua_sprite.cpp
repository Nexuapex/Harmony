//
// lua_sprite.cpp
// Harmony
//

#include <string>

#include "lua_sprite.h"
#include "lua_interface.h"
#include "gl_types.h"
#include "gx_sprite.h"

namespace harmony {
	const char * lua::sprite_class = "sprite";
	
	const gx::sprite_ref sprite_empty;
	
	gx::sprite_ref lua::to_sprite(const engine & engine, index_t index) {
		return engine.to_proxy(sprite_class, index, sprite_empty);
	}
	
	gx::sprite_ref * lua::check_sprite(const engine & engine, index_t index) {
		return reinterpret_cast<gx::sprite_ref *>(
			luaL_checkudata(engine, index, sprite_class)
		);
	}
	
	static int sprite_create_sprite(lua_State * state) {
		game::engine & engine = lua::get_game_engine(state);
		
		// Create the sprite object.
		std::string name = luaL_checkstring(state, 1);
		std::string suffix = luaL_checkstring(state, 2);
		lua_Integer width = luaL_checkinteger(state, 3);
		lua_Integer height = luaL_optinteger(state, 4, width);
		gx::sprite_ref sprite(new gx::sprite(name, suffix, ivec2(width, height)));
		
		// Create and return the userdata proxy.
		engine.lua_engine().push_proxy(lua::sprite_class, sprite);
		return 1;
	}
	
	static int sprite_gc(lua_State * state) {
		game::engine & engine = lua::get_game_engine(state);
		
		// Call the destructor.
		lua::check_sprite(engine.lua_engine(), 1)->~shared_ptr();
		return 0;
	}
	
	static luaL_Reg sprite_library[] = {
		{"create_sprite", sprite_create_sprite},
		{NULL, NULL}
	};
	
	void lua::register_sprite_library(const engine & engine) {
		// Register the Lua API.
		engine.register_library("object", sprite_library);
		
		// Register the sprite userdata type.
		if (engine.push_metatable(sprite_class)) {
			// Garbage collection finalizer.
			lua_pushcfunction(engine, sprite_gc);
			lua_setfield(engine, -2, "__gc");
		}
		lua_pop(engine, 1);
	}
}
