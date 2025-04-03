#pragma once

#include <heap/seadHeap.h>
#include <math/seadMatrix.hpp>
#include <math/seadVector.hpp>
#include <math/seadBoundBox.hpp>
#include <prim/seadSafeString.hpp>
#include <gfx/seadColor.h>
#include <gfx/seadDrawContext.h>
#include <gfx/seadTexture.h>

namespace sead {
    struct PrimitiveDrawer {
        struct QuadArg {
            sead::Vector3 mMidPoint;
            sead::Vector2 mSize;
            sead::Color4f field_14;
            sead::Color4f field_24;
            char field_34;

            void setCornerAndSize(Vector3f const&, Vector2f const&);
            void setBoundBox(BoundBox2f const&, float);
            void setColor(Color4f const&, Color4f const&);
            void setColorHorizontal(Color4f const&, Color4f const&);
            void setCornerAndSize(Vector3f const&, Vector3f const&);
            void setBoundBox(BoundBox3f const&);
        };
        struct UVArg;
        struct CubeArg;

        PrimitiveDrawer(DrawContext*);

        virtual ~PrimitiveDrawer();

        void prepareMgrFromBinary(Heap*, void const*, unsigned int);
        void createDrawMgrInstance_(Heap*);
        void prepareMgr(Heap*, SafeString const&);
        void prepareMgrFromBinary(Heap*, void const*, unsigned int, unsigned int);
        void prepareMgr(Heap*, SafeString const&, unsigned int);
        void setCamera(Camera const*);
        void setCameraViewMatrix(Matrix34f const*);
        void setProjection(Projection const*);
        void setProjectionMatrix(Matrix44f const*);
        void setModelMatrix(Matrix34f const*);
        void setDrawContext(DrawContext*);
        void begin();
        uintptr_t getDrawMgr_(); /* TODO: */
        void end();
        void drawQuad(Color4f const&, Color4f const&);
        void drawQuad(Texture const&, Color4f const&, Color4f const&, Vector2f const&, Vector2f const&);
        void drawBox(Color4f const&, Color4f const&);
        void drawCube(Color4f const&, Color4f const&);
        void drawWireCube(Color4f const&, Color4f const&);
        void drawLine(Color4f const&, Color4f const&);
        void drawSphere4x8(Color4f const&, Color4f const&);
        void drawSphere8x16(Color4f const&, Color4f const&);
        void drawDisk16(Color4f const&, Color4f const&);
        void drawDisk32(Color4f const&, Color4f const&);
        void drawCircle16(Color4f const&);
        void drawCircle32(Color4f const&);
        void drawCylinder16(Color4f const&, Color4f const&);
        void drawCylinder32(Color4f const&, Color4f const&);
        void drawQuad(QuadArg const&);
        void drawQuad(Texture const&, QuadArg const&, PrimitiveDrawer::UVArg const&);
        void drawBox(QuadArg const&);
        void drawCube(PrimitiveDrawer::CubeArg const&);
        void drawWireCube(PrimitiveDrawer::CubeArg const&);
        void drawLine(Vector3f const&, Vector3f const&, Color4f const&, Color4f const&);
        void drawLine(Vector3f const&, Vector3f const&, Color4f const&);
        void drawSphere4x8(Vector3f const&, float, Color4f const&, Color4f const&);
        void drawSphere4x8(Vector3f const&, float, Color4f const&);
        void drawSphere8x16(Vector3f const&, float, Color4f const&, Color4f const&);
        void drawSphere8x16(Vector3f const&, float, Color4f const&);
        void drawDisk16(Vector3f const&, float, Color4f const&, Color4f const&);
        void drawDisk16(Vector3f const&, float, Color4f const&);
        void drawDisk32(Vector3f const&, float, Color4f const&, Color4f const&);
        void drawDisk32(Vector3f const&, float, Color4f const&);
        void drawCircle16(Vector3f const&, float, Color4f const&);
        void drawCircle32(Vector3f const&, float, Color4f const&);
        void drawCylinder16(Vector3f const&, float, float, Color4f const&, Color4f const&);
        void drawCylinder16(Vector3f const&, float, float, Color4f const&);
        void drawCylinder32(Vector3f const&, float, float, Color4f const&, Color4f const&);
        void drawCylinder32(Vector3f const&, float, float, Color4f const&);
        void drawAxis(Vector3f const&, float);
    }
}