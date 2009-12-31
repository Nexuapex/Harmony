//
// lua_engine.cpp
// Harmony
//

#include <string>
#include <sstream>

#include "lua_engine.h"
#include "lua_vector.h"
#include "lua_sprite.h"
#include "plat_interface.h"

namespace harmony {
	lua::engine::engine(void * context) {
		// Set up the Lua state.
		state_ = luaL_newstate();
		luaL_openlibs(state_);
		
		// Insert the context pointer into the registry.
		lua_pushlightuserdata(state_, context);
		lua_setfield(state_, LUA_REGISTRYINDEX, "harmony_engine_context");
		
		// Get up the search path for Lua files loaded from other scripts.
		char * search_path = hplat_get_script_path();

		// <package table>
		lua_getfield(state_, LUA_GLOBALSINDEX, "package");
		
		// <package table> <search path>
		lua_pushstring(state_, search_path);
		
		// <package table>
		lua_setfield(state_, -2, "path");
		
		// empty stack
		lua_pop(state_, 1);
		
		// Free the search path buffer.
		free(search_path);
	}
	
	lua::engine::~engine() {
		lua_close(state_);
	}
	
	lua_State * lua::engine::state() const {
		return state_;
	}
	
	lua::engine::operator lua_State*() const {
		return state_;
	}
	
	void lua::engine::register_library(const char * library_name, const luaL_Reg * library) const {
		// If there is no given library name, use the globals table.
		if (!library_name)
			lua_pushvalue(state_, LUA_GLOBALSINDEX);
		
		// Register the functions in the table.
		luaL_register(state_, library_name, library);
		
		// Restore the stack.
		lua_pop(state_, 1);
	}
	
	// Checks if the value at the given index is a specific proxy type.
	bool lua::engine::is_proxy(const char * class_name, index_t index) const {
		// If it's not a userdata, it can't be a proxy.
		if (!lua_isuserdata(state_, index))
			return false;
		
		// <value's metatable>
		if (!lua_getmetatable(state_, index))
			return false;
		
		// <value's metatable> <class metatable>
		lua_getfield(state_, LUA_REGISTRYINDEX, class_name);
		
		// Check if the metatable matches.
		bool is_proxy = !!lua_rawequal(state_, -1, -2);
		
		// empty stack
		lua_pop(state_, 2);
		
		// Return the result.
		return is_proxy;
	}
	
	void lua::engine::push_vector(const vec2 & value) const {
		push_proxy(lua::vec2_class, value);
	}
	
	void lua::engine::push_vector(const ivec2 & value) const {
		push_proxy(lua::ivec2_class, value);
	}
	
	void lua::engine::push_sprite(const gx::sprite_ref & value) const {
		push_proxy(lua::sprite_class, value);
	}
	
	bool lua::engine::push_metatable(const char * class_name) const {
		return !!luaL_newmetatable(state_, class_name);
	}
	
	bool lua::engine::push_script(const std::string & filename) const {
		std::string path = "script/" + filename;
		char * source = hplat_read_text_file(path.c_str());
		
		if (source) {
			bool result = !luaL_loadstring(state_, source);
			free(source);
			return result;
		} else {
			std::string message = "could not find script: " + filename;
			lua_pushstring(state_, message.c_str());
			return false;
		}
	}
	
	bool lua::engine::call(size_t num_arguments, size_t num_results) const {
		return !lua_pcall(state_, num_arguments, num_results, 0);
	}
	
	void lua::engine::run_script(const std::string & context,
		const std::string & filename, size_t num_arguments,
		size_t num_results) const
	{
		// <arguments?> <function/error message>
		if (!push_script(filename)) {
			if (num_arguments > 0) {
				// <error message> <arguments>.
				lua_insert(state_, -static_cast<int>(num_arguments + 1));
				
				// <error message>
				lua_pop(state_, static_cast<int>(num_arguments));
			}
			
			// Throw the error.
			throw_error(context);
		} else {
			// <function> <arguments>
			lua_insert(state_, -static_cast<int>(num_arguments + 1));
		}
		
		// <results/error message>
		if (!call(num_arguments, num_results)) {
			// Throw the error.
			throw_error(context);
		}
	}
	
	void lua::engine::throw_error(const std::string & context) const {
		throw_error(context, lua_gettop(state_));
	}
	
	void lua::engine::throw_error(const std::string & context, index_t index) const {
		std::stringstream message;
		const char * err = lua_tostring(state_, index);
		message << context << ": " << err;
		lua_remove(state_, index);
		throw error(message.str());
	}
}
