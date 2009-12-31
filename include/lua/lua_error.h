//
// lua_error.h
// Harmony
//

#ifndef HARMONY_LUA_ERROR_H
#define HARMONY_LUA_ERROR_H

#include <stdexcept>

namespace harmony {
	namespace lua {
		class error : public std::runtime_error {
		public:
			explicit error(const std::string & what) : runtime_error(what) {}
		};
	}
}

#endif // HARMONY_LUA_ERROR_H
