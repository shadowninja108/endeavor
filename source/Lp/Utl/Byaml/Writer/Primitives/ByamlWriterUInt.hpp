#pragma once

#include <common.hpp>

#include "ByamlWriterData.hpp"

namespace Lp::Utl {
    struct ByamlWriterUInt : public ByamlWriterData {
        uint mData;

        virtual ~ByamlWriterUInt();
        int getTypeCode() const; /* TODO: */
        void write(sead::WriteStream*) const;
        void print(int) const;
    };
}