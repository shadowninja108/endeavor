#pragma once

#include "DbgMenuItem.hpp"
#include "DbgMenuPage.hpp"

namespace Cmn {
    struct DbgMenuItemPage : public DbgMenuItem {
        SEAD_RTTI_OVERRIDE(DbgMenuItemPage, DbgMenuItem);

        DbgMenuPage *mPage;
        
        virtual ~DbgMenuItemPage();
        virtual void reset();
        virtual void makeValueString(sead::BufferedSafeString&);
        /* TODO: probably returns enums? */
        virtual int onDecide_();
    };
}