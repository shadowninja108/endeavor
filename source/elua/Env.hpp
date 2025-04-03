#pragma once

#include <sead/hostio/seadHostIOReflexible.h>

namespace elua {
    struct VM;
    struct Env : sead::hostio::Reflexible {
        VM* mVM;
        int mRegistryKey;
        Env* mParent;

        virtual ~Env();
        void deleteEnvImpl();
        void reset();
        void pushSelf();
    };
}