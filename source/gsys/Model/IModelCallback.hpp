#pragma once

namespace gsys {
    struct Model;

    struct IModelCallback {
        virtual void beforeModelApplyAnimation(Model*);
        virtual void beforeModelUpdateWorldMatrix(Model*);
        virtual void afterModelUpdateWorldMatrix(Model*);
        virtual void afterClearMaterialParameter(Model*);
    };
}