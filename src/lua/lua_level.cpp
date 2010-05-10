//
// lua_level.cpp
// Harmony
//

#include "lua_level.h"
#include "lua_interface.h"
#include "game.h"
#include "gl.h"

namespace harmony {
	const char * lua::terrain_tile_class = "terrain tile";
	
	const game::terrain_tile_ref terrain_tile_empty;
	
	game::terrain_tile_ref lua::to_terrain_tile(const engine & engine, index_t index) {
		return engine.to_proxy(terrain_tile_class, index, terrain_tile_empty);
	}
	
	game::terrain_tile_ref * lua::check_terrain_tile(const engine & engine, index_t index) {
		return reinterpret_cast<game::terrain_tile_ref *>(
			luaL_checkudata(engine, index, terrain_tile_class)
		);
	}
	
	static const char * tile_passable_options[] = {
		"impassable",
		"passable",
		NULL
	};
	
	static const char * tile_rotation_options[] = {
		"normal",
		"rotate right",
		"rotate 180",
		"rotate left",
		"flip",
		"flip rotate left",
		"flip rotate 180",
		"flip rotate right",
		NULL
	};
	
	static int terrain_create_tile(lua_State * state) {
		game::engine & engine = lua::get_game_engine(state);
		
		// Get the function's parameters.
		const char * filename = luaL_checkstring(state, 1);
		bool passable = luaL_checkoption(state, 2, "passable", tile_passable_options) != 0;
		gl::ushort_t rotation = static_cast<gl::ushort_t>(
			luaL_checkoption(state, 3, "normal", tile_rotation_options)
		);
		
		// Create the tile object.
		gx::texture_ref texture = engine.texture_cache().get(filename);
		game::terrain_tile_ref tile(new game::terrain_tile(passable, texture, rotation));
		
		// Create and return the userdata proxy.
		engine.lua_engine().push_proxy(lua::terrain_tile_class, tile);
		return 1;
	}
	
	static int terrain_tile_gc(lua_State * state) {
		game::engine & engine = lua::get_game_engine(state);
		
		// Call the destructor.
		lua::check_terrain_tile(engine.lua_engine(), 1)->~shared_ptr();
		return 0;
	}
	
	static luaL_Reg terrain_library[] = {
		{"create_tile", terrain_create_tile},
		{NULL, NULL}
	};
	
	void lua::register_level_library(const engine & engine) {
		// Register the Lua API.
		engine.register_library("terrain", terrain_library);
		
		// Register the terrain tile userdata type.
		if (engine.push_metatable(terrain_tile_class)) {
			// Garbage collection finalizer.
			lua_pushcfunction(engine, terrain_tile_gc);
			lua_setfield(engine, -2, "__gc");
		}
		lua_pop(engine, 1);
	}
}
