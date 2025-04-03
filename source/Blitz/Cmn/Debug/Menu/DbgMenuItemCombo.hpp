#pragma once

#include <sead/prim/seadDelegate.h>

#include "DbgMenuItem.hpp"

namespace Cmn {
    struct DbgMenuItemCombo : public DbgMenuItem {
        SEAD_RTTI_OVERRIDE(DbgMenuItemCombo, DbgMenuItem);

        int mIdx;
        int field_B4;
        int field_B8;
        sead::AnyDelegate mCB;

        virtual int getComboNum_() const = 0;
        virtual int getComboIdx() const = 0;
        virtual int onChangeComboIdx_(int) = 0;
        virtual void makeComboString_(int, sead::BufferedSafeString*) const = 0;

        float calcComboStringWidth(int) const;
    };
}