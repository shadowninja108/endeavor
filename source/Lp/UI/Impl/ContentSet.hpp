#pragma once

#include <sead/container/seadOffsetList.h>

#include "ContentBase.hpp"
#include "Name.hpp"

namespace Lp::UI::Impl {
    struct ContentSet {
        struct Connection : public ContentBase {
            /* TODO: ? */
        };
        struct Item {
            sead::ListNode mListNode;
            Name field_10;
            Connection mConnection;
            int field_40;
            TypeInfo const* field_48;
        };
        
        sead::OffsetList<Item> mChildren;
        Item mRootItem;
    };
}