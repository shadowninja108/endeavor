#pragma once

namespace Lp::Utl {
    
    /* TODO: this doesn't seem right... */
    template<bool Value, typename IfTrue, typename IfFalse>
    struct Conditional {};
    template<typename IfTrue, typename IfFalse>
    struct Conditional<false, IfTrue, IfFalse> {
        using Type = IfFalse;
    };
    template<typename IfTrue, typename IfFalse>
    struct Conditional<true, IfTrue, IfFalse> {
        using Type = IfTrue;
    };

    template<typename T>
    struct IsFloatingPoint {
        static const bool cResult = false;
    };
    template<>
    struct IsFloatingPoint<float> {
        static const bool cResult = true;
    };
    template<>
    struct IsFloatingPoint<double> {
        static const bool cResult = true;
    };
}