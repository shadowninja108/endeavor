#pragma once

#include <sead/prim/seadDelegate.h>
#include <Lp/Sys/Assert.hpp>

#include "DbgMenuItem.hpp"

namespace Cmn {
    struct DbgMenuItemPush : public DbgMenuItem {
        SEAD_RTTI_OVERRIDE(DbgMenuItemPush, DbgMenuItem);

        sead::AnyDelegate mCB;

        DbgMenuItemPush(sead::SafeString const& label, void (*delegate)()) {
            mLabel = label;
            mCB = sead::DelegateFunc(delegate);
        }

        template<typename T>
        DbgMenuItemPush(sead::SafeString const& label, T*, void (T::*delegate)()) {
            mLabel = label;
            mCB = sead::Delegate(delegate);
        }

        /* TODO: probably returns enums? */
        virtual int onDecide_();
        virtual int editCalc_();
        virtual void editDraw_(agl::lyr::RenderInfo const&, sead::Vector2f const&);        
        
        static auto Create(sead::SafeString const& label, void (*delegate)()) {
            return new DbgMenuItemPush(label, delegate);
        }

        template<typename T>
        static auto Create(sead::SafeString const& label, T* self, void (T::*delegate)()) {
            return new DbgMenuItemPush(label, self, delegate);
        }
    };

    static_assert(sizeof(DbgMenuItemPush) == 0xD0);
}