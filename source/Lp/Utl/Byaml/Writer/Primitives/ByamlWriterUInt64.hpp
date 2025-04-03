#pragma once

#include "ByamlWriterBigData.hpp"

namespace Lp::Utl {
    struct ByamlWriterUInt64 : public ByamlWriterBigData {
        uint64_t mData;

        virtual ~ByamlWriterUInt64();
        int getTypeCode() const; /* TODO: */
        void print(int) const;
        virtual int calcBigDataSize() const;
        virtual void writeBigData(sead::WriteStream*) const;
    };
}