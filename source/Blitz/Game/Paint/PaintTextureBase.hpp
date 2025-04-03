#pragma once

#include <sead/prim/seadRuntimeTypeInfo.h>
#include <agl/TextureSampler.hpp>
#include <agl/Texture.hpp>
#include <sead/gfx/seadViewport.h>
#include <sead/gfx/seadProjection.h>

namespace Game {
    struct PaintTextureBase : public sead::RuntimeTypeInfo::Interface {
        SEAD_RTTI_BASE(PaintTextureBase);
        
        public:
        uintptr_t field_8;
        int mWidth;
        int mHeight;
        int mMapWidth;
        int mMapHeight;
        sead::Viewport mViewport;
        sead::OrthoProjection mProjection;
        agl::TextureData mColorData;
        agl::TextureSampler mColorSampler;
        agl::TextureData mMapData;
        agl::TextureSampler mMapColorSampler;
        agl::TextureData mDepthData;

        virtual ~PaintTextureBase();
        agl::TextureData* getColorData() const;
        agl::TextureSampler* getColorSampler() const;
        agl::TextureData* getMapColorSampler() const;
        agl::TextureData* getDepthData() const;
    };
}