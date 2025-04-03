#pragma once

#include <sead/container/seadRingBuffer.h>

#include "TypeInfo.hpp"
#include "../Impl/Observer.hpp"

namespace Lp::UI {
    namespace Impl {
        struct ContentSet;
    }

    struct ContentBase {
        /* TODO: */
        int mValueType;
        TypeInfo* const mTypeInfo;

        virtual bool canSetBy(TypeInfo const&) const;
        virtual bool canGetAs(TypeInfo const&) const;
        virtual void searchImpl(char const*, uint, Impl::ContentSet*, sead::RingBuffer<Impl::Observer>*);
    };
}