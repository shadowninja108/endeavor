#pragma once

#include <prim/seadSafeString.hpp>
#include <framework/menu/seadDebugMenuSkinBase.h>

namespace sead {
    struct DebugMenuItemBase {
        int field_8;
        int field_C;
        bool field_10;
        bool mFolded;
        BufferedSafeString mText;

        virtual ~DebugMenuItemBase();
        virtual void outputText(BufferedSafeString*);
        virtual void drawText(DebugMenuSkinBase*, DebugMenuSkinBase::DrawInstance*, Vector3f const&);
        virtual void drawBackground(DebugMenuSkinBase *, DebugMenuSkinBase::DrawInstance *,Vector3f const&, Vector2f const&);
    };
}