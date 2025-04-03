#pragma once

#include <gsys/SystemTask.hpp>

#include <Lp/Sys/Cstm/IRootTaskCstm.hpp>
#include <Lp/Sys/Cstm/ISceneInfoCstm.hpp>

namespace endv {
    void OnCreateGsysCreateArg(gsys::SystemTask::CreateArg& arg);
    void OnPostRootTaskCreateVariousParts();
}

namespace endv::Cstm {
    struct RootTask : Lp::Sys::IRootTaskCstm {
        SEAD_RTTI_OVERRIDE(RootTask, Lp::Sys::IRootTaskCstm);
        
        public:
        Lp::Sys::IRootTaskCstm* m_Impl = nullptr;

        virtual void createVariousParts() {
            m_Impl->createVariousParts();
            OnPostRootTaskCreateVariousParts();
        }
        virtual void createRenderer() { m_Impl->createRenderer(); }
        virtual void createCalcMethodTree() { m_Impl->createCalcMethodTree(); }
        virtual void createVariousParts_UserCb(CreateVariousParts_UserCb cb ) { m_Impl->createVariousParts_UserCb(cb); }
        virtual uintptr_t createThreadDefCstm() { return m_Impl->createThreadDefCstm(); }
        virtual Lp::Sys::ISceneInfoCstm* createSceneInfoCstm() { return m_Impl->createSceneInfoCstm(); }
        virtual uintptr_t createResMgrCstm() { return m_Impl->createResMgrCstm(); }
        virtual uintptr_t createSaveDataMgrCstm() { return m_Impl->createSaveDataMgrCstm(); }
        virtual uintptr_t createEffectMgrCstm() { return m_Impl->createEffectMgrCstm(); }
        virtual uintptr_t createSoundMgrCstm() { return m_Impl->createSoundMgrCstm(); }
        virtual uintptr_t createXLinkMgrCstm() { return m_Impl->createXLinkMgrCstm(); }
        virtual uintptr_t createUIMgrCstm() { return m_Impl->createUIMgrCstm(); }
        virtual uintptr_t createDbgModeCstm() { return m_Impl->createDbgModeCstm(); }
        virtual uintptr_t createEnlTaskCstm() { return m_Impl->createEnlTaskCstm(); }
        virtual uintptr_t createORCstm() { return m_Impl->createORCstm(); }
        virtual uintptr_t createLuaCstm() { return m_Impl->createLuaCstm(); }
        virtual uintptr_t createSimpleAccountMgrCstm() { return m_Impl->createSimpleAccountMgrCstm(); }
        virtual uintptr_t createProcessSwitchCstm() { return m_Impl->createProcessSwitchCstm(); }
        virtual uintptr_t createCalcMethodTree_UserCb(CreateCalcMethodTree_UserCb cb) { return m_Impl->createCalcMethodTree_UserCb(cb); }
        virtual void pushGfxPreCalc() { m_Impl->pushGfxPreCalc(); }
        virtual void pushGfxPostCalc() { m_Impl->pushGfxPostCalc(); }
        virtual gsys::SystemTask::CreateArg getGsysCreateArg() { 
            auto arg = m_Impl->getGsysCreateArg();
            OnCreateGsysCreateArg(arg);
            return arg;
        }
        virtual void parallelInitThreadFunc(int a) { m_Impl->parallelInitThreadFunc(a); }
        virtual void printOnInfLoop(sead::InfLoopChecker::InfLoopParam const& param) { m_Impl->printOnInfLoop(param); }
        virtual void printOnAbort(sead::ExceptionHandler::Information const& info) { m_Impl->printOnAbort(info); }
        virtual void addGameConfigHostIONode(sead::SafeString const& name) { m_Impl->addGameConfigHostIONode(name); }
        virtual void addGSysHostIONode() { m_Impl->addGSysHostIONode(); }
    };
    SEAD_RTTI_OVERRIDE_IMPL(RootTask, Lp::Sys::IRootTaskCstm);
    inline static RootTask s_RootTaskInstance;
};