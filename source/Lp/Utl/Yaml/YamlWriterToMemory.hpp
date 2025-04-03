#pragma once

#include <sead/stream/seadStream.h>
#include <sead/stream/seadRamStream.h>

#include "YamlFormatter.hpp"

namespace Lp::Utl {
    struct YamlWriterToMemory : public YamlFormatter {
        uchar* mBuffer;
        uint mBufferSize;
        sead::RamWriteStream mStream;

        virtual ~YamlWriterToMemory();
        uint getUsedBufferSize() const;   
    };
}