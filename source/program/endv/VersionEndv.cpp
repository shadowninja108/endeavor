#include "Version.hpp"

namespace endv::version {
    SEAD_ENUM_EX_VALUES(
        Type,
        static_cast<int>(0xcac1b8f6),   /* "Build 1" */
        static_cast<int>(0x43e761c4)    /* "Build 2" */
    )
}