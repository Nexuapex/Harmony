//
// lua_mark.h
// Harmony
//

#ifndef HARMONY_LUA_MARK_H
#define HARMONY_LUA_MARK_H

#include "lua_types.h"
#include "lua_engine.h"
#include "game_mark.h"
#include "game_actor.h"

namespace harmony {
	namespace lua {
		extern const char * mark_class;
		extern const char * actor_class;
		
		game::mark_ref to_mark(const engine & engine, index_t index);
		game::mark_ref * check_mark(const engine & engine, index_t index);
		game::actor_ref to_actor(const engine & engine, index_t index);
		game::mark_ref * check_actor(const engine & engine, index_t index);
		
		void register_mark_library(const engine & engine);
	}
}

#endif // HARMONY_LUA_MARK_H
