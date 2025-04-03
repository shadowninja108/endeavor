#pragma once

#include <common.hpp>

namespace Lp::Utl {
    struct ByamlData;
    
    class ByamlHeader {
        u16 mMagic;
        u16 mVersion;
        u32 mHashKeyTableOffset;
        u32 mStringTableOffset;
        u32 mDataOffset;

        public:
        u16 getTag() const;
        bool isInvertOrder() const;
        u16 getVersion() const;
        u32 getHashKeyTableOffset() const;
        u32 getStringTableOffset() const;
        u32 getDataOffset() const;
    };

    struct ByamlIter {
        const uchar* mData;
        const ByamlHeader* mHeader;

        ByamlIter();
        ByamlIter(const uchar*);
        ByamlIter(ByamlIter const&);
        ByamlIter(const uchar*, const uchar*);
        void operator=(const ByamlIter);
        bool isValid() const;
        bool isTypeHash() const;
        bool isTypeArray() const;
        bool isTypeContainer() const;
        bool isExistKey(const char*) const;
        int getKeyIndex(char const*) const;
        bool isInvertOrder() const;
        int getSize() const;
        Lp::Utl::ByamlIter getIterByIndex(int) const;
        Lp::Utl::ByamlIter getIterByKey(const char*) const;
        bool getByamlDataByKey(ByamlData*, const char*) const;
    };
}