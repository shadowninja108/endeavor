#pragma once

#include <common.hpp>

#include <sead/heap/seadDisposer.h>
#include <sead/container/seadTList.h>
#include <sead/prim/seadRuntimeTypeInfo.h>
#include <sead/prim/seadSafeString.hpp>
#include <sead/math/seadVector.hpp>

#include <agl/lyr/RenderInfo.hpp>

namespace Cmn {
    struct DbgMenuPage;
    struct DbgMenuItem : sead::IDisposer {
        SEAD_RTTI_BASE(DbgMenuItem);

        sead::TListNode<DbgMenuItem*> mListNode;
        bool mEnabled = true;
        sead::FixedSafeString<64> mLabel;
        uint mLabelHash;
        DbgMenuPage* mParentPage;

        DbgMenuItem() : mListNode(this) {};
        virtual ~DbgMenuItem();
        virtual void reset();
        virtual void makeValueString(sead::BufferedSafeString&);
        virtual float calcValueStringWidth();
        /* TODO: probably returns enums? */
        virtual int onDecide_();
        virtual int editCalc_();
        virtual void editDraw_(agl::lyr::RenderInfo const&, sead::Vector2f const&);
    };
    static_assert(sizeof(DbgMenuItem) == 0xB0);
}