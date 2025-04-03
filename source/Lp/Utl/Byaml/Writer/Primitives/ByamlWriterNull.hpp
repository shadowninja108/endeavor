#pragma once

#include "ByamlWriterData.hpp"

namespace Lp::Utl {
    struct ByamlWriterNull : public ByamlWriterData {
        virtual ~ByamlWriterNull();
        int getTypeCode() const; /* TODO: */
        void write(sead::WriteStream*) const;
        void print(int) const;
    };
}