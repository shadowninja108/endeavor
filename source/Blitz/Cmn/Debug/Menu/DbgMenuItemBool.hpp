#pragma once

#include "DbgMenuItemCombo.hpp"

#include <Lp/Sys/Assert.hpp>

namespace Cmn {
    struct DbgMenuItemBool : DbgMenuItemCombo {
        SEAD_RTTI_OVERRIDE(DbgMenuItemBool, DbgMenuItemCombo);

        bool* mOutPtr;

        DbgMenuItemBool(sead::SafeString const& label, bool& value, void (*delegate)()) {
            mLabel = label;
            mCB = sead::DelegateFunc(delegate);
            mOutPtr = &value;
            LP_ASSERT_NOFMT(!sead::MemUtil::isStack(&value));
        }

        template<typename T>
        DbgMenuItemBool(sead::SafeString const& label, bool& value, T*, void (T::*delegate)()) {
            mLabel = label;
            mCB = sead::Delegate(delegate);
            mOutPtr = &value;
            LP_ASSERT_NOFMT(!sead::MemUtil::isStack(&value));
        }

        virtual int getComboNum_() const;
        virtual int getComboIdx() const;
        virtual int onChangeComboIdx_(int);
        virtual void makeComboString_(int, sead::BufferedSafeString*) const;

        static auto Create(sead::SafeString const& label, bool& value, void (*delegate)()) {
            return new DbgMenuItemBool(label, value, delegate);
        }

        template<typename T>
        static auto Create(sead::SafeString const& label, bool& value, T* self, void (T::*delegate)()) {
            return new DbgMenuItemBool(label, value, self, delegate);
        }
    };
}