//
// lua_vector.h
// Harmony
//

#ifndef HARMONY_LUA_VECTOR_H
#define HARMONY_LUA_VECTOR_H

#include "lua_types.h"
#include "lua_engine.h"
#include "vec2.h"
#include "ivec2.h"

namespace harmony {
	namespace lua {
		extern const char * vec2_class;
		extern const char * ivec2_class;
		
		vec2 to_vec2(const engine & engine, index_t index);
		vec2 check_vec2(const engine & engine, index_t index);
		vec2 opt_vec2(const engine & engine, index_t index, const vec2 & default_value);
		ivec2 to_ivec2(const engine & engine, index_t index);
		ivec2 check_ivec2(const engine & engine, index_t index);
		ivec2 opt_ivec2(const engine & engine, index_t index, const ivec2 & default_value);
		
		void register_vector_library(const engine & engine);
	}
}

#endif // HARMONY_LUA_VECTOR_H
