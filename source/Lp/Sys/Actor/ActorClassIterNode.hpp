#pragma once

#include <sead/prim/seadSafeString.hpp>
#include <sead/container/seadTreeNode.h>
#include <sead/container/seadTList.h>
#include <sead/prim/seadRuntimeTypeInfo.h>
#include <sead/thread/seadCriticalSection.h>
#include <sead/prim/seadScopedLock.h>
#include <concepts>
#include <type_traits>

namespace Lp::Sys {
    struct Actor;
    struct ActorClassIterNodeBase {
        SEAD_RTTI_BASE(ActorClassIterNodeBase);
        
        public:
        sead::TTreeNode<ActorClassIterNodeBase*> mClassIterNodeListNode;
        sead::TList<Actor*> mActors;
        sead::SafeString mClassName;

        public:
        ActorClassIterNodeBase(const char* className) : mClassName(className) {}

        /* Yes, not virtual. */ ~ActorClassIterNodeBase();
        int derivedSize();
        Actor* nextSleepActor(Actor*);
        Actor* frontSleepActor();
        Actor* nextActiveActor(Actor*);
        Actor* derivedNextActor(Actor*);
        Actor* frontActiveActor();
        Actor* derivedFrontActor();
        Actor* derivedNextSleepActor(Actor*);
        Actor* derivedFrontSleepActor();
        Actor* derivedNextActiveActor(Actor*);
        Actor* derivedFrontActiveActor();
        void dump();
        void erase_(Actor*);
        void toNode_(Actor*);
        void nextActor(Actor*);
        void pushBack_(Actor*);

        static sead::CriticalSection sLock;
    };

    template<typename Base>
    requires std::is_base_of_v<ActorClassIterNodeBase, Base>
    struct ActorClassIterNode : public Base {
        SEAD_RTTI_OVERRIDE(ActorClassIterNode<Base>, Base);

        ActorClassIterNode(const char* className) : Base(className) {}
    };
}