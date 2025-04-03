#pragma once

#include <common.hpp>

#include <sead/heap/seadHeap.h>

#include <Lp/Sys/Hio/IUseHioNode.hpp>

#include <gsys/Model/ModelScene.hpp>

#include "Cmn/SceneBase.hpp"
#include "Cmn/ViewerEnvChanger.hpp"

namespace BlitzViewer {
    struct Scene : public Cmn::SceneBase {
        SEAD_RTTI_OVERRIDE(Scene, Cmn::SceneBase);

        gsys::ModelScene* mModelScene;
        Cmn::ViewerEnvChanger* mEnvChanger;

        Scene(sead::Heap*);
    };
    static_assert(sizeof(Scene) == 0x398, "");
}