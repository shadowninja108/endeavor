#pragma once

#include <sead/container/seadTList.h>
#include <sead/stream/seadStream.h>

namespace Lp::Utl {
    struct ByamlWriterStringTable {
        sead::TList<char*> mStrings;

        virtual ~ByamlWriterStringTable();
        char* tryAdd(char const*);
        int calcHeaderSize() const;
        int calcContentSize() const;
        int calcPackSize() const;
        bool isEmpty() const;
        int calcIndex(char const*) const;
        void write(sead::WriteStream*) const;
        void print() const;
    };
}