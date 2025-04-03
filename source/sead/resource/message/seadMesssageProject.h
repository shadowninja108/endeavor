#pragma once

#include <container/seadBuffer.h>
#include <gfx/seadColor.h>
#include <heap/seadHeap.h>
#include <LibMessageStudio/LMS.hpp>

namespace sead {
    struct MessageProject {
        /* Unofficial names. */
        struct GradationColor {
            sead::Color4u8 mColor1;
            sead::Color4u8 mColor2;
        };
        struct Style {
            int mRegionWidth;
            int mLineNum;
            int mFontIndex;
            int mBaseColorIndex;
        };
        struct AttrIndex {
            int mType;
            int mOffset;
        };

        LMSProject* mProject;
        Buffer<GradationColor> mGradationColors;
        Buffer<Style> mStyles;
        Buffer<AttrIndex> mAttrs;
        int mContentsNum;

        bool initialize(void* data, Heap* heap);
        void finalize();
        void* getInitializeData() const;

        virtual ~MessageProject();

        static void* allocForLibms_(ulong);
        static void freeForLibms_(void*);
    };
}