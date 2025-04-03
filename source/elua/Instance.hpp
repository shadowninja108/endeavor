#pragma once

#include <sead/container/seadListImpl.h>
#include <sead/hostio/seadHostIOReflexible.h>

#include "lua.hpp"

namespace elua {
    struct VM;
    struct Env;
    struct Coroutine;

    struct Instance : sead::hostio::Reflexible {
        enum class Status {
            Ok = 0x0,
            Unset = 0x1,
            Runtime = 0x2,
            Syntax = 0x3,
            OutOfMemory = 0x4,
        };

        sead::ListNode mListNode;
        VM* mVM;
        Env* mGlobalEnv;
        Env* mEnv;
        Coroutine* mCoroutine;
        int mStatus;    /* TODO: Is this Status? */
 
        Instance(VM*);
        
        virtual ~Instance();
        bool loadModule(sead::SafeString const& script, sead::SafeString& const name);
        bool runScript(sead::SafeString const& script, sead::SafeString& const name);
        bool runFunction(sead::SafeString const& script, sead::SafeString const& func, sead::SafeString& const name);
        bool runFunction(sead::SafeString const& func);
        bool resume();
        void killRoutine();
        void debugPrintStack();
        lua_State* getRawState();
    };
}