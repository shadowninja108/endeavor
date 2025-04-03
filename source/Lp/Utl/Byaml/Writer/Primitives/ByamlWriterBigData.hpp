#pragma once

#include "ByamlWriterData.hpp"

namespace Lp::Utl {
    struct ByamlWriterBigDataList;
    struct ByamlWriterBigData : public ByamlWriterData {
        ByamlWriterBigDataList* mParent;
        int mOffset;

        virtual ~ByamlWriterBigData();
        virtual void write(sead::WriteStream*) const;
        virtual int calcBigDataSize() const;
        virtual void writeBigData(sead::WriteStream*) const;
    };
}