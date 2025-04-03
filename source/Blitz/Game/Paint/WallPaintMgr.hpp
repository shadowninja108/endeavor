#pragma once

#include <common.hpp>

#include <gsys/Model/Model.hpp>

#include <agl/Texture.hpp>
#include <agl/TextureSampler.hpp>
#include <agl/GPUMemAddrBase.hpp>

#include <sead/prim/seadDelegate.h>
#include <sead/math/seadVector.hpp>
#include <sead/container/seadBuffer.h>
#include <sead/gfx/seadCamera.h>
#include <sead/gfx/seadProjection.h>

namespace Game {
    struct WallPaintMgr {
        struct Grid {
            float field_0;
            float field_4;
            sead::Vector3f field_8;
            int mIndex;
        };
        struct Edge {
            sead::Vector3f field_0;
            sead::Vector3f field_C;
            sead::Vector3f field_18;
            sead::Vector3f field_24;
        };
        
        uintptr_t field_8;
        uchar field_10;
        sead::Buffer<Grid> mGridInfo[4];
        gsys::Model* mFieldModel;
        sead::Vector3f field_60;
        sead::Vector3f mGridProj;
        sead::Vector3f mGridDiv;
        float field_84;
        float mPaintGridXZOffset;
        sead::LookAtCamera* field_90;
        sead::OrthoProjection field_98;
        float field_148;
        float field_14C;
        agl::TextureData mGridTex;
        agl::TextureSampler field_2D0;
        agl::GPUMemAddrBase field_498;
        agl::TextureData field_4B0;
        agl::TextureSampler field_630;
        int field_7F8;

        sead::Delegate1<WallPaintMgr, Edge const&> mActivateGridOnEdgeCallback;
        sead::Delegate1<WallPaintMgr, Edge const&> field_820;
        sead::Delegate1<WallPaintMgr, Edge const&> field_840;

        virtual ~WallPaintMgr();
    };
    static_assert(sizeof(WallPaintMgr) == 0x860);
}