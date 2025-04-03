#pragma once

#include <agl/utl/param/Parameter.hpp>

namespace Lp::Sys {
    template<typename T>
    struct Param;

    template<typename T>
    struct AglParam : public agl::utl::Parameter<T> {
        Param<T>* mParent;
        agl::utl::ParameterObj mObj;

        virtual ~AglParam();
        virtual void postApplyResource_(void const*, ulong);
    };
}