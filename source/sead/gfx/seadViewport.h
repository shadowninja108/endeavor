#pragma once

#include <math/seadBoundBox.hpp>
#include <gfx/seadFrameBuffer.h>
#include <gfx/seadDrawContext.h>
#include <gfx/seadProjection.h>
#include <gfx/seadCamera.h>

namespace sead {

    struct Viewport {
        float mMinX;
        float mMinY;
        float mMaxX;
        float mMaxY;
        Graphics::DevicePosture mDevicePosture;
        
        Viewport();
        Viewport(float, float, float, float);
        Viewport(BoundBox2f const&);
        Viewport(LogicalFrameBuffer const&);        

        void setByFrameBuffer(LogicalFrameBuffer const&);
        void apply(DrawContext*, LogicalFrameBuffer const&) const;
        void getOnFrameBufferPos(Vector2f*, LogicalFrameBuffer const&) const;
        void getOnFrameBufferSize(Vector2f*, LogicalFrameBuffer const&) const;
        void assertAreaIsInFrameBufferPhysicalArea_(Vector2f const&, Vector2f const&, LogicalFrameBuffer const&) const;
        void applyViewport(DrawContext*, LogicalFrameBuffer const&) const;
        void applyScissor(DrawContext*, LogicalFrameBuffer const&) const;
        void project(Vector2f*, Vector3f const&) const;
        void project(Vector2f*, Vector2f const&) const;
        void unproject(Vector3f*, Vector2f const&, Projection const&, Camera const&) const;
        // void unprojectRay(Ray<Vector3<float>> *, sead::Vector2f const&, Projection const&, Camera const&) const;

        virtual ~Viewport();
    };
}