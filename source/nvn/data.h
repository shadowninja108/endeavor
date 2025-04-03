#pragma once

#include "stdint.h"

typedef uint64_t NVNcommandHandle;

#define u64 long
#define ALIGNED64(size) u64 data[size / sizeof(u64)]; static_assert(size % sizeof(u64) == 0)
#define NVNstruct(name, size) struct NVN##name { ALIGNED64(size); }

NVNstruct(window, 0x180);
NVNstruct(sync, 0x40);
NVNstruct(texture, 0xC0);
NVNstruct(memoryPool, 0x100);
NVNstruct(commandBuffer, 0xA0);
NVNstruct(buffer, 0x30);
NVNstruct(queue, 0x2000);
NVNstruct(device, 0x3000);
NVNstruct(deviceBuilder, 0x40);
NVNstruct(textureView, 0x28);

#undef NVNstruct
#undef ALIGNED64
#undef u64

struct NVNqueueErrorInfo {
    long mFaultAddress;
    int mAccessType;    /* 0 = READ, 1 = WRITE */
};