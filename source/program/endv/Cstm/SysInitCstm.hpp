#pragma once

#include <Lp/Sys/Cstm/ISysInitCstm.hpp>
#include <Lp/Sys/HeapInfo.hpp>

#include "RootTaskCstm.hpp"

namespace endv {
    void OnSetHeapInfo(Lp::Sys::HeapInfo* heapInfo);
    void OnOverwriteFrameworkCreateArg(sead::GameFrameworkNx::CreateArg* arg);
}

namespace endv::Cstm {
    struct SysInit : Lp::Sys::ISysInitCstm {
        SEAD_RTTI_OVERRIDE(SysInit, Lp::Sys::ISysInitCstm);
        
        public:
        Lp::Sys::ISysInitCstm* m_Impl = nullptr;

        virtual void setHeapInfo() {
            /* Let the game populate HeapInfo::spInfo. */
            m_Impl->setHeapInfo();
            OnSetHeapInfo(Lp::Sys::HeapInfo::spInfo);
        }
        virtual void overwriteFrameworkCreateArg(sead::GameFrameworkNx::CreateArg* arg) { 
            m_Impl->overwriteFrameworkCreateArg(arg);
            OnOverwriteFrameworkCreateArg(arg);
        };
        virtual size_t getRootTaskPrepareThreadStackSize() const { return m_Impl->getRootTaskPrepareThreadStackSize(); };
        virtual void setRootTaskCstm() {
            /* Setup our own root task cstm immediately after the game does. */
            m_Impl->setRootTaskCstm();
            endv::Cstm::s_RootTaskInstance.m_Impl = Lp::Sys::IRootTaskCstm::spCstm;
            Lp::Sys::IRootTaskCstm::spCstm = &endv::Cstm::s_RootTaskInstance;
        };
        virtual void onAppExit() { m_Impl->onAppExit(); };
        virtual sead::Vector2<int> getScanBufferSize() const { return m_Impl->getScanBufferSize(); };
        virtual sead::Vector2f getVirtualCanvasSize() { return m_Impl->getVirtualCanvasSize(); };
    };
    SEAD_RTTI_OVERRIDE_IMPL(SysInit, Lp::Sys::ISysInitCstm);
    inline static SysInit s_SysInitInstance;
};