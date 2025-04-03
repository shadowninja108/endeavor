#pragma once

#include <sead/heap/seadHeap.h>
#include <sead/hostio/seadHostIOReflexible.h>
#include <sead/prim/seadSafeString.hpp>
#include <sead/filedevice/seadFileDevice.h>

#include "lua.hpp"
#include "Instance.hpp"
#include "Coroutine.hpp"
#include "Env.hpp"

namespace elua {
    struct VM : sead::hostio::Reflexible {

        /* typo got em */
        enum class GcOpiton {
            
        };

        VM(sead::Heap*, bool);
        Instance* createInstance();
        Coroutine* createCoroutin(); /* L typo bozo */
        Env* createEnv(Env*);
        bool loadModuleForGlobal(sead::SafeString const& script, sead::SafeString const& name);
        bool loadModuleForEnv(sead::SafeString const& script, sead::SafeString const& name, Env&);
        bool handleError(lua_State*, int);
        int gc();
        int gc(GcOpiton, int);
        sead::FileDevice* getFileDevice();
        Instance* getRelativeInstanceFromLuaState(lua_State*);
    };
}