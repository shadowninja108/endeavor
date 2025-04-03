#pragma once

#include "ByamlWriterBigData.hpp"

namespace Lp::Utl {
    struct ByamlWriterInt64 : public ByamlWriterBigData {
        int64_t mData;

        virtual ~ByamlWriterInt64();
        int getTypeCode() const; /* TODO: */
        void print(int) const;
        virtual int calcBigDataSize() const;
        virtual void writeBigData(sead::WriteStream*) const;
    };
}