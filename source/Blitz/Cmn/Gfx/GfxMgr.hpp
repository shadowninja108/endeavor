#pragma once

#include <sead/heap/seadHeap.h>
#include <sead/prim/seadSafeString.hpp>
#include <sead/prim/seadDelegate.h>
#include <sead/prim/seadRuntimeTypeInfo.h>

#include <Lp/Sys/CalcInGSysCalc.hpp>
#include <Lp/Sys/Hio/IUseHioNode.hpp>

#include <gsys/Model/ModelScene.hpp>
#include <gsys/Model/ModelSceneEnv.hpp>

#include <agl/utl/DebugTexturePage.hpp>
#include <agl/DrawContext.hpp>

#include "GPUPerfController.hpp"
#include "../Def/Hour.hpp"

namespace Cmn {
    /* Changed a bit between target build and 3.1.0. */
    struct GfxMgr : public Lp::Sys::IUseHioNode {
        SEAD_RTTI_BASE(GfxMgr);

        struct CreateArg {
            Lp::Sys::Scene* mScene;
            sead::FixedSafeString<32> field_8;
            sead::FixedSafeString<32> mEnvSceneName;
        };
        static_assert(sizeof(CreateArg) == 0x78);

        uintptr_t field_8;
        sead::IDisposer mDisposer;
        gsys::ModelScene* mModelScene;
        sead::FixedSafeString<32> field_38;
        sead::FixedSafeString<32> mEnvSceneName;
        Def::Hour mHour;
        Lp::Sys::CalcInGSysCalc* field_B0;
        // Lp::Sys::CalcInGSysCalc* field_B8;
        GPUPerfController* mGPUPerfController;
        sead::Delegate1<GfxMgr, gsys::ModelSceneEnv::ApplyCallbackArg const&> mEnvApplyCB;
        // agl::utl::DebugTexturePage mDbgTexPage;
        bool field_E0;
        // char field_311;

        virtual ~GfxMgr();
        virtual void load(CreateArg const&);
        virtual void postLoad();
        virtual void enter();
        virtual void reset();
        virtual void exit();
        virtual void calcFrame();
        virtual void preActorCalc();
        virtual void postActorCalcDraw(agl::DrawContext*);
        virtual void getCurr3DCamera();
        virtual int getLyrIdx_3D_Main() const;
        virtual int getLyrIdx_2D_Main() const;
        virtual void createModelScene_(sead::Heap*);
        virtual void createModelScenePassCallback_(sead::Heap*) const;
        virtual void createModelResourceCallback_() const;
        virtual void getConfigName_() const;
        virtual void setupHourImpl_();
        virtual void setupEnv_();
        virtual void createLayer_(Lp::Sys::Scene*);
        virtual void setupStressAnalyzer_();
        virtual void applyEnvSet_();
        virtual void setupEnablePass_();
        virtual void initializePBRMgr_();
        virtual void initializeDynamicLightMgr_();
        virtual void createDebugMenu_();
    };
    static_assert(sizeof(GfxMgr) == 0xE8);
}