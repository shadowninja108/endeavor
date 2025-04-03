#pragma once

#include <framework/menu/seadDebugMenuItemBase.h>
#include <framework/menu/seadDebugMenuSkinBase.h>
#include <container/seadListImpl.h>
#include <heap/seadDisposer.h>

namespace sead {
    struct DebugMenu;
    struct DebugMenuPageBase : public IDisposer {
        SEAD_RTTI_BASE(DebugMenuPageBase);

        /* TODO: determine difference (and how tf to deal with this in oead). */
        public:
        ListNode mListNode1;
        ListNode mListNode2;
        DebugMenu* mMenu;
        int mPageId;
        int field_4C;
        int field_50;
        char field_54;
        DebugMenuItemBase* field_58;
        DebugMenuSkinBase* mSkin;
        FixedSafeString<96> mTitle;

        virtual ~DebugMenuPageBase();
        virtual void calc();
        virtual void draw(DrawContext*);
        virtual void dump(); 
        virtual int getItemSize_() const = 0;
        virtual DebugMenuItemBase *getNthItem_(int) = 0;
        virtual int getIndexOf_(DebugMenuItemBase *) = 0;
        virtual DebugMenuItemBase *getNextItem_(DebugMenuItemBase *) = 0;
        virtual DebugMenuItemBase *getParentItem_(DebugMenuItemBase *) = 0;
        virtual int getLineNum_() const;
    };
}