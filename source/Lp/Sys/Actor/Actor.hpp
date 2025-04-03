#pragma once

#include <agl/lyr/RenderInfo.hpp>
#include <sead/math/seadMatrix.hpp>
#include <sead/gfx/seadColor.h>
#include <sead/container/seadTList.h>
#include <sead/container/seadTreeNode.h>
#include <sead/heap/seadHeapMgr.h>
#include <sead/prim/seadScopedLock.h>
#include <sead/mc/seadJob.h>
#include <sead/mc/seadCoreInfo.h>
#include "ActorSystem.hpp"
#include "ActorJobPriority.hpp"
#include "ActorMemProfilerAutoVal.hpp"
#include "ActorClassIterNode.hpp"
#include "Constants.hpp"
#include <concepts>

#define LP_ACTOR(name, base)                                                                                            \
    SEAD_RTTI_OVERRIDE(name, base);                                                                                     \
    public:                                                                                                             \
    static auto* getClassIterNodeStatic() {                                                                             \
        auto baseNode = *base::getClassIterNodeStatic();                                                                \
        static ::Lp::Sys::ActorClassIterNode<decltype(baseNode)> sClassIterNode(#name);                                 \
        sead::ScopedLock lk(&::Lp::Sys::ActorClassIterNodeBase::sLock);                                                 \
        baseNode.mClassIterNodeListNode.pushBackChild(&sClassIterNode.mClassIterNodeListNode);                          \
        return &sClassIterNode;                                                                                         \
    }                                                                                                                   \
    virtual ::Lp::Sys::ActorClassIterNodeBase* getClassIterNode() override { return getClassIterNodeStatic(); }         \
    virtual const char* getClassName() const override { return #name; } 

namespace Lp::Sys {
    struct Actor {
        public:

        enum ListNodeKind {
            ListNodeKind_ActivateSleep = 0x0,
            ListNodeKind_ChangeCalcTiming = 0x1,
            ListNodeKind_ChangeJobPriority = 0x2,
            ListNodeKind_Remove = 0x3,
            ListNodeKind_DbgSleepForReactivate = 0x4,
            ListNodeKind_End,
        };

        uintptr_t field_8;
        sead::TTreeNode<Actor*> mManageTreeNode;
        sead::TTreeNode<Actor*> mActiveTreeNode;
        sead::TListNode<Actor*> mListNodes[ListNodeKind_End];
        CalcBitfield mCalcTiming;
        CalcBitfield mCalcTimingByParent;
        CalcBitfield mNewCalcTiming;
        CalcBitfield mNewCalcTimingByParent;
        CalcBitfield mChildCalcTiming;
        sead::Job0<Actor> mCalcJob;
        sead::CoreId mCoresByCalcList[s_ActorSystem_MaxCalcList];
        ActorJobPriority mJobPriorityiesByCalc[s_ActorSystem_MaxCalcList];
        sead::Heap* mHeap;
        int mColCheckIndex;
        sead::TickTime mConstructTime;
        uintptr_t field_268; /* For the love of god, cannot infer anything about this. It's constructed then never used. */
        sead::FixedSafeString<64> mClassName;
        sead::TListNode<Actor*> mClassIterListNode;

        Actor();
        virtual ~Actor();
        virtual CalcBitfield getDefaultCalcTiming();
        virtual CalcBitfield getDefaultCalcByParent();
        virtual void actorLoad();
        virtual void actorPostLoad();
        virtual void actorEnter();
        virtual void actorPostEnter();
        virtual void actorReset();
        virtual void actorPostReset();
        virtual void actorExit();
        virtual void actorDestroy();
        virtual void actorCalc(int);
        virtual void actorCalc_PostChildCalcByThis(int);
        virtual void actorDbgDraw3D(agl::lyr::RenderInfo const&) const;
        virtual void actorDbgDraw2D(agl::lyr::RenderInfo const&) const;
        virtual void actorOnCreate();
        virtual void actorOnActivate();
        virtual void actorOnSleep();
        virtual void actorOnRemove();
        virtual void dbgOnAfterSleepBeforeReActivate(bool);
        virtual sead::Color4f getProcBarColor(int) const;
        virtual sead::Matrix34f* getDbgMtx() const;
        virtual const char* getClassName() const;
        SEAD_RTTI_BASE(Actor); /* Why the fuck is this down here? */
        public:
        virtual ActorClassIterNodeBase* getClassIterNode();

        void actorSysOnCreate(Actor*);

        static ActorClassIterNodeBase* getClassIterNodeStatic() {
            static ActorClassIterNodeBase sClassIterNode("Actor");
            return &sClassIterNode;
        }

        template<typename T>
        requires std::derived_from<T, Actor>
        static T* create(Actor* parent, sead::Heap* heap) {
            auto& lock = SEAD_INSTANCE(ActorSystem)->mActorCS;
            lock.lock();

            ActorMemProfilerAutoVal profiler(sead::SafeString("TODO"), ActorMemProfiler::Func_Create);
            T* actor = new (heap) T();

            if(actor != nullptr) {
                if(heap == nullptr)
                    heap = SEAD_INSTANCE(sead::HeapMgr)->getCurrentHeap();

                actor->mHeap = heap;
                actor->actorSysOnCreate(parent);
            }
            lock.unlock();            
            return actor;
        }
    };

    
    struct RootActor : public Actor {
        LP_ACTOR(Lp::Sys::RootActor, Actor);
    };
}