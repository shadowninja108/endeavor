#pragma once

#include <types.h>

namespace nn::os {

    struct MemoryInfo {
        size_t availaible_size;
        size_t used_size;
        char unk[0x28]; 
    };

    void QueryMemoryInfo(MemoryInfo *memoryInfo);
}