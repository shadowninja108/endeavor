#pragma once

#include <sead/prim/seadSafeString.hpp>
#include "PropertyType.hpp"

namespace xlink2 {
    struct PropertyDefinition {
        sead::FixedSafeString<64> mUserName;
        PropertyType mType;
        bool field_64;

        virtual ~PropertyDefinition();
    };

    struct F32PropertyDefinition : public PropertyDefinition {
        /* Inferred, but unsure it's ever actually used? */
        float mMin;
        float mMax;
    };

    struct S32PropertyDefinition : public PropertyDefinition {
        /* Inferred, but unsure it's ever actually used? */
        int mMin;
        int mMax;
    };

    struct EnumPropertyDefinition : public PropertyDefinition {
        struct Entry {
            const char* mName;
            int mIndex;
        };

        EnumPropertyDefinition(char const*, int, sead::Heap*, bool);
        EnumPropertyDefinition(char const*, int, bool, sead::Heap*, ...);
        EnumPropertyDefinition(char const*, int, char const**, bool, sead::Heap*);
        EnumPropertyDefinition(char const*, bool);

        void setEntries_(int, char const**);
        void entry(int, char const*);
        int getEntryKeyLength(unsigned int) const;
        int searchEntryValueByKey(char const*) const;
        const char* searchEntryKeyByValue(int) const;
        void setEntryBuf_(int, Entry*);
    };

    template<size_t Size>
    struct FixedEnumPropertyDefinition : public EnumPropertyDefinition {
        Entry mBuffer[Size];
    };
}