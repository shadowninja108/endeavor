#pragma once

#include <heap/seadHeap.h>
#include <LibMessageStudio/LMS.hpp>

namespace sead {
    struct MessageSetBase {
        LMSMessage* mLMS;
        int mTextCount;

        bool initialize(void* data, sead::Heap* heap);
        void finalize();
        void* getInitializeData() const;
        int calcTextSizeByIndex(int) const;
        bool searchTextLabelByIndex(sead::BufferedSafeString*, int) const;

        virtual ~MessageSetBase();

        static void* allocForLibms(ulong);
        static void freeForLibmx(void*);
    };
}