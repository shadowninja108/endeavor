#pragma once

#include "basis/seadTypes.h"
#include "seadStreamSrc.h"
#include "seadStream.h"

namespace sead {
    struct RamStreamSrc : public sead::StreamSrc {
        void* mBuffer;
        u32 mLength;
        int mPos;

        RamStreamSrc(void* buffer, u32 length); /* : mBuffer(buffer), mLength(length) {} */

        virtual ~RamStreamSrc();
        virtual u32 read(void* data, u32 size);
        virtual u32 write(const void* data, u32 size);
        virtual u32 skip(s32 offset);
        virtual void rewind();
        virtual bool isEOF();
    };

    struct RamWriteStream : public sead::WriteStream {
        sead::RamStreamSrc mSrc;

        RamWriteStream(void* buffer, u32 length, Stream::Modes mode); /* : mSrc(buffer, length) {
            mSrcPtr = &mSrc;
            setMode(mode);
        } */
    };
}