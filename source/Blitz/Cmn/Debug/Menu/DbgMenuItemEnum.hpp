#pragma once

#include "DbgMenuItemCombo.hpp"

namespace Cmn {

    struct DbgMenuItemEnum : public DbgMenuItemCombo {
        SEAD_RTTI_OVERRIDE(DbgMenuItemEnum, DbgMenuItemCombo);

        template<typename T>
        DbgMenuItemEnum(sead::SafeString const&, T&);

        template<typename ContainerT, typename PrimitiveT>
        DbgMenuItemEnum(ContainerT const&, PrimitiveT&);

        struct Accessor {
            virtual ~Accessor();
            virtual int getEnumNum() const = 0;
            virtual int getEnumIdx() const = 0;
            virtual int setEnumIdx() = 0;
            virtual const char* getEnumText() const = 0;
        };

        template<typename T>
        struct AccessorEnum : public Accessor {
            virtual int getEnumNum() const;
            virtual int getEnumIdx() const;
            virtual int setEnumIdx();
            virtual const char* getEnumText() const;
        };

        Accessor* mAccessor;
    };
}