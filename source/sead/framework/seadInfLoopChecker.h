#pragma once

#include "basis/seadTypes.h"
#include "framework/seadCalculateTask.h"
#include "framework/seadTaskMgr.h"
#include "thread/seadAtomic.h"
#include "thread/seadThread.h"

namespace sead
{
class InfLoopChecker : public CalculateTask
{
    SEAD_TASK_SINGLETON(InfLoopChecker)
    SEAD_RTTI_OVERRIDE(InfLoopChecker, CalculateTask)

public:
    struct InfLoopParam
    {
    };

    using InfLoopEvent = DelegateEvent<const InfLoopParam&>;

    explicit InfLoopChecker(const TaskConstructArg& arg);
    ~InfLoopChecker() override;

    void countUp();
    void prepare() override;
    void calc() override;

    InfLoopEvent& getEvent() { return mEvent; }

private:
    void onInfLoop_();

    u32 mLoopCount;
    u32 mLoopThreshold;
    bool mEnabled;
    InfLoopEvent mEvent;
    sead::Atomic<u32> mSkipCounter;
};

class InfLoopCheckerThread : public Thread {
    InfLoopCheckerThread(sead::TickSpan,sead::Heap *,int,int,int);
    virtual void calc_(MessageQueue::Element msg) override;
};

}  // namespace sead
