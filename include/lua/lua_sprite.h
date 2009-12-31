//
// lua_sprite.h
// Harmony
//

#ifndef HARMONY_LUA_SPRITE_H
#define HARMONY_LUA_SPRITE_H

#include "lua_types.h"
#include "lua_engine.h"
#include "gx_sprite.h"

namespace harmony {
	namespace lua {
		extern const char * sprite_class;
		
		gx::sprite_ref to_sprite(const engine & engine, index_t index);
		gx::sprite_ref * check_sprite(const engine & engine, index_t index);
		
		void register_sprite_library(const engine & engine);
	}
}

#endif // HARMONY_LUA_SPRITE_H
