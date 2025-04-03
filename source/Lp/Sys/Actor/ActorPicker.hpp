#pragma once

#include <sead/container/seadRingBuffer.h>
#include <sead/prim/seadSafeString.hpp>
#include <sead/prim/seadDelegate.h>

#include <cstddef>
#include <array>

namespace Lp::Sys {
    struct Actor;
    struct ActorPicker {
        struct ArgCb {
            int field_0;
            Actor* mActor;
            bool field_10;
            bool field_11;
            bool field_12;
            bool field_13;
            int field_14;
            int field_18;
            int field_1C;
            int field_20;
            int field_24;
        };
        struct alignas(8) Unk : std::array<std::byte, 0x18> {};

        uintptr_t field_8;
        bool field_10;

        sead::FixedRingBuffer<Unk, 1024> mUnkBuffer;
        Actor* mFocusedActor;
        int mFocusedLayer;
        float field_603c; /* Blitz initializes as 50.0 */
        float field_6040; /* Blitz initializes as 600.0 */
        sead::RingBuffer<sead::FixedSafeString<32>> mNameList1;
        sead::RingBuffer<sead::FixedSafeString<32>> mNameList2;

        using CbType = sead::Delegate1<ActorPicker, ArgCb const&>;
        CbType* mCallbackPtr;
        CbType mDefaultCallback;


        virtual ~ActorPicker();
        void defaultCallback(ArgCb const&);
        void calc();
        void selectNode(Actor*);
        
    };
}