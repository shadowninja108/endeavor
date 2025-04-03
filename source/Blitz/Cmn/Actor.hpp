#pragma once

#include <sead/heap/seadHeap.h>

#include <Lp/Sys/Actor/Actor.hpp>
#include <Lp/Sys/XLink/XLinkIUser.hpp>
#include <Lp/Sys/XLink/XLink.hpp>
#include <Lp/Utl/StateMachine.hpp>

#include <gsys/Model/Model.hpp>

#include "Def/ResetType.hpp"
#include "Def/Team.hpp"
#include "Component/ComponentHolder.hpp"

/* TODO: */
namespace xlink2 {
    struct IEventCallbackELink { struct EventArg; };
}

namespace Cmn {
    struct Actor : public Lp::Sys::Actor, public Lp::Sys::XLinkIUser {
        LP_ACTOR(Cmn::Actor, Lp::Sys::Actor);

        Lp::Sys::XLink* mXLink;
        Def::Team mTeam;
        ComponentHolder* mComponentHolder;
        gsys::Model* mModel;
        Lp::Utl::StateMachine* mStateMachine;

        virtual void load();
        virtual void postLoad();
        virtual void enter();
        virtual void postEnter();
        virtual void exit();
        virtual void destroy();
        virtual void firstCalc();
        virtual void secondCalc();
        virtual void thirdCalc();
        virtual void fourthCalc();
        virtual void fifthCalc();
        virtual void xlinkCalc();
        virtual void calc_PostChildCalcByThis(int);
        virtual void onCreate();
        virtual void onActivate();
        virtual void onSleep();
        virtual void prepareReset(Def::ResetType);
        virtual void reset(Def::ResetType);
        virtual void postReset(Def::ResetType);
        virtual void isSkipReset(Def::ResetType) const;
        virtual void checkResetCoreSafe(Def::ResetType) const;
        virtual void getCameraFocusMtx() const;
        virtual void calcElinkEvent(xlink2::IEventCallbackELink::EventArg const&) const;
        virtual void getXLinkMtx() const;
        virtual void getXLinkScale() const;
        virtual void getModelRTMtx(bool) const;
        virtual void getModelScale(bool) const;
        virtual void isUseXLink() const;
        virtual void isXLinkDoSleepEmitAndPlay() const;
        virtual void isCalcXLink() const;
        virtual const char* getXLinkName() const;
        virtual void onXLinkSetupModels();
        virtual void onXLinkSetupActionSlot(sead::Heap*);
        virtual void onXLinkSetupProperty();
        virtual void setXLinkLocalPropertyDefinition_(int);
        virtual void countXLinkLocalProperty_() const;
        virtual void createAdditionalActionSlot(sead::Heap*);
        virtual void createComponentHolder_();
        virtual void executeStateMachine_();
        virtual void resetState_();
        virtual void changeFirstState_();
    };
    static_assert(offsetof(Actor, mXLink) == 0x320, "");
}