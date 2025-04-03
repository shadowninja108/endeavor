#pragma once

#include <framework/seadGameFramework.h>
#include <time/seadTickSpan.h>
#include <time/seadTickTime.h>
#include <gfx/seadColor.h>
#include <gfx/seadFrameBuffer.h>
#include <gfx/nx/seadFrameBufferNvn.h>
#include <gfx/nx/seadDisplayBufferNvn.h>
#include <thread/seadThread.h>
#include <framework/seadProcessMeterBar.h>
#include <nn/os.hpp>
#include <nvn/nvn.hpp>

namespace sead {
    struct GameFrameworkNx : public GameFramework {
        SEAD_RTTI_OVERRIDE(GameFrameworkNx, GameFramework);
        
        public:
        struct CreateArg {
            int mVBlankWaitInterval;
            Color4f mClearColor;
            int mFramebufferWidth;
            int mFramebufferHeight;
            char field_1C;
            bool mTripleBuffer;
            bool mIsDebug;
            char field_1f;
            int field_20;
            int mControlMemorySize;
            int field_28;
            int field_2C;
            int mAllocatorSize;
            int field_34;
            int field_38;
            int field_3C;
            int mNvnDebugLevel;
            int field_44;
        };
        static_assert(sizeof(CreateArg) == 0x48);

        using WaitDrawDoneCB = void (*)();
        using ErrorCB = bool (*)(NVNqueueGetErrorResult, const char*, NVNqueueErrorInfo*);

        CreateArg mArg;
        TickSpan mTicksPerFrame;
        TickTime mLastFrameTick;
        FrameBufferNvn* mFrameBuffer1;
        LogicalFrameBuffer field_20B0;
        TickSpan mVBlankInterval;
        DisplayBufferNvn* mDisplayBuffer;
        WaitDrawDoneCB mDrawDoneCB;
        ErrorCB mErrorCB;
        NVNmemoryPool* mCommandMemoryPool;
        void* mCommandMemoryPoolAddress;
        NVNcommandBuffer* mCommandBuffer;
        NVNbuffer* field_2108;
        uintptr_t field_2110; /* Result of nvnBufferMap on field_2108. */
        NVNmemoryPool* mShaderScratchMemoryPool;
        int mShaderScratchMemorySize;
        uintptr_t mAllocator; /* nn::mem::StandardAllocator* */
        size_t mPeakCommandMemoryUsed;
        size_t mPeakControlMemoryUsed;
        NVNqueue* mNvnQueue;
        FrameBufferNvn* mFrameBuffer2;
        uintptr_t mViDisplay;   /* nn::vi::Display* */
        uintptr_t mViLayer;     /* nn::vi::Layer* */
        DelegateThread* mPresentationThread;
        NVNsync* mSync;
        MultiProcessMeterBar<4> mPresentBar;
        NVNcommandHandle mCommandBufferHandle;
        nn::os::SystemEventType  mVSyncEvent;
        bool field_2388;
        bool field_2389;
        bool mDoPresent;
        char field_238B;
        char field_238C;
    };
    static_assert(sizeof(GameFrameworkNx) == 0x2390);
}