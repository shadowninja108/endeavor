#pragma once

#include <gsys/Model/Model.hpp>

#include "PaintTextureBase.hpp"
#include "WallPaintMgr.hpp"
#include "PaintFaceType.hpp"

#include <agl/RenderTargetColor.hpp>

namespace Game {
    struct PaintTexture : public PaintTextureBase {
        SEAD_RTTI_OVERRIDE(PaintTexture, PaintTextureBase);
        public:
        gsys::Model* mFieldModel;
        WallPaintMgr mWallPaintMgr;
        uchar field_E58;
        agl::RenderTargetColor mRenderTargetColorsByPaintFaceType[Game::PaintFaceType_Y_Down];
        // agl::RenderTargetDepth mRenderTargetDepthsByPaintFaceType[Game::PaintFaceType_Y_Down];
        // agl::RenderBuffer mRenderBuffersByPaintFaceType[Game::PaintFaceType_Y_Down];
        // agl::RenderTargetColor mMiniMapTexTargetColor[Game::PaintFaceType_Y_Down];
        // agl::RenderBuffer mMiniMapRenderBuffer[Game::PaintFaceType_Y_Down];
        // bool mReqClearTextures;
        // uchar field_27D1;
        // uchar field_27D2;
        // PaintMasker mMasker;
        // sead::Vector2f mPaintProj;
        
        virtual ~PaintTexture();
        agl::TextureData* getColorData() const;
        agl::TextureSampler* getColorSampler() const;
        agl::TextureData* getMapColorSampler() const;
        agl::TextureData* getDepthData() const;
    };
}