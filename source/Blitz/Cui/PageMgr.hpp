#pragma once

#include <sead/heap/seadHeap.h>
#include <sead/container/seadOffsetList.h>

#include <Lp/UI/PageHolder.hpp>

#include "PageHandler.hpp"

namespace Cui {
    struct PageMgr {
        sead::Heap* mHeap;
        Lp::UI::PageHolder* mPageHolder;
        sead::OffsetList<PageHandler> mPageHandlers;
    };
}