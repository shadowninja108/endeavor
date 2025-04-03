#pragma once

#include <common.hpp>

#include "ParameterBase.hpp"
#include "Res/ResParameterObj.hpp"

namespace agl::utl {
    struct IParameterObj {
        ParameterBase* mHead;
        ParameterBase* mTail;
        int mIndex;
        uint mHash;
        IParameterObj* mNext;
        uintptr_t field_28;

        virtual ~IParameterObj();
        virtual bool preWrite_();
        virtual void postWrite_();
        virtual bool preRead_();
        virtual void postRead_();
        virtual bool preCopy_();
        virtual void postCopy_();
        virtual bool isApply_(ResParameterObj);
    };
    static_assert(sizeof(IParameterObj) == 0x30);
}