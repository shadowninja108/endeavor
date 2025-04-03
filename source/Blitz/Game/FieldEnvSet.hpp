#pragma once

#include <sead/math/seadVector.hpp>
#include <sead/gfx/seadColor.h>
#include <sead/prim/seadBitFlag.h>
#include <sead/prim/seadEnum.h>

#include <gsys/Model/ModelScene.hpp>

#include <Lp/Sys/Param/Param.hpp>
#include <Lp/Sys/Param/Params.hpp>

#include "InkType.hpp"

namespace Game {
    
    struct FieldEnvSet : public Lp::Sys::Params {
        /* TODO: check these + japanese text_ */
        SEAD_ENUM(LensFlareType, None=-1, Day_0, Day_1, Evening, Night, Mission_Underground);
        SEAD_ENUM(OceanType, Transparent, Transparent_Caustics, Opaque);

        Lp::Sys::Param<sead::Vector3f> mMainLightDir;
        Lp::Sys::Param<sead::Color4f> mMainLightColor;
        Lp::Sys::Param<float> mMainLightIntens;
        Lp::Sys::Param<LensFlareType> mLensFlareType;
        Lp::Sys::Param<sead::Vector3f> mEnvMapPoint;
        Lp::Sys::Param<sead::FixedSafeString<32>> mVRName;
        Lp::Sys::Param<float> mVRRotate;
        Lp::Sys::Param<float> mVRYOffset;
        Lp::Sys::Param<bool> mIsCustomAutoExposureRange;
        Lp::Sys::Param<float> mAutoExposureRangeMax;
        Lp::Sys::Param<float> mZFogStart;
        Lp::Sys::Param<float> mZFogEnd;
        Lp::Sys::Param<sead::Color4f> mZFogColor;
        Lp::Sys::Param<float> mZFogScatteringCoef;
        Lp::Sys::Param<float> mFogBlendFactor;
        Lp::Sys::Param<float> mRadialFogLobeCtrl;
        Lp::Sys::Param<float> mRadialFogSizeCtrl;
        Lp::Sys::Param<float> mRadialFogShadowInfluence;
        Lp::Sys::Param<sead::Color4f> mRadialFogColor;
        Lp::Sys::Param<float> mRadialFogIntens;
        Lp::Sys::Param<float> mYFogStart;
        Lp::Sys::Param<float> mYFogEnd;
        Lp::Sys::Param<sead::Color4f> mYFogColor;
        Lp::Sys::Param<float> mProjShadowDensity;
        Lp::Sys::Param<float> mProjShadowRotate;
        Lp::Sys::Param<sead::Vector2f> mProjShadowScale;
        Lp::Sys::Param<sead::Vector2f> mProjShadowTrans;
        Lp::Sys::Param<sead::Vector2f> mProjShadowScrollAnim;
        Lp::Sys::Param<float> mProjShadowRotateAnim;
        Lp::Sys::Param<float> mDOFLevel;
        Lp::Sys::Param<float> mDOFStart;
        Lp::Sys::Param<float> mDOFEnd;
        Lp::Sys::Param<float> mDOFFarCancel;
        Lp::Sys::Param<sead::FixedSafeString<32>> mCustomGEnvName;
        Lp::Sys::Param<sead::FixedSafeString<32>> mCustomSceneEnvName;
        Lp::Sys::Param<InkType> mInkType;
        Lp::Sys::Param<float> mPaintYOffset;
        Lp::Sys::Param<float> mPaintGridHeight;
        Lp::Sys::Param<bool> mIsPlanerReflection;
        Lp::Sys::Param<float> mPlanerReflectionHeight;
        Lp::Sys::Param<sead::Vector2f> mPlanerReflectionResoScale;
        Lp::Sys::Param<bool> mIsCreateOcean;
        Lp::Sys::Param<OceanType> mOceanType;
        Lp::Sys::Param<sead::BitFlag<uchar>> mIsDrawOuterOcean;
        Lp::Sys::Param<bool> mIsInkOcean;
        Lp::Sys::Param<sead::Color4f> mOceanColor;
        Lp::Sys::Param<sead::Color4f> mSkyColor;
        Lp::Sys::Param<sead::Color4f> mOceanEdgeBubbleColor;
        Lp::Sys::Param<float> mOceanNormAnisotropy;
        Lp::Sys::Param<float> mOceanHeight;
        Lp::Sys::Param<float> mOceanSimulationStep;
        Lp::Sys::Param<float> mOceanChoppiness;
        Lp::Sys::Param<float> mOceanWindSpeed;
        Lp::Sys::Param<sead::Vector2f> mOceanWindDir;
        Lp::Sys::Param<sead::Vector2f> mOceanFlowVel;
        Lp::Sys::Param<sead::Vector2<int>> mOceanMeshResoBit;
        Lp::Sys::Param<sead::Vector2<int>> mOceanMeshDivNumBit;
        Lp::Sys::Param<float> mOceanMeshVertWidth;
        Lp::Sys::Param<float> mOceanWaveRepeat;
        Lp::Sys::Param<float> mOceanCausticsFadeStart;
        Lp::Sys::Param<float> mOceanCausticsFadeEnd;
        Lp::Sys::Param<bool> mOceanEnableDepthFog;
        Lp::Sys::Param<sead::Color4f> mOceanDepthFogColor;
        Lp::Sys::Param<float> mOceanDepthFogStart;
        Lp::Sys::Param<float> mOceanDepthFogEnd;
        sead::FixedSafeString<64> field_2F30;
        char field_2F88;
        gsys::ModelScene* mModelScene;
        long field_2F98;
        float field_2FA0;
        float field_2FA4;
        sead::FixedSafeString<64> field_2FA8;
    };
    static_assert(sizeof(Lp::Sys::Param<float>) == 0xB0);
    static_assert(sizeof(Lp::Sys::Param<FieldEnvSet::LensFlareType>) == 0xB0);
    static_assert(sizeof(Lp::Sys::Param<sead::Vector3f>) == 0xC0);
    static_assert(sizeof(Lp::Sys::Param<sead::Color4f>) == 0xC8);
    static_assert(sizeof(Lp::Sys::Param<bool>) == 0xB0);
    static_assert(sizeof(Lp::Sys::Param<sead::FixedSafeString<32>>) == 0xF0);
    static_assert(offsetof(Lp::Sys::AglParam<sead::SafeString>, mObj) == 0x30);

    static_assert(offsetof(FieldEnvSet, mMainLightDir) == 0xA0);
    static_assert(offsetof(FieldEnvSet, mMainLightColor) == 0x160);
    static_assert(offsetof(FieldEnvSet, mLensFlareType) == 0x2D8);
    static_assert(offsetof(FieldEnvSet, mEnvMapPoint) == 0x388);
    static_assert(offsetof(FieldEnvSet, mVRName) == 0x448);
    static_assert(offsetof(FieldEnvSet, mAutoExposureRangeMax) == 0x748);
    static_assert(offsetof(FieldEnvSet, mOceanDepthFogEnd) == 0x2E80);
    static_assert(offsetof(FieldEnvSet, field_2FA8) == 0x2FA8);
    static_assert(sizeof(FieldEnvSet) == 0x3000);
}