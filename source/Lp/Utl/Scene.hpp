#pragma once

#include <sead/prim/seadSafeString.hpp>

#include <concepts>

#include "../Sys/Scene/Scene.hpp"

namespace Lp::Utl {
    void reqChangeScene(int, const char*);
    void reqChangeScene(sead::SafeString const&, char const*);
    Sys::Scene* getCurScene();
    Sys::SceneInfo* getSceneInfo(int, bool);    

    template<typename T>
    requires std::derived_from<T, Sys::Scene>
    inline T* getCurSceneTyped() {
        return reinterpret_cast<T*>(getCurScene());
    }
}