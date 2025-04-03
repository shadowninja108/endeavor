#pragma once

#include <sead/prim/seadRuntimeTypeInfo.h>
#include <sead/framework/seadInfLoopChecker.h>

#include <gsys/SystemTask.hpp>

#include "ISceneInfoCstm.hpp"

/* TODO: */
namespace sead {
    struct ExceptionHandler {
        struct Information;
    };
}

namespace Lp::Sys {

    struct IRootTaskCstm {
        SEAD_RTTI_BASE(IRootTaskCstm);

        enum CreateVariousParts_UserCb {};
        enum CreateCalcMethodTree_UserCb {};

        virtual void createVariousParts();
        virtual void createRenderer();
        virtual void createCalcMethodTree();
        virtual void createVariousParts_UserCb(CreateVariousParts_UserCb);
        virtual uintptr_t createThreadDefCstm();
        virtual ISceneInfoCstm* createSceneInfoCstm();
        virtual uintptr_t createResMgrCstm();
        virtual uintptr_t createSaveDataMgrCstm();
        virtual uintptr_t createEffectMgrCstm();
        virtual uintptr_t createSoundMgrCstm();
        virtual uintptr_t createXLinkMgrCstm();
        virtual uintptr_t createUIMgrCstm();
        virtual uintptr_t createDbgModeCstm();
        virtual uintptr_t createEnlTaskCstm();
        virtual uintptr_t createORCstm();
        virtual uintptr_t createLuaCstm();
        virtual uintptr_t createSimpleAccountMgrCstm();
        virtual uintptr_t createProcessSwitchCstm();
        virtual uintptr_t createCalcMethodTree_UserCb(CreateCalcMethodTree_UserCb);
        virtual void pushGfxPreCalc();
        virtual void pushGfxPostCalc();
        virtual gsys::SystemTask::CreateArg getGsysCreateArg();
        virtual void parallelInitThreadFunc(int);
        virtual void printOnInfLoop(sead::InfLoopChecker::InfLoopParam const&);
        virtual void printOnAbort(sead::ExceptionHandler::Information const&);
        virtual void addGameConfigHostIONode(sead::SafeString const&);
        virtual void addGSysHostIONode();

        static IRootTaskCstm* spCstm;
    };
}