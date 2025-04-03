#pragma once

#include "ByamlWriterBigData.hpp"

namespace Lp::Utl {
    struct ByamlWriterDouble : public ByamlWriterBigData {
        double mData;

        virtual ~ByamlWriterDouble();
        int getTypeCode() const; /* TODO: */
        void print(int) const;
        virtual int calcBigDataSize() const;
        virtual void writeBigData(sead::WriteStream*) const;
    };
}