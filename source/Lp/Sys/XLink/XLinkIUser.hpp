#pragma once

#include <sead/container/seadPtrArray.h>
#include <sead/heap/seadHeap.h>
#include <XLink/LinkCommon/IUser.hpp>
#include <XLink/LinkCommon/ToolConnectionContext.hpp>
#include <XLink/LinkCommon/PropertyDefinition.hpp>
#include <gsys/Model/Model.hpp>
#include "XLinkActionSlotBase.hpp"

namespace Lp::Sys {
    struct XLinkIUser : public xlink2::IUser {
        sead::PtrArray<gsys::Model> mModels;
        sead::PtrArray<XLinkActionSlotBase> mActionSlots;
        sead::PtrArray<xlink2::PropertyDefinition> mLocalPropertyDefinitions;
        
        virtual void onXLinkSetupModels();
        virtual void onXLinkSetupActionSlot(sead::Heap*);
        virtual void onXLinkSetupProperty();
        virtual void onXLinkGetReservedAssetName(xlink2::ToolConnectionContext*) const;
        virtual void onXLinkCallClip(bool);
        virtual void onXLinkCalcPre();
        virtual void onXLinkCalcPost();
        virtual void onXLinkDestroy();
        virtual void onXLinkBeforeChangeAction(XLinkActionSlotBase const*, char const*, int);
        virtual void onXLinkAfterChangeAction(XLinkActionSlotBase const*);
        virtual const char* getXLinkName() const;
        virtual const char* getELinkName() const;
        virtual const char* getSLinkName() const;
    };
}