#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include <heap/seadHeap.h>

namespace sead {
    struct DisplayBuffer {
        SEAD_RTTI_BASE(DisplayBuffer);

        public:
        virtual void initializeImpl_(Heap*) = 0;

        void presentTextureAndAcquireNext();
        void waitAcquireDone();
        void setPresentInterval(uchar);
        void setTripleBuffer(bool);
        void setWindowCrop(int, int, int, int);
        void getWindowCrop(int*, int*, int*, int*) const;
        void applyChangeWindowCrop();
    };
}