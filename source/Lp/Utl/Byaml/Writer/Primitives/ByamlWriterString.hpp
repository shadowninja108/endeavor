#pragma once

#include "ByamlWriterData.hpp"
#include "../ByamlWriterStringTable.hpp"

namespace Lp::Utl {
    struct ByamlWriterString : public ByamlWriterData {
        const char* mValue;
        ByamlWriterStringTable* mStringTable;

        virtual ~ByamlWriterString();
        virtual int getTypeCode() const;
        virtual void write(sead::WriteStream*) const;
        virtual void print() const;
    };
}