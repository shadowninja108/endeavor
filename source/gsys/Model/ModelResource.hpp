#pragma once

#include <sead/container/seadPtrArray.h>

#include "ModelShaderArchive.hpp"
#include "IModelCallback.hpp"

namespace gsys {
    struct ModelResource {
        struct CreateArg {
            void* mBinary;
            sead::FixedPtrArray<ModelShaderArchive, 256> mShaderArchives;
            char field_818;
            char field_819;
            char field_81A;
            char field_81B;
            int field_81C;
            IModelCallback* mCallback;
        };
    };
}