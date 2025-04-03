#pragma once

#include <sead/container/seadTList.h>

#include "ByamlWriterContainer.hpp"
#include "../ByamlWriterStringTable.hpp"

namespace Lp::Utl {
    struct ByamlWriterArray : public ByamlWriterContainer {

        sead::TList<ByamlWriterData*> mValues;
        ByamlWriterStringTable* mStringTable;

        virtual ~ByamlWriterArray();
        int calcPackSize() const;
        int getTypeCode() const; /* TODO: */
        void write(sead::WriteStream*) const;
        void print(int) const;
        
        virtual void addBool(bool);
        virtual void addInt(int);
        virtual void addUInt(unsigned int);
        virtual void addFloat(float);
        virtual void addInt64(long, ByamlWriterBigDataList*);
        virtual void addUInt64(unsigned long, ByamlWriterBigDataList*);
        virtual void addDouble(double, ByamlWriterBigDataList*);
        virtual void addBinary(void const*, unsigned int, ByamlWriterBigDataList*);
        virtual void addString(char const*);
        virtual void addHash(ByamlWriterHash*);
        virtual void addArray(ByamlWriterArray*);
        virtual void addNull();

        virtual void writeContainer(sead::WriteStream*) const;
        virtual bool isArray() const;
        virtual void deleteData();
    };
}