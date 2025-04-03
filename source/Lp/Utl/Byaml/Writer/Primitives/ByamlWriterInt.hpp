#pragma once

#include "ByamlWriterData.hpp"

namespace Lp::Utl {
    struct ByamlWriterInt : public ByamlWriterData {
        int mData;

        virtual ~ByamlWriterInt();
        int getTypeCode() const; /* TODO: */
        void write(sead::WriteStream*) const;
        void print(int) const;
    };
}