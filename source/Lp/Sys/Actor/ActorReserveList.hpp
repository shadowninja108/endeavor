#pragma once

#include <sead/container/seadTList.h>

#include "../Hio/IUseHioNode.hpp"

namespace Lp::Sys {
    struct Actor;
    
    struct ActorReserveList : public IUseHioNode {
        uintptr_t field_8;
        sead::TList<Actor*> m_Actors;
        int mListIndex;

        ActorReserveList(int index) : mListIndex(index) {}

        virtual ~ActorReserveList() = 0;
        void push(sead::TListNode<Actor*>* node);
    };

    struct ActorReserveActivateList : public ActorReserveList {
        virtual ~ActorReserveActivateList();
        void activateAll();
    };
    struct ActorReserveSleepList : public ActorReserveList {
        virtual ~ActorReserveSleepList();
        void sleepAll();
    };
    struct ActorReserveChangeTimingList : public ActorReserveList {
        virtual ~ActorReserveChangeTimingList();
        void changeAll();
    };
    struct ActorReserveChangeJobPriorityList : public ActorReserveList {
        virtual ~ActorReserveChangeJobPriorityList();
        void changeAll();
    };
    struct ActorReserveRemoveList : public ActorReserveList {
        virtual ~ActorReserveRemoveList();
        void removeAll();
    };
}