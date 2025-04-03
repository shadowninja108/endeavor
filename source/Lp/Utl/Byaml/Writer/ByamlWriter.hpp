#pragma once

#include <sead/heap/seadHeap.h>
#include <sead/hostio/seadHostIOCurve.h>
#include <sead/container/seadTList.h>
#include <sead/time/seadCalendarTime.h>

#include "../Iter/ByamlIter.hpp"
#include "ByamlWriterStringTable.hpp"
#include "ByamlWriterBigDataList.hpp"
#include "Container/ByamlWriterContainer.hpp"

namespace Lp::Utl {
    struct ByamlWriter {
        sead::Heap* mHeap;
        ByamlWriterStringTable* mHashKeyStringTable;
        ByamlWriterStringTable* mStringTable;
        sead::TList<ByamlWriterContainer*> mContainers;
        ByamlWriterBigDataList* mBigDataList;
        ByamlWriterContainer** mContainerStack;
        int mContainerStackMax;
        int mContainerIdx;
        bool mAutoFree;

        ByamlWriter(sead::Heap*, bool);

        virtual ~ByamlWriter();
        void addBool(bool);
        ByamlWriterArray* getArrayCurrentContainer();
        void addInt(int);
        void addInt(int const*, int);
        void pushArray();
        void pop();
        void addUInt(unsigned int);
        void addUInt(unsigned int const*, int);
        void addFloat(float);
        void addFloat(float const*, int);
        void addInt64(long);
        void addUInt64(unsigned long);
        void addDouble(double);
        void addBinary(void const*, unsigned int);
        void addString(char const*);
        void addNull();
        void addBool(char const*, bool);
        ByamlWriterHash* getHashCurrentContainer();
        void addInt(char const*, int);
        void addInt(char const*, int const*, int);
        void pushArray(char const*);
        void addUInt(char const*, unsigned int);
        void addUInt(char const*, unsigned int const*, int);
        void addFloat(char const*, float);
        void addFloat(char const*, float const*, int);
        void addInt64(char const*, long);
        void addUInt64(char const*, unsigned long);
        void addDouble(char const*, double);
        void addBinary(char const*, void const*, unsigned int);
        void addString(char const*, char const*);
        void addCurve(char const*, sead::hostio::Curve<float> const&);
        void addCalendar(char const*, sead::CalendarTime const&);
        void addNull(char const*);
        void pushHash();
        void pushContainer(ByamlWriterContainer*);
        void pushHash(char const*);
        void pushIter(ByamlIter const&);
        void pushLocalIter(ByamlIter const&, char const*);
        void pushIter(char const*, ByamlIter const&);
        int calcHeaderSize() const;
        int calcPackSize() const;
        void write(sead::WriteStream*);
        void print() const;
        ByamlWriterContainer* getCurrentContainer();
    };
}