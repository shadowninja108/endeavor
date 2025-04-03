#pragma once

#include <gsys/Model/ModelScene.hpp>
#include <gsys/Model/Model.hpp>

#include <agl/lyr/DrawMethod.hpp>
#include <agl/TextureSampler.hpp>

#include "../Cmn/Gfx/GfxMgr.hpp"
#include "FieldEnvSet.hpp"

namespace Game {
    struct GfxMgr : public Cmn::GfxMgr {
        gsys::ModelScene* mMiniMapModelScene;
        gsys::ModelScene* mScreenshotModelScene;
        agl::TextureSampler field_f8;
        gsys::Model* mVRModel;
        agl::lyr::DrawMethod mBGDrawMethod;
        FieldEnvSet* mFieldEnvSet;
        uintptr_t mInkAnimation;
        bool mBakeLightForceEnable;
        bool mDrawOverlayDrc;
        agl::TextureData* mOverlayDrcTexture;
        /* ... */
    };
}