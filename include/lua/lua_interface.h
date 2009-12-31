//
// lua_interface.h
// Harmony
//

#ifndef HARMONY_LUA_INTERFACE_H
#define HARMONY_LUA_INTERFACE_H

#include "game_engine.h"
#include "lua_library.h"

namespace harmony {
	namespace lua {
		game::engine & get_game_engine(lua_State * state);
	}
}

#endif
