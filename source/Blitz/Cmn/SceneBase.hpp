#pragma once

#include <common.hpp>

#include <sead/heap/seadHeap.h>

#include <Lp/Sys/Scene/Scene.hpp>
#include <Lp/Sys/Hio/IUseHioNode.hpp>
#include <Lp/Sys/Layer/GfxLayerBG.hpp>

#include "Def/ResetType.hpp"
#include "SceneSound.hpp"
#include "Gfx/GfxMgr.hpp"
#include "../Cui/PageMgr.hpp"

namespace Cmn {
    /* TODO: */
    struct ActorPicker;
    struct SceneMemChecker;

    struct SceneBase : public Lp::Sys::Scene, Lp::Sys::IUseHioNode {

        SEAD_RTTI_OVERRIDE(SceneBase, Lp::Sys::Scene);

        struct ActorHio : public Lp::Sys::IUseHioNode {
            ulong field_8;
        };

        u64 field_238;
        sead::DelegateR<SceneBase, bool> mResetShortCB;
        sead::DelegateR<SceneBase, bool> mResetLongCB;
        sead::DelegateR<SceneBase, bool> mExitShortCB;
        sead::DelegateR<SceneBase, bool> mExitLongCb;
        SceneSound* mSceneSound;
        int field_2C8;
        Cui::PageMgr* mPageMgr;
        /* TODO: */
        uintptr_t mCmnSeqPageHandler;
        uintptr_t mMsgWindowPageHandler;
        Def::ResetType mResetType;
        GfxMgr* mGfxMgr;
        char field_2F8;
        Lp::Sys::GfxLayerBG* mBG;
        agl::lyr::DrawMethod mActorCalcLayerDrawMethod;
        ActorHio mActorHio;
        ActorPicker* mActorPicker;
        SceneMemChecker* mSceneMemChecker;

        SceneBase(sead::Heap*);

        virtual void load();
        virtual void enter();
        virtual void preActorCalc();
        virtual void exit();
        virtual void destroy();
        virtual void draw2D(agl::lyr::RenderInfo const&);
        virtual void postDraw2D(agl::lyr::RenderInfo const&);
        virtual void draw3D(agl::lyr::RenderInfo const&);
        virtual void postDraw3D(agl::lyr::RenderInfo const&);
        virtual void cbResetShort();
        virtual void cbResetLong();
        virtual void cbExitShort();
        virtual void cbExitLong();
        virtual void createSceneSound();
        virtual void prepareReset();
        virtual void reset();
    };
    static_assert(sizeof(SceneBase) == 0x388);
    static_assert(offsetof(SceneBase, field_238) == 0x238);
}