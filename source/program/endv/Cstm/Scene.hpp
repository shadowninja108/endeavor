#pragma once

#include <lib.hpp>
#include <Lp/Sys/Task/RootTask.hpp>
#include <Lp/Sys/Scene/SceneMgr.hpp>
#include <Lp/Sys/Cstm/ISceneInfoCstm.hpp>
#include <Lp/Utl/Scene.hpp>
#include <Lp/Sys/HeapGroup.hpp>

#include <sead/heap/seadExpHeap.h>

#include <concepts>

namespace endv {
    void OnCreateScene(Lp::Sys::Scene* scene);
}

namespace endv::Cstm {

    template<typename T>
    requires std::derived_from<T, Lp::Sys::Scene>
    static T* newScene(int id, sead::Heap* heap) {
        /* Get scene info Cstm and ensure it's not null. */
        auto cstm = Lp::Sys::ISceneInfoCstm::spCstm;
        EXL_ASSERT(cstm != nullptr);

        /* Get current scene info and ensure it's not null. */
        auto info = cstm->getSceneInfo(id);
        EXL_ASSERT(info != nullptr);

        /* Allocate and construct scene from given heap. */
        auto scene = new (heap) T(heap);
    
        OnCreateScene(scene);

        return scene;
    }
}