#pragma once

#include <concepts>
#include <framework/menu/seadDebugMenuPageBase.h>
#include <container/seadObjList.h>

namespace sead {
    template<typename T>
    requires std::derived_from<T, DebugMenuPageBase>
    struct DebugMenuPage : public DebugMenuPageBase {
        SEAD_RTTI_OVERRIDE(DebugMenuPage<T>, DebugMenuPageBase);

        public:
        ObjList<T> mItems;

        virtual int getItemSize_() const;
        virtual DebugMenuItemBase *getNthItem_(int);
        virtual int getIndexOf_(DebugMenuItemBase *);
        virtual DebugMenuItemBase *getNextItem_(DebugMenuItemBase *);
        virtual DebugMenuItemBase *getParentItem_(DebugMenuItemBase *);
    };
}