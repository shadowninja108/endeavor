#ifndef SEAD_PROJECTION_H_
#define SEAD_PROJECTION_H_

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <math/seadBoundBox.hpp>
#include <prim/seadRuntimeTypeInfo.h>

namespace sead
{
namespace Graphics
{
enum DevicePosture
{
    cDevicePosture_Same = 0,
    cDevicePosture_RotateRight = 1,
    cDevicePosture_RotateLeft = 2,
    cDevicePosture_RotateHalfAround = 3,
    cDevicePosture_FlipX = 4,
    cDevicePosture_FlipY = 5,
    cDevicePosture_FlipXY = 3,
    cDevicePosture_Invalid = 4,
};

}

struct Viewport;
class Projection
{
    SEAD_RTTI_BASE(Projection)

public:
    Projection();
    virtual ~Projection();

    virtual float getNear() const = 0;
    virtual float getFar() const = 0;
    virtual float getFovy() const = 0;
    virtual float getAspect() const = 0;
    virtual void getOffset(Vector2f*) const = 0;
    /* TODO: probably debug only... */
    virtual void updateAttributesForDirectProjection();

    virtual u32 getProjectionType() const = 0;
    virtual void doUpdateMatrix(Matrix44f* mtx) const = 0;
    virtual void doUpdateDeviceMatrix(Matrix44f*, const Matrix44f&, Graphics::DevicePosture) const;
    virtual void doScreenPosToCameraPosTo(Vector3f*, const Vector3f&) const = 0;

    void updateMatrixImpl_() const;
    const Matrix44f& getDeviceProjectionMatrix() const;

    mutable bool mDirty;
    mutable bool mDeviceDirty;
    Matrix44f mMatrix;
    Matrix44f mDeviceMatrix;
    Graphics::DevicePosture mDevicePosture;
    f32 mDeviceZScale;
    f32 mDeviceZOffset;
};

class OrthoProjection : public Projection {
    SEAD_RTTI_OVERRIDE(OrthoProjection, Projection);

    public:
    float mNear;
    float mFar;
    float mTop;
    float mBottom;
    float mLeft;
    float mRight;

    OrthoProjection();
    OrthoProjection(float, float, float, float, float, float);
    OrthoProjection(float, float, BoundBox2f const&);
    OrthoProjection(float, float, Viewport const&);

    virtual float getNear() const;
    virtual float getFar() const;
    virtual float getFovy() const;
    virtual float getAspect() const;
    virtual void getOffset(Vector2f*) const;
    virtual u32 getProjectionType() const;
    virtual void doUpdateMatrix(Matrix44f* mtx) const;
    virtual void doScreenPosToCameraPosTo(Vector3f*, const Vector3f&) const;

    void setByViewport(Viewport const&);
    void setTBLR(float, float, float, float);
    void setBoundBox(BoundBox2f const&);
    void createDividedProjection(OrthoProjection*, int, int, int, int) const;
};

}  // namespace sead

#endif  // SEAD_PROJECTION_H_
