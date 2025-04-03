#pragma once

#include "seadTaskBase.h"
#include "seadMethodTree.h"

namespace sead {
    struct Task : public TaskBase {
        SEAD_RTTI_OVERRIDE(Task, TaskBase);

        public:
        MethodTreeNode mCalc;
        MethodTreeNode mDraw;

        virtual void pauseCalc(bool b) override;
        virtual void pauseDraw(bool b) override;
        virtual void pauseCalcRec(bool b) override;
        virtual void pauseDrawRec(bool b) override;
        virtual void pauseCalcChild(bool b) override;
        virtual void pauseDrawChild(bool b) override;
        virtual void attachCalcImpl() override;
        virtual void attachDrawImpl() override;
        virtual void detachCalcImpl() override;
        virtual void detachDrawImpl() override;
        virtual const RuntimeTypeInfo::Interface* getCorrespondingMethodTreeMgrTypeInfo() const override;
        virtual MethodTreeNode* getMethodTreeNode(s32 method_type) override;

        virtual void calc();
        virtual void draw();
    };
}