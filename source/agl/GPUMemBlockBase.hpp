#pragma once

#include <common.hpp>

#include "MemoryAttribute.hpp"
#include "detail/MemoryPool.hpp"
#include "detail/MemoryPoolHeap.hpp"

namespace agl {
    struct GPUMemBlockBase {
        void* mStartPtr;
        ulong mSize;
        detail::MemoryPool* mPool;
        detail::MemoryPoolHeap* mPoolHeap;
        char field_28;
        MemoryAttribute mAttribute;
        GPUMemBlockBase* mNext;

        virtual ~GPUMemBlockBase();
    };
}