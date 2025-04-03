#pragma once

#include <sead/heap/seadDisposer.h>
#include <sead/thread/seadCriticalSection.h>
#include <sead/thread/seadReadWriteLock.h>
#include <sead/filedevice/nin/seadNinContentFileDeviceNin.h>
#include <sead/filedevice/nin/seadNinAocFileDeviceNin.h>
#include <sead/filedevice/nin/seadNinHostIOFileDevice.h>
#include <sead/filedevice/nin/seadNinSDFileDeviceNin.h>

namespace Lp::Sys {
    struct FileDeviceHolder {
        /* TODO: where does this come from? */
        uintptr_t field_8;
        sead::CriticalSection mCS;
        sead::ReadWriteLock mRWLock;
        SEAD_SINGLETON_DISPOSER(FileDeviceHolder);
        public:
        sead::NinContentFileDevice* mContent;
        sead::NinAocFileDevice* mAoc;
        sead::NinHostIOFileDevice* mDialog; /* Lp::Sys::DialogFileDevice* */
        sead::NinSDFileDevice* mSD;

        virtual ~FileDeviceHolder();
    };
}