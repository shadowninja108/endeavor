#pragma once

#include <sead/prim/seadSafeString.hpp>
#include <sead/thread/seadCriticalSection.h>
#include <sead/thread/seadReadWriteLock.h>
#include "../Task/ProjTaskBase.hpp"
#include "Scene.hpp"


namespace Lp::Sys {

    struct SceneMgr : public ProjTaskBase {
        SEAD_RTTI_OVERRIDE(SceneMgr, ProjTaskBase)

        uintptr_t thunk;
        /* TODO: prob a macro for this */
        uintptr_t field_230;
        sead::CriticalSection mCS;
        sead::ReadWriteLock mRWLock;
        char field_330;
        // uintptr_t field_338;
        // char field_340;

        Scene* mCurrentScene;
        int mCurrentSceneId;
        int mNextSceneId;
        int mPrevSceneId;
        bool mIsReqChangeScene;
        bool mForceFaderFastOut;
        sead::FixedSafeString<256> mCurentSceneName;
        sead::FixedSafeString<256> mNextSceneName;
        sead::FixedSafeString<256> mSceneMeta;
        /* ... */

        /* TODO: macro for this */
        static SceneMgr* sInstance;
    };
    static_assert(offsetof(SceneMgr, mCurrentSceneId) == 0x350);
}