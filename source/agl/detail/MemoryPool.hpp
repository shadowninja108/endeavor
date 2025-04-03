#pragma once

#include <nvn.hpp>

namespace agl::detail {
    struct MemoryPool {
        NVNmemoryPool mImpl;
        int mPoolType;
    };
}