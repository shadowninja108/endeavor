#pragma once

#include "lua.hpp"

namespace elua {
    struct VM;
    struct Coroutine {
        lua_State* mThread;
        VM* mVM;

        virtual ~Coroutine();
    };
}