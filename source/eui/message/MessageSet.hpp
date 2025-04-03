#pragma once

#include <sead/resource/message/seadMessageSet.h>
#include "MessageString.hpp"

namespace eui {
    struct MessageSet : public sead::MessageSetBase {
        virtual ~MessageSet();

        MessageString findMessage(char const*) const;
        MessageString tryFindMessage(char const*) const;
        MessageString findMessageByIndex(int) const;
        MessageString tryFindMessageByIndex(int) const;
        bool hasMessageByIndex(int) const;
        bool hasMessage(char const*) const;
        int calcMessageLength(char const*) const;
        int calcMessageLengthByIndex(int) const;
    };
}