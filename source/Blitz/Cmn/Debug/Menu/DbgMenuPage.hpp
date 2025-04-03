#pragma once

#include <sead/heap/seadDisposer.h>
#include <sead/prim/seadRuntimeTypeInfo.h>
#include <sead/prim/seadSafeString.hpp>
#include <sead/container/seadListImpl.h>
#include <sead/container/seadOffsetList.h>

#include "DbgMenuItem.hpp"

namespace Cmn {
    struct DbgMenuPage : sead::IDisposer {
        SEAD_RTTI_BASE(DbgMenuPage);

        sead::TListNode<DbgMenuItem*> mListNode;
        sead::FixedSafeString<64> mLabel;
        sead::OffsetList<DbgMenuItem> mChildItems;
        int field_b0;
        int mPageItemNum;
        int field_b8;
        char field_bc;

        DbgMenuPage(sead::SafeString const&);

        virtual ~DbgMenuPage();

        void reset();
        bool addItem(DbgMenuItem*);
        DbgMenuItem* findItem(uint, bool) const;
        void removeItem(DbgMenuItem*);
        DbgMenuItem* findItem(sead::SafeString const&, bool);
        DbgMenuPage* findPage(sead::SafeString const&, bool);
        void calc_();
        void draw_(agl::lyr::RenderInfo const&);
    };
    static_assert(sizeof(DbgMenuPage) == 0xC0);
}