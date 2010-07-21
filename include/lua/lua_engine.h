//
// lua_engine.h
// Harmony
//

#ifndef HARMONY_LUA_ENGINE_H
#define HARMONY_LUA_ENGINE_H

#include <string>

#include "lua_library.h"
#include "lua_types.h"
#include "lua_error.h"
#include "vec2.h"
#include "ivec2.h"
#include "gx_sprite.h"

namespace harmony {
	namespace lua {
		extern const char * engine_context_registry_key;
		
		// Handles the Lua scripting engine and state.
		class engine {
		public:
			explicit engine(void * context);
			~engine();
			
			// Returns the actual Lua state.
			lua_State * state() const;
			operator lua_State*() const;
			
			// Registers a library of functions.
			void register_library(const char * library_name, const luaL_Reg * library) const;
			
			// Checks if the value at the given index is a specific proxy type.
			bool is_proxy(const char * class_name, index_t index) const;
			
			// Converts the userdata proxy at a given index to the original object.
			template <typename T>
			const T & to_proxy(const char * class_name, index_t index, const T & empty_value) const {
				// Return the appropriate value.
				if (is_proxy(class_name, index))
					return *reinterpret_cast<const T *>(lua_touserdata(state_, index));
				else
					return empty_value;
			}
			
			// Pushes a new userdata proxy for the given object onto the stack.
			template <typename T>
			void push_proxy(const char * class_name, const T & value) const {
				// Create the proxy userdata.
				new (lua_newuserdata(state_, sizeof(T))) T(value);
				
				// Push the metatable for that userdata on the stack.
				push_metatable(class_name);
				
				// Associate the userdata with the metatable.
				lua_setmetatable(state_, -2);
			}
			
			// Pushes a vector onto the stack.
			void push_vector(const vec2 & value) const;
			void push_vector(const ivec2 & value) const;
			
			// Pushes a sprite onto the stack.
			void push_sprite(const gx::sprite_ref & value) const;
			
			// Pushes the metatable associated with the specified class onto the stack.
			bool push_metatable(const char * class_name) const;
			
			// Loads a script and pushes it onto the stack.
			bool push_script(const std::string & filename) const;
			
			// Calls a function using the values on top of the stack.
			bool call(size_t num_arguments, size_t num_results) const;
			
			// Executes a script, loading it from a file.
			void run_script(const std::string & context, const std::string & filename,
				size_t num_arguments, size_t num_results) const;
			
		protected:
			// Throws whatever error is on top of the stack, removing it.
			void throw_error(const std::string & context) const;
			
			// Throws the error at the given stack position. Also removes that
			// error from the stack.
			void throw_error(const std::string & context, index_t index) const;
			
		private:
			lua_State * state_;
		};
	}
}

#endif // HARMONY_LUA_ENGINE_H
