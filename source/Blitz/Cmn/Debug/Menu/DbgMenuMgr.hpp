#pragma once

#include <sead/heap/seadDisposer.h>

#include <agl/lyr/RenderInfo.hpp>

#include "DbgMenuPage.hpp"

namespace Cmn {
    struct DbgMenuMgr : public DbgMenuPage {
        SEAD_SINGLETON_DISPOSER(DbgMenuMgr);

        int field_40;
        sead::OffsetList<DbgMenuPage> mPages;
        bool mShowMenu;

        virtual ~DbgMenuMgr();

        void calc();
        void draw(agl::lyr::RenderInfo const&);
        bool isEnable() const;
        void setEnable(bool);
        void appendPagePath(sead::BufferedSafeString const&);
    };
    static_assert(sizeof(DbgMenuMgr) == 0x118);
}