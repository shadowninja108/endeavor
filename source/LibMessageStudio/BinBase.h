#pragma once

#include <stddef.h>

#include "ProjectBlock.h"

struct LMSBinBase {
    const void* mBin;
    size_t mBinLength;
    char field_10;
    char field_11;
    unsigned short mBlockCount;
    LMSProjectBlock* mBlocks;
};