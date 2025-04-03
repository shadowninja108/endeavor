#pragma once

#include <sead/prim/seadSafeString.hpp>
#include <sead/resource/seadResource.h>
#include <sead/heap/seadHeap.h>

#include <gsys/Model/ModelResource.hpp>

namespace Lp::Sys {
    struct ModelArc {
        sead::DirectResource* mArchive;
        gsys::ModelResource* mModelResource;

        ModelArc();
        ModelArc(sead::SafeString const&, sead::Heap *, bool, gsys::ModelResource::CreateArg const*);
        ModelArc(sead::SafeString const&, sead::Heap *, sead::Heap * ,bool, gsys::ModelResource::CreateArg const*);
        ModelArc(sead::DirectResource const*, sead::SafeString const&, sead::Heap *, gsys::ModelResource::CreateArg const*);
        void load(sead::SafeString const&, sead::Heap *, bool, gsys::ModelResource::CreateArg const*);
        void load(sead::SafeString const&, sead::Heap *, sead::Heap *, bool, gsys::ModelResource::CreateArg const*);
        void initializeCmn(sead::DirectResource const*, sead::SafeString const&, sead::Heap *, gsys::ModelResource::CreateArg const*);

        static void getFullPath(sead::FixedSafeString<256>*, sead::SafeString const&);
        static bool checkResExist(sead::SafeString const&);
    };
}