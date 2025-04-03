#pragma once

#include <sead/heap/seadHeap.h>
#include "../Scene/Scene.hpp"

#include <concepts>

namespace Lp::Sys {

    struct SceneInfo {
        template<typename T>
        using CtorT = T* (int, sead::Heap*);

        const char* mName;
        CtorT<Scene>* mCtor;
        const char* mMeta;

        template<typename T>
        requires std::derived_from<T, Scene>
        CtorT<T>*& TypedCtor() {
            auto typed = reinterpret_cast<CtorT<T>**>(&mCtor);
            return *typed;
        }
    };

    struct ISceneInfoCstm {
        SEAD_RTTI_BASE(ISceneInfoCstm);

        public:
        virtual int getSceneNum() const;
        virtual SceneInfo* getSceneInfo(int) const;
        virtual void initChangeScene(int);
        virtual void startSceneFadeOut();
        virtual bool isAbleExitScene() const;
        virtual bool isAbleEnterScene() const;
        virtual bool isAbleFaderFadeOut() const;
        virtual void preSceneAndHeapDestroy();
        virtual void postSceneAndHeapDestroy();
        virtual bool isAbleChangeSceneAsHbm() const;
        virtual int getBootSceneId() const;
        virtual int getAfterBootSceneId() const;
        virtual void addHioNodeCategory() ;
        virtual int* getSceneDbgHeapSize() const;
        virtual int getOverWriteSceneHeapSize() const;

        static ISceneInfoCstm* spCstm;
    };

}