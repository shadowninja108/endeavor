#pragma once

#include <sead/stream/seadStream.h>

namespace Lp::Utl {
    struct ByamlWriterData {
        virtual ~ByamlWriterData();
        void makeIndex();
        int calcPackSize() const;
        int getTypeCode() const; /* TODO: */
        bool isContainer() const;
        void write(sead::WriteStream*) const;
        void print(int) const;
    };
}