#pragma once

#include "ByamlWriterBigData.hpp"

namespace Lp::Utl {
    struct ByamlWriterBinary : public ByamlWriterBigData {
        const void* mData;
        int mSize;

        virtual ~ByamlWriterBinary();
        int getTypeCode() const; /* TODO: */
        void print(int) const;
        virtual int calcBigDataSize() const;
        virtual void writeBigData(sead::WriteStream*) const;
    };
}