#pragma once

#include <sead/prim/seadSafeString.hpp>
#include <sead/container/seadSafeArray.h>

#include "Def.hpp"

namespace DbgSetting {
    struct MapSort {
        static constexpr int s_BucketCount = (Category_EndMap-Category_StartMap)+1;

        /* Note: This is 1024 in the target build, but is 2048 on 3.1.0. */
        static constexpr int s_BucketMaxSize = 1024;

        template<typename T>
        using Bucket = sead::SafeArray<T, s_BucketMaxSize>;
        using String = sead::FixedSafeString<64>;

        /* Fairly sure they intended this to be s_BucketCount size. Nice job guys. */
        sead::SafeArray<int, s_BucketMaxSize> mBucketCounts;

        sead::SafeArray<Bucket<int>,    s_BucketCount> mIds;
        sead::SafeArray<Bucket<String>, s_BucketCount> mFilePaths;
        sead::SafeArray<Bucket<String>, s_BucketCount> mNames;

        void load();
        void sort(sead::SafeString const& name);
        void add(int bucket, int id, sead::SafeString const& filePath, sead::SafeString const& name);
    };
    static_assert(sizeof(MapSort) == 0x169000);
}