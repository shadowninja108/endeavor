#pragma once

#include <sead/heap/seadDisposer.h>
#include <sead/gfx/seadViewport.h>
#include <sead/gfx/seadCamera.h>
#include <sead/gfx/seadProjection.h>
#include <sead/gfx/seadColor.h>
#include <sead/hostio/seadHostIOReflexible.h>
#include <sead/prim/seadBitFlag.h>
#include <sead/prim/seadSafeString.hpp>
#include <sead/prim/seadRuntimeTypeInfo.h>
#include <sead/container/seadBuffer.h>

#include "Renderer.hpp"
#include "RenderStep.hpp"
#include "LayerJob.hpp"
#include "DebugInfo.hpp"

namespace agl::lyr {
    struct Layer : public sead::IDisposer, sead::hostio::Reflexible {
        SEAD_RTTI_BASE(Layer);

        public:
        Renderer* mRenderer;
        sead::Viewport mViewport1;
        sead::Viewport mViewport2;
        sead::Camera* mCamera;
        sead::Projection* mProjection;
        sead::BitFlag16 mOptions1;
        sead::BitFlag16 mOptions2;
        sead::BitFlag16 mOptions3;
        sead::BitFlag8 mOptions4;
        uchar mDisplayType; /* TODO: enum? */
        char field_89;
        char field_8A;
        char field_8B;
        int mId;
        int mJobWeight;
        sead::Color4f mClearColor;
        float field_A4;
        sead::Buffer<RenderStep> mRenderSteps;
        int mMaxDLSize;
        LayerJob* field_C0;
        LayerJob* field_C8;
        LayerJob* field_D0;
        sead::FixedSafeString<256> field_D8;
        DebugInfo* mDebugInfo;
        int field_1F8;

        virtual void getRenderStepNum() const;
        virtual sead::SafeString getRenderStepName(int) const;
        virtual void initializeImpl(sead::Heap*);
        virtual void calcImpl();
        virtual void postCalcCommandImpl();
        virtual void preDrawImpl(agl::lyr::RenderInfo const&) const;
        virtual void preDrawRenderStepImpl(agl::lyr::RenderInfo const&) const;
        virtual void preDrawRenderStepMethodImpl(agl::lyr::RenderInfo const&, agl::lyr::DrawMethod const&) const;
        virtual void postDrawRenderStepMethodImpl(agl::lyr::RenderInfo const&, agl::lyr::DrawMethod const&) const;
        virtual void postDrawRenderStepImpl(agl::lyr::RenderInfo const&) const;
        virtual void postDrawImpl(agl::lyr::RenderInfo const&) const;
        virtual bool isRenderStepGPUCalc(int) const;
        virtual bool isRenderStepNoDependency(int) const;
        virtual bool isForceInvisible() const;
        virtual bool isForceDisableClear() const;
        virtual void calcJobWeight();
        sead::Camera* getRenderCamera() const;

        // TODO: go into gsys::Layer
        // virtual void doInitialize(sead::Heap*);
        // virtual void doCalc();
        // virtual void doPreDraw(agl::lyr::RenderInfo const&) const;
        // virtual void doPostDraw(agl::lyr::RenderInfo const&) const;
    };
}