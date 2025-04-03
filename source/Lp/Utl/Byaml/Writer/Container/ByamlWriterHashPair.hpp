#pragma once

#include <sead/container/seadListImpl.h>

namespace Lp::Utl {
    struct ByamlWriterData;
    struct ByamlWriterHashPair {
        sead::ListNode mListNode;
        ByamlWriterHashPair* mSelf;  /* I would think this is another ListNode, but this is seemingly always just itself? wut? */
        ByamlWriterHashPair* mSortedNext;
        const char* mKey;
        ByamlWriterData* mValue;
    };
}