#pragma once

#include <sead/heap/seadHeap.h>
#include <sead/math/seadVector.hpp>
#include <agl/DrawContext.hpp>

namespace gsys {
    
    struct SystemTask {
        
        struct CreateArg {
            int mDbgCtrlIdx;
            sead::Heap* mHeap;
            sead::Heap* mDbgHeap;
            sead::Vector2<int> mVirtualCanvasSize[2];
            sead::Vector2<int> mScanBufferSize[2];
            size_t mAglWorkMemSize;
            size_t mDynamicTextureAllocatorMemSize;
            size_t mDynamicTextureAllocatorDebugMemSize;
            size_t mModelWorkBufferMemSize;
            size_t mMaxDisplayListSize;
            size_t field_68;
            size_t field_70;
            bool mCreateEditor;
            bool mUseParticleMgr;
            bool field_7A;
            bool mCreateScreenshotMgr;
            uintptr_t mSeadPtclConfig;
            bool mEnableParticleLinearDepth;
            int field_8C;
            int mGpuParticleHeapSize;
            int mEffectModelHeapSize;
            int mPtclEmitCallbackHeapSize;
            char field_9C;
            uintptr_t field_A0;
            uintptr_t field_A8;
            int field_B0;
            int mWorkBufferSize;
            int field_B8;
            bool mEnableBatchProcessStreamOut;
            /* ... */

            virtual ~CreateArg();
        };

        agl::DrawContext* invokeDrawTV_(agl::DrawContext *drawContext);
    };
}