#pragma once

#include <common.hpp>

#include <sead/heap/seadHeap.h>
#include <sead/prim/seadSafeString.hpp>

namespace Lp::Utl {
    struct TextSave {
        bool mSaved;
        int mBufferPosition;
        int mBufferSize;
        char* mBuffer;
        sead::HeapSafeString* mFileName;
        sead::Heap* mHeap;

        TextSave(sead::SafeString const& fileName, uint bufferSize);

        virtual ~TextSave();
        void save(bool makeDirectory);
        void print(const char*, ...);
        char* getPtr();
        void outBinary(uchar const*, uint);
        void printFilename();
        int getColumn();
        void alignColumn(uint);
    };
}