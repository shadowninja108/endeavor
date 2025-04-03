#pragma once

#include <agl/lyr/DrawMethod.hpp>
#include <sead/framework/seadCalculateTask.h>
#include <sead/framework/seadMethodTree.h>

namespace Lp::Sys {
    struct ProjTaskBase : public sead::CalculateTask {
        SEAD_RTTI_OVERRIDE(ProjTaskBase, sead::CalculateTask)
        public:
        agl::lyr::DrawMethod m2DRenderMethod;
        agl::lyr::DrawMethod m3DRenderMethod;
        
        virtual void draw2D(agl::lyr::RenderInfo const&);
        virtual void draw3D(agl::lyr::RenderInfo const&);
    };
    static_assert(sizeof(ProjTaskBase) == 0x228, "");
}