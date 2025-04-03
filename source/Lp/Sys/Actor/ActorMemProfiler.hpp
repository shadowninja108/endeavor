#pragma once

#include <sead/thread/seadCriticalSection.h>
#include <sead/prim/seadSafeString.hpp>
#include <sead/heap/seadDisposer.h>
#include <sead/container/seadTList.h>

namespace Lp::Sys {
    
    struct ActorMemProfiler {
        SEAD_SINGLETON_DISPOSER(ActorMemProfiler);
        public:

        enum Func {
            Func_Create,
            Func_Load,
            Func_PostLoad,
            Func_Enter,
            Func_PostEnter,
            Func_End
        };

        struct Info {
            sead::FixedSafeString<32> mName;
            uint mNameHash;
            int mCount;
            int mSize;
            int mPeakUsage;
        };

        sead::TList<Info> mInfoListsByFunc[Func_End];
        sead::TList<Info> mInfoPool;
        sead::TListNode<Info>* mTopNode;
        sead::FixedSafeString<0x3FC00> mDumpStr;
        sead::CriticalSection mCS;
        
        void add(sead::SafeString const&, Func, int);
        void makeDumpStr();
        void dump();
        /* TODO: Lp Hio. */

        static bool checkSameName(Info const*, Info const*);
        static int compareName(Info const*, Info const*);
        static int compareSize(Info const*, Info const*); 
    };
}