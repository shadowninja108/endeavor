#pragma once

#include "ByamlWriterData.hpp"

namespace Lp::Utl {
    struct ByamlWriterBool : public ByamlWriterData {
        bool mData;

        virtual ~ByamlWriterBool();
        int getTypeCode() const; /* TODO: */
        void write(sead::WriteStream*) const;
        void print(int) const;
    };
}