#pragma once

#include <math/seadVector.hpp>
#include <heap/seadHeap.h>
#include <gfx/seadFrameBuffer.h>
#include <nvn/nvn.hpp>

namespace sead {
    struct FrameBufferNvn : public FrameBuffer {
        SEAD_RTTI_OVERRIDE(FrameBufferNvn, FrameBuffer);

        public:
        NVNtexture* mTexture1;
        NVNtexture* mTexture2;

        static FrameBufferNvn* create(Heap*, Vector2f const&, uint, uint);

        virtual ~FrameBufferNvn();
        virtual void copyToDisplayBuffer(DrawContext*, const DisplayBuffer*) const;
        virtual void clear(u32 clr_flag, const Color4f&, f32, u32) const;
        virtual void clearMRT(DrawContext*, u32, const Color4f&) const;
        virtual void bindImpl_() const;
    };
}