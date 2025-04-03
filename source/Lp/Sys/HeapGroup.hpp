#pragma once

#include <sead/thread/seadCriticalSection.h>
#include <sead/thread/seadReadWriteLock.h>
#include <sead/heap/seadDisposer.h>

namespace Lp::Sys {

    struct HeapGroup {
        /* TODO: where does this come from? */
        uintptr_t field_8;
        sead::CriticalSection mCS;
        sead::ReadWriteLock mRwLock;

        SEAD_SINGLETON_DISPOSER(HeapGroup);

        public:
        enum Group {
            Group_Sys,
            Group_Gfx,
            Group_Res,
            Group_Snd,
            Group_Scene,
            Group_Dbg,
            Group_Others,
            Group_End,
        };

        sead::SafeArray<sead::Heap*, Group_End> mHeaps;

        virtual ~HeapGroup();

        void createHeap(sead::Heap*);
    };
}