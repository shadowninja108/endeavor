#pragma once

#include <sead/stream/seadStream.h>

#include "../Primitives/ByamlWriterData.hpp"
#include "../ByamlWriterBigDataList.hpp"

namespace Lp::Utl {
    struct ByamlWriterHash;
    struct ByamlWriterArray;

    struct ByamlWriterContainer : public ByamlWriterData {

        virtual bool isContainer() const;

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

        virtual void writeContainer(sead::WriteStream*) const = 0;
        virtual bool isHash() const;
        virtual bool isArray() const;
        virtual void deleteData() = 0;
    };
}