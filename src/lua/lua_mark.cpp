//
// lua_mark.cpp
// Harmony
//

#include "lua_mark.h"
#include "lua_interface.h"
#include "lua_sprite.h"
#include "game.h"
#include "gx_sprite.h"

namespace harmony {
	const char * lua::mark_class = "mark";
	const char * lua::actor_class = "actor";
	
	const game::mark_ref mark_empty;
	const game::mark_ref actor_empty;
	
	game::mark_ref lua::to_mark(const engine & engine, index_t index) {
		return engine.to_proxy(mark_class, index, mark_empty);
	}
	
	game::mark_ref * lua::check_mark(const engine & engine, index_t index) {
		return reinterpret_cast<game::mark_ref *>(
			luaL_checkudata(engine, index, mark_class)
		);
	}
	
	game::actor_ref lua::to_actor(const engine & engine, index_t index) {
		return boost::dynamic_pointer_cast<game::actor>(
			engine.to_proxy(actor_class, index, actor_empty)
		);
	}
	
	game::mark_ref * lua::check_actor(const engine & engine, index_t index) {
		return reinterpret_cast<game::mark_ref *>(
			luaL_checkudata(engine, index, actor_class)
		);
	}
	
	static int mark_create_mark(lua_State * state) {
		game::engine & engine = lua::get_game_engine(state);
		
		// Create the mark object.
		game::mark_ref mark(new game::mark);
		
		// Create and return the userdata proxy.
		engine.lua_engine().push_proxy(lua::mark_class, mark);
		return 1;
	}
	
	static int mark_create_actor(lua_State * state) {
		game::engine & engine = lua::get_game_engine(state);
		
		// Create the actor object.
		game::mark_ref actor(new game::actor);
		
		// Create and return the userdata proxy.
		engine.lua_engine().push_proxy(lua::actor_class, actor);
		return 1;
	}
	
	static int mark_gc(lua_State * state) {
		game::engine & engine = lua::get_game_engine(state);
		
		// Call the destructor.
		lua::check_mark(engine.lua_engine(), 1)->~shared_ptr();
		return 0;
	}
	
	enum {
		actor_field_unknown = 0,
		actor_field_sprite = 1
	};
	
	static const char * actor_fields[] = {
		"",
		"sprite",
		NULL
	};
	
	static int actor_index(lua_State * state) {
		game::engine & engine = lua::get_game_engine(state);
		
		// Get the actor.
		game::actor_ref actor = boost::dynamic_pointer_cast<game::actor>(
			*lua::check_actor(engine.lua_engine(), 1)
		);
		
		// Check which field it is.
		if (lua_isstring(state, 2)) {
			switch (luaL_checkoption(state, 2, "", actor_fields)) {
				case actor_field_sprite:
					engine.lua_engine().push_sprite(actor->sprite());
					break;
				default:
					lua_pushnil(state);
					break;
			}
		} else {
			lua_pushnil(state);
		}
		
		return 1;
	}
	
	static int actor_newindex(lua_State * state) {
		game::engine & engine = lua::get_game_engine(state);
		
		// Get the actor.
		game::actor_ref actor = boost::dynamic_pointer_cast<game::actor>(
			*lua::check_actor(engine.lua_engine(), 1)
		);
		
		// Check which field it is.
		if (lua_isstring(state, 2)) {
			switch (luaL_checkoption(state, 2, "", actor_fields)) {
				case actor_field_sprite:
					actor->set_sprite(lua::to_sprite(engine.lua_engine(), 3));
					break;
			}
		}
		
		return 0;
	}
	
	static int actor_gc(lua_State * state) {
		game::engine & engine = lua::get_game_engine(state);
		
		// Call the destructor.
		lua::check_actor(engine.lua_engine(), 1)->~shared_ptr();
		return 0;
	}
	
	static luaL_Reg mark_library[] = {
		{"create_mark", mark_create_mark},
		{"create_actor", mark_create_actor},
		{NULL, NULL}
	};
	
	void lua::register_mark_library(const engine & engine) {
		// Register the Lua API.
		engine.register_library("object", mark_library);
		
		// Register the mark userdata type.
		if (engine.push_metatable(mark_class)) {
			// Garbage collection finalizer.
			lua_pushcfunction(engine, mark_gc);
			lua_setfield(engine, -2, "__gc");
		}
		lua_pop(engine, 1);
		
		// Register the actor userdata type.
		if (engine.push_metatable(actor_class)) {
			// Getter metamethod.
			lua_pushcfunction(engine, actor_index);
			lua_setfield(engine, -2, "__index");
			
			// Setter metamethod.
			lua_pushcfunction(engine, actor_newindex);
			lua_setfield(engine, -2, "__newindex");
			
			// Garbage collection finalizer.
			lua_pushcfunction(engine, actor_gc);
			lua_setfield(engine, -2, "__gc");
		}
		lua_pop(engine, 1);
	}
}
