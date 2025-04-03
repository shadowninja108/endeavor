#pragma once

#include <sead/container/seadOffsetList.h>

#include "ByamlWriterContainer.hpp"

namespace Lp::Utl {
    struct ByamlWriterHash : public ByamlWriterContainer {
        /* This should be a list of HashPair, but nothing seems to line up? TODO: what is going on here... */
        sead::ListImpl mPairList;

        virtual ~ByamlWriterHash();
        int calcPackSize() const;
        int getTypeCode() const; /* TODO: */
        void write(sead::WriteStream*) const;
        void print(int) const;
        
        virtual void addBool(char const*, bool);
        virtual void addInt(char const*, int);
        virtual void addUInt(char const*, unsigned int);
        virtual void addFloat(char const*, float);
        virtual void addInt64(char const*, long, ByamlWriterBigDataList*);
        virtual void addUInt64(char const*, unsigned long, ByamlWriterBigDataList*);
        virtual void addDouble(char const*, double, ByamlWriterBigDataList*);
        virtual void addBinary(char const*, void const*, unsigned int, ByamlWriterBigDataList*);
        virtual void addString(char const*, char const*);
        virtual void addHash(char const*, ByamlWriterHash*);
        virtual void addArray(char const*, ByamlWriterArray*);
        virtual void addNull(char const*);

        virtual void writeContainer(sead::WriteStream*) const;
        virtual bool isHash() const;
        virtual void deleteData();
    };
}