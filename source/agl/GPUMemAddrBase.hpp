#pragma once

#include "GPUMemBlockBase.hpp"
#include "detail/MemoryPool.hpp"

namespace agl {
    struct GPUMemAddrBase {
        detail::MemoryPool* mPool;
        int mLength;
        GPUMemBlockBase* mBlock;
    };
}