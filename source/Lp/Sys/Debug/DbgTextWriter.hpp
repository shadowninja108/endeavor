#pragma once

#include "../Task/ProjTaskBase.hpp"

#include <sead/container/seadTList.h>
#include <sead/math/seadVector.hpp>
#include <sead/gfx/seadColor.h>
#include <sead/thread/seadCriticalSection.h>
#include <sead/thread/seadReadWriteLock.h>

namespace Lp::Sys {

    struct DbgTextWriter : public ProjTaskBase {
        SEAD_RTTI_OVERRIDE(DbgTextWriter, ProjTaskBase)
        SEAD_SINGLETON_DISPOSER(DbgTextWriter)

        public:
        struct ArgEx {
            int field_0 = 1;
            int field_4 = 1;
            sead::Vector2f mScale;
            float field_10 = 0;
            sead::Color4f mColor;
            uint mFlags = 0;
            bool mIsDecDrawFrameInScenePause = true;
            bool mIsDecDrawFrameDelayTrigInScenePause = false;

            ArgEx() :
                mScale(1,1),
                mColor(1,1,1,1)
            {}
        };

        struct Info {
            static constexpr s32 BufferSize = 256;

            int mLayerId;
            u8 field_4;
            sead::BufferedSafeString mStrUtf8;
            sead::WBufferedSafeString mStrUtf16;
            union {
                char        mStrUtf8Data[BufferSize / sizeof(char)];
                char16_t    mStrUtf16Data[BufferSize / sizeof(char16_t)];
            };
            sead::Vector2f mPos;
            ArgEx mEx;
        };

        uintptr_t thunk;
        /* TODO: prob a macro for this */
        uintptr_t field_230;
        sead::CriticalSection mCS;
        sead::ReadWriteLock mRWLock;
        char field_340;

        sead::TList<Info> field_348;
        sead::TList<Info> field_360;
        /* TODO: Maybe a FixedTList<T>? */
        sead::TList<Info> field_378;        
        sead::TListNode<Info> field_390[1024];
        sead::CriticalSection mCS2;

        /* TODO: functions */
        void entryCmn(int, sead::Vector2f const&, ArgEx const*, Info *);
    };
}