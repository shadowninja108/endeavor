#pragma once

#include <common.hpp>

#include "lua.hpp"

namespace eula {
    struct ScriptGlueData {
        long mType; /* TODO: investigate... */
        const char* mName;
        lua_CFunction mFuncPtr;
        uintptr_t field_10; /* TODO: */
        void* mUserData; /* Seems only relevant for global functions? */
    };
}