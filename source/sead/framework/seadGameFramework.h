#pragma once

#include <framework/seadFramework.h>
#include <framework/seadProcessMeterBar.h>
#include <framework/seadProcessMeter.h>
#include <framework/seadInfLoopChecker.h>
#include <framework/menu/seadMenuMgr.h>
#include <framework/seadCuckooClock.h>
#include <controller/seadControllerMgr.h>
#include <hostio/seadHostIOMgr.h>
#include <prim/seadSafeString.hpp>

namespace sead {
    struct GameFramework : public Framework {
        SEAD_RTTI_OVERRIDE(GameFramework, Framework);

        using DrawContextCB = void (*)(bool);

        public:
        int mDisplayState; /* TODO: enum? */
        sead::MultiProcessMeterBar<32> mCalcBar;
        sead::MultiProcessMeterBar<32> mDrawBar;
        sead::MultiProcessMeterBar<32> mWaitGPUBar;
        InfLoopCheckerThread* mCheckerThread;
        uintptr_t field_2040;   /* "FrameDrawContext"? */
        DrawContextCB mDrawContextCB;

        virtual void createControllerMgr(TaskBase*);
        virtual void createHostIOMgr(TaskBase*);
        virtual void createProcessMeter(TaskBase*);
        virtual void createSeadMenuMgr(TaskBase*);
        virtual void createInfLoopChecker(TaskBase*);
        virtual void createCuckooClock(TaskBase*);
        virtual float calcFps() = 0;
        virtual void saveScreenShot(SafeString const&);
        virtual bool isScreenShotBusy() const;
        virtual void waitStartDisplayLoop_();
        virtual void initHostIO_();

        void startDisplay();
        void initialize(const Framework::InitializeArg&);
        void lockFrameDrawContext();
        void unlockFrameDrawContext();
    };
    static_assert(sizeof(GameFramework) == 0x2050);
}