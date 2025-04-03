#pragma once

namespace Lp::Utl {
    struct ByamlStringTableIter {
        const char* mData;
        bool mIsInvertOrder;

        ByamlStringTableIter();
        ByamlStringTableIter(const char*, bool);

        int getSize() const;
        const char* getAddressTable() const;
        const char* getStringAddress(int) const;
        const char* getEndAddress() const;
        const char* getString(int) const;
        int getStringSize(int) const;
        int findStringIndex(const char*) const;
        bool isValidate() const;
    };
}