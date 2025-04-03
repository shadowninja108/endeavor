#pragma once

#include <sead/heap/seadDisposer.h>
#include <sead/container/seadOffsetList.h>

#include "VM.hpp"

namespace elua {
    struct Manager {
        SEAD_SINGLETON_DISPOSER(Manager);

        sead::OffsetList<VM> mVMList;
        VM* mDefaultVM;
        uintptr_t field_48; /* TODO: */

        virtual ~Manager();

        void initialize();
        VM* createVM(sead::Heap*, bool);
        void calc();
        void removeVM(VM*);
    };
}