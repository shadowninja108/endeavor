#pragma once

#include <common.hpp>

#include <sead/container/seadSafeArray.h>
#include <sead/container/seadBuffer.h>
#include <sead/container/seadPtrArray.h>

#include <gsys/Model/ModelScene.hpp>

#include <Game/FieldEnvSet.hpp>
#include "Def/Hour.hpp"

#include "../Scene/DbgSetting/MapSort.hpp"


namespace Cmn {
    /* Note: The layout of this changed significantly between target build and 3.1.0. */
    struct ViewerEnvChanger {
        gsys::ModelScene* mModelScene;
        DbgSetting::MapSort* mDbgMapSort;
        int mEnvIndex;
        char field_1C;

        static constexpr int s_BucketCount = 4;
        using Bucket = sead::SafeArray<sead::Buffer<Game::FieldEnvSet>, static_cast<int>(Def::Hour::End)>;

        sead::SafeArray<Bucket, s_BucketCount> mFieldEnvSets;

        virtual ~ViewerEnvChanger();
        void applyEnvSet();
    };
}