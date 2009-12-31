//
// lua_level.h
// Harmony
//

#ifndef HARMONY_LUA_LEVEL_H
#define HARMONY_LUA_LEVEL_H

#include <string>

#include "lua_types.h"
#include "lua_engine.h"
#include "game_level.h"

namespace harmony {
	namespace lua {
		extern const char * terrain_tile_class;
		
		game::level_ref load_level(const engine & engine, const std::string & filename);
		
		game::terrain_tile_ref to_terrain_tile(const engine & engine, index_t index);
		game::terrain_tile_ref * check_terrain_tile(const engine & engine, index_t index);
		
		void register_level_library(const engine & engine);
	}
}

#endif // HARMONY_LUA_LEVEL_H
