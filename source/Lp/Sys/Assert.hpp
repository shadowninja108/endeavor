#pragma once

#include <common.hpp>

namespace Lp::Sys {
    NORETURN void cpAssertFmt(const char*,int , const char*, ...);
    NORETURN void cpAssertNoFmt(const char*,int , const char*);
    NORETURN void cpAssertIsStack(bool, const void*);
    NORETURN void cpAssertProduct(int);
    NORETURN void cpWarning(int, const char*, int, const char*);
    NORETURN void cpWarningMgrSetFalseLastAddOk();

    #define LP_ASSERT_NOFMT(expr)                               \
        if(!(expr))                                             \
            ::Lp::Sys::cpAssertNoFmt(__FILE_NAME__, __LINE__, #expr)
}