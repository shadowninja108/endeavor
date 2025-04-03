#pragma once

#include <sead/math/seadMatrix.hpp>
#include <sead/gfx/seadCamera.h>
#include <sead/gfx/seadProjection.h>

#include "ToolConnectionContext.hpp"

namespace xlink2 {
    struct IUser {
        virtual sead::Matrix34f* getBoneWorldMtxPtr(char const*) const;
        virtual const char* getActionSlotName(int) const;
        virtual sead::Camera* getDebugDrawCamera() const;
        virtual sead::Projection* getDebugDrawProjection() const;
        virtual const char* getDebugUserName() const;
        virtual void* getUserInformation() const;   /* Unknown return type. */
        virtual void getReservedAssetName(ToolConnectionContext*) const;
        virtual int getNumBone() const;
        virtual int getBoneName(int) const;
        virtual int getNumAction(int) const;
        virtual const char* getActionName(int, int) const;
        virtual void captureScreen(char const*);
        /* Why the fuck does this return a float? */
        virtual float getSortKey(sead::Vector3<float> const&) const;
        virtual sead::Matrix34f getAutoInputMtxSource() const;
        virtual sead::Matrix34f getMtxCorrectingDrawBone() const;
    };
}