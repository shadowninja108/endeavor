#pragma once

#include "ByamlWriterData.hpp"

namespace Lp::Utl {
    struct ByamlWriterFloat : public ByamlWriterData {
        float mData;

        virtual ~ByamlWriterFloat();
        int getTypeCode() const; /* TODO: */
        void write(sead::WriteStream*) const;
        void print(int) const;
    };
}