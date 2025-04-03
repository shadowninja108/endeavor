#pragma once

#include <common.hpp>

#include "Res/ResParameterList.hpp"
#include "Res/ResParameterObj.hpp"
#include "Res/ResParameter.hpp"

namespace agl::utl {
    struct IParameterObj;
    struct ParameterBase;
    struct IParameterList {
        IParameterObj* mChildObjHead;
        IParameterObj* mChildObjTail;

        IParameterList* mChildListHead;
        IParameterList* mChildListTail;

        uint mListNameHash;

        IParameterList* mNextList;
        IParameterList* mPrevList;

        virtual ~IParameterList();
        virtual bool preWrite_();
        virtual void postWrite_();
        virtual bool preRead_();
        virtual void postRead_();
        virtual bool isApply_(ResParameterList);
        virtual void callbackNotAppliable_(IParameterObj *, ParameterBase *, ResParameterObj);
        virtual void callbackNotInterpolatable_(IParameterObj *, ParameterBase *, ResParameterObj, ResParameterObj, ResParameter, ResParameter, float);
    };
}