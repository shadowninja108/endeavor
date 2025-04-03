#pragma once

#include "seadStream.h"
#include "seadStreamSrc.h"
#include "seadBufferStream.h"
#include <sead/filedevice/seadFileDevice.h>

namespace sead {
    struct FileDeviceStreamSrc : public StreamSrc {
        sead::FileHandle *mFileHandle;
        int mPosition;
        sead::FileHandle mHandle;
        char field_58;
        int mFileSize;

        virtual ~FileDeviceStreamSrc();
        virtual u32 read(void* data, u32 size);
        virtual u32 write(const void* data, u32 size);
        virtual u32 skip(s32 offset);
        virtual void rewind();
        virtual bool isEOF();
    };

    struct FileDeviceWriteStream : public WriteStream {
        FileDeviceStreamSrc mSrc;

        FileDeviceWriteStream(Modes);
        FileDeviceWriteStream(StreamFormat *);
        FileDeviceWriteStream(FileHandle *,Modes);
        FileDeviceWriteStream(FileHandle *,StreamFormat *);
        void setFileHandle(FileHandle*);
    };

    struct BufferFileDeviceWriteStream : public FileDeviceWriteStream {
        sead::BufferWriteStreamSrc mBufferedSrc;

        BufferFileDeviceWriteStream(Modes);
        BufferFileDeviceWriteStream(StreamFormat *);
        BufferFileDeviceWriteStream(FileHandle *,Modes);
        BufferFileDeviceWriteStream(FileHandle *,StreamFormat *);
    };
}