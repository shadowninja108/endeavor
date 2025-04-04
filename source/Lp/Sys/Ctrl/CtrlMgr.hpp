#pragma once

#include "../Task/ProjTaskBase.hpp"
#include "Ctrl.hpp"
#include "CtrlType.hpp"

#include <sead/thread/seadCriticalSection.h>
#include <sead/thread/seadReadWriteLock.h>
#include <sead/container/seadPtrArray.h>
#include <sead/controller/seadController.h>
#include <sead/controller/seadControllerMgr.h>

namespace Lp::Sys {

    struct CtrlMgr : public ProjTaskBase {
        SEAD_RTTI_OVERRIDE(CtrlMgr, ProjTaskBase)
        
        public:
        uintptr_t thunk;
        /* TODO: prob a macro for this */
        uintptr_t field_230;
        sead::CriticalSection mCS;
        sead::ReadWriteLock mRWLock;
        char field_340;
        sead::SafeArray<sead::PtrArray<Ctrl>, CtrlType_End> mCtrls;
        uintptr_t mKbdMouseCtrl;
        sead::SafeArray<sead::Controller*, 8> mSeadCtrls;
        sead::Controller* mHandheldSeadCtrl;
        int field_3D8;

        void createCtrl(sead::ControllerMgr*);
        void changeCtrlJoy_(int ctrlType, int ctrlId);

        /* TODO: macro for this. */
        static CtrlMgr* sInstance;
    };
}