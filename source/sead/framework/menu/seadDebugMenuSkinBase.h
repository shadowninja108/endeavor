#pragma once

#include <prim/seadSafeString.hpp>
#include <gfx/seadViewport.h>
#include <gfx/seadProjection.h>
#include <math/seadVector.hpp>
#include <framework/seadPrimitiveDrawer.h>

namespace sead {
    struct DebugMenuSkinBase {
        struct DrawInstance {
            OrthoProjection mProjection;
            OrthoCamera mCamera;
            PrimitiveDrawer mDrawer;
            /* TODO: wtf is this */
            char gap138[120];
            DrawContext *mDrawCtx;
        };

        virtual ~DebugMenuSkinBase();
        virtual void beginDrawImage(DrawInstance *, const Viewport *);
        virtual void endDrawImage(DrawInstance *);
        virtual void drawBackground(DrawInstance *, const Vector3f *, const Vector2f *);
        virtual void drawTitleBackground(DrawInstance *, const Vector3f *, const Vector2f *);
        virtual void drawItemBackground(DrawInstance *, const Vector3f *, const Vector2f *);
        virtual void drawScrollBar(DrawInstance *, const Vector3f *, const Vector2f *, float, float);
        virtual void drawQuad(DrawInstance *, const Vector3f *, const Vector2f *, const Color4f *, const Color4f *, bool);
        virtual void beginDrawText(DrawInstance *, const Viewport *);
        virtual void endDrawText(DrawInstance *);
        virtual void drawTitleText(DrawInstance *, const Vector3f *, const SafeString *);
        virtual void drawItemText(DrawInstance *, const Vector3f *, const SafeString *);
        virtual void drawCursorText(DrawInstance *, const Vector3f *);
        virtual void drawFolderText(DrawInstance *, const Vector3f *, bool);
        virtual void drawText(DrawInstance *, const Vector3f *, const SafeString *, const Color4f *);
        virtual float getLineHeight();
        virtual float getFontWidth();
    };
}