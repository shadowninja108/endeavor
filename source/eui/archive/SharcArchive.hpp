#pragma once

#include <sead/resource/seadSharcArchiveRes.h>
#include <sead/filedevice/seadArchiveFileDevice.h>

namespace eui {
    struct SharcArchive {

        struct FileReader {
            sead::ArchiveFileDevice mDevice;    /* mDevice.mArchive = sharc->mArchive; */
            int mCurrentIndex;
            sead::DirectoryHandle mDirHandle;
            sead::DirectoryEntry mDirEntry;

            ~FileReader();
            bool readNext();            
        };

        sead::SharcArchiveRes* mArchive;

        ~SharcArchive();
        void initialize(sead::Heap* heap, void* data, int size);
    };
}