#pragma once

#include <sead/heap/seadHeap.h>
#include <sead/container/seadPtrArray.h>

#include "RenderDisplay.hpp"

namespace agl::lyr {
    struct RenderDisplay;
    struct Layer;
    struct LayerJob {
        enum class Type {
            Draw    = 0x0,
            SubDraw = 0x1,
            Begin   = 0x2,
            End     = 0x3,
            GPUCalc = 0x4,
        };

        sead::SafeString mTypeStr;
        Type mType;
        const Layer* mLayer;
        const RenderDisplay* field_28;
        int field_30;

        void initialize(Type, Layer const*, sead::Heap*);
        void finalize();
        void pushBackTo(RenderDisplay const*, int, sead::PtrArray<LayerJob>);

        virtual ~LayerJob();
        virtual void invoke();

        static bool compare(LayerJob* const, LayerJob* const);
    };
}