#pragma once

#include <sead/prim/seadRuntimeTypeInfo.h>
#include <sead/heap/seadHeap.h>

#include <agl/lyr/DrawMethod.hpp>
#include <agl/lyr/RenderInfo.hpp>

#include "../../Utl/ProcInVain.hpp"
#include "../../Utl/Meta.hpp"

namespace Lp::Sys {
    /* TODO: */
    struct SceneLoadInCalcThread;
    struct SceneGeneralThread;
    struct SceneStatusChecker;
    struct SceneDbgResetter;

    struct Scene {
        SEAD_RTTI_BASE(Scene);

        int field_8;
        agl::lyr::DrawMethod mSysSceneDraw2D;
        agl::lyr::DrawMethod mSysSceneDraw3D;
        sead::Heap* mHeap;
        sead::Heap* mDbgHeap;
        int mCalcCount;
        SceneLoadInCalcThread* mLoadInCalcThread;
        SceneGeneralThread* mGeneralThread;
        SceneStatusChecker* mStatusChecker;
        SceneDbgResetter* mDbgResetter;
        bool mShortReset;
        bool mShortExit;
        Utl::ProcInVain* mProcInVain;
        Utl::Meta mMeta;

        virtual void sceneLoad();
        virtual void sceneEnter();
        virtual void sceneReset();
        virtual void sceneCalc();
        virtual void sceneDraw2D(agl::lyr::RenderInfo const&);
        virtual void sceneDraw3D(agl::lyr::RenderInfo const&);
        virtual void sceneExit();
        virtual void sceneDestroy();
        virtual void dbgShortReset();
        virtual void dbgShortExit();
    };
    static_assert(sizeof(Scene) == 0x230);
}