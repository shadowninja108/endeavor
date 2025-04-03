#pragma once

#include "lua.hpp"

namespace elua {
    struct Util {
        static bool checkCount(lua_State*, int);
        static void pop(lua_State*);
    };
}