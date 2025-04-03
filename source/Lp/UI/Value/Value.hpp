#pragma once

#include "ValueBase.hpp"

namespace Lp::UI  {
    template<typename T>
    struct Value : public ValueBase {
        T mValue;
    };
}