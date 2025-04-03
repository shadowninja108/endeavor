#pragma once

#include <sead/prim/seadSafeString.hpp>

namespace eui {
    struct MessageString {
        const char16_t* mStr;
        int mLength;

        MessageString();
        MessageString(int, const char16_t*);
        MessageString(const char16_t*, const char16_t*);
        MessageString(sead::WSafeString const&);
        MessageString(MessageString const&);
        void operator=(MessageString const&);
        char16_t& operator[](int) const;
        /* begin */
        /* end */
        /* toIterator */
        bool tryMakeTagStrippedString(sead::WBufferedSafeString*) const;
    };
}