#pragma once

#include "BinBase.h"

struct LMSMessage {
    LMSBinBase mBase;
    int mTextHashTable;
    int mTextBlock;
    int mAtrBlock;
    int mAtoBlock;
    int mTsyBlock; 
};