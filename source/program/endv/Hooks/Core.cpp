#include "Core.hpp"

#include <lib.hpp>

#include <Lp/Sys/Task/RootTask.hpp>
#include <Lp/Sys/SysInit.hpp>
#include <Lp/Sys/Framework.hpp>
#include <Lp/Sys/Debug/DbgMode.hpp>
#include <Lp/Sys/Ctrl/CtrlMgr.hpp>
#include <Lp/Sys/Ctrl/Ctrl.hpp>
#include <Lp/Sys/Ctrl/CtrlType.hpp>
#include <Lp/Sys/Ctrl/DbgMixCtrl.hpp>
#include <Lp/Sys/Framework.hpp>
#include <Lp/Sys/Assert.hpp>
#include <Lp/Sys/Debug/DbgMode.hpp>
#include <Lp/Sys/HeapGroup.hpp>

#include <sead/devenv/seadGameConfig.h>
#include <sead/devenv/seadEnvUtil.h>

#include <Blitz/Cmn/Gfx/PBRMgr.hpp>
#include <Blitz/Cmn/ViewerEnvChanger.hpp>
#include <Blitz/Game/Actor/Lift.hpp>

#include "../Heap.hpp"
#include "../../shimmer/client.hpp"
#include "../Cstm/SysInitCstm.hpp"

namespace nn {
    namespace oe {
        struct LaunchStorageInfoForDebug {
            int field_0;
            /* ... */
        };
        void GetLaunchStorageInfoForDebug(LaunchStorageInfoForDebug*);
    }

    namespace pcm {
        enum MeasuringPoint {};
        void Initialize();
        bool IsSupported(MeasuringPoint);
    }
}

namespace endv {
}

namespace endv::hooks::core {
    
    /* Stub various nnSdk debug only things. */
    HOOK_DEFINE_REPLACE(NnPcmInit) {
        static void Callback() {}
    };
    HOOK_DEFINE_REPLACE(NnPcmSupported) {
        static bool Callback(nn::pcm::MeasuringPoint) { return false; }
    };
    HOOK_DEFINE_REPLACE(NnOeGetLaunchStorageInfo) {
        static void Callback(nn::oe::LaunchStorageInfoForDebug* out) {
            out->field_0 = 0;
        };
    };

    /* Work around -1 env not being available by loading the first Versus one. TODO: make this work properly. */
    HOOK_DEFINE_TRAMPOLINE(ViewerEnvChangerApply) {
        static void Callback(Cmn::ViewerEnvChanger* self) {
            if(self->mEnvIndex == -1) {
                self->mEnvIndex = 1;
            }
            Orig(self);
        }
    };

    /* Seems PBRMgr is expected to have some debug ResFile? Don't see it initialized anywhere. Suppress using it for now. TODO: do this properly. */
    HOOK_DEFINE_REPLACE(PBRMgrDebugDrawEnvMap) {
        static void Callback(Cmn::PBRMgr* self, bool u) {}
    };

    // HOOK_DEFINE_TRAMPOLINE(PBRMgrLoad) {
    //     static void Callback(Cmn::PBRMgr* self, sead::Heap* heap) {
    //         Orig(self, heap);

    //         auto& bin = self->GetViewerEnvMapBinRef();
    //     }
    // };

    /* nn::htc is not available to grab host env vars, so override known vars to point to SD instead. */
    HOOK_DEFINE_TRAMPOLINE(SeadGetEnv) {
        static int Callback(sead::BufferedSafeString* out,sead::SafeString const& in) {
            auto cstr = in.cstr();
            Logging.Log("SeadGetEnv: %s", cstr);

            #define CASE(cmp, res)                      \
                else if(strcmp(cstr, cmp) == 0) {       \
                    out->copy(sead::SafeString(res));   \
                    return sizeof(res)-1;               \
                }

            if(false){}
            CASE("PROJECT_ROOT", "sd:/Blitz")
            CASE("PROJECT_TMP", "sd:/BlitzTmp")
            #undef CASE

            Logging.Log("SeadGetEnv unresolved %s", cstr);
            return -1;
        }
    };

    /* Populate SysInit cstm before it's used and after it's asserted to be non-null(???). */
    HOOK_DEFINE_TRAMPOLINE(SysInit) {
        static void Callback() {
            endv::Cstm::s_SysInitInstance.m_Impl = Lp::Sys::ISysInitCstm::spCstm;
            Lp::Sys::ISysInitCstm::spCstm = &endv::Cstm::s_SysInitInstance;

            Orig();
        }
    };

    /* Workaround not using debug controllers. */
    HOOK_DEFINE_TRAMPOLINE(LpCtrlCreate) {
        static void Callback(Lp::Sys::CtrlMgr* self, sead::ControllerMgr* ctrlMgr) {
            Orig(self, ctrlMgr);

            auto& normal = self->mCtrls[Lp::Sys::CtrlType_cNormal];
            for(int i = Lp::Sys::CtrlType_cDbgOrigin; i < Lp::Sys::CtrlType_End; i++) {
                auto& ptrs = self->mCtrls[i];
                if(ptrs.size() == 0) {
                    ptrs.pushFront(normal[0]);
                } else if(i == Lp::Sys::CtrlType_cDbg || i == Lp::Sys::CtrlType_cDbgMix) {
                    reinterpret_cast<Lp::Sys::DbgMixCtrl*>(ptrs[0])->mBitfield = 0b1;
                }
            }
        }
    };

    HOOK_DEFINE_TRAMPOLINE(HeapGroupCreate) {
        static void Callback(Lp::Sys::HeapGroup* self, sead::Heap* heap) {
            Orig(self, heap);

            /* Initialize our root heap using the HeapGroup cOthers heap. */
            endv::heap::Initialize(self->mHeaps[Lp::Sys::HeapGroup::Group_Others]);

            /* Then initialize our client asap. */
            shimmer::client::Initialize();
        }
    };

    void Install() {
        uintptr_t base = exl::util::GetMainModuleInfo().m_Total.m_Start;

        exl::patch::CodePatcher p(0x0);
        /* Suppress abort WarningMgr. TODO: work around this. */
        p.Seek(reinterpret_cast<uintptr_t>(&Lp::Sys::cpWarning) + 0x1CC - base);
        p.WriteInst(exl::armv8::inst::Nop());
        /* Disable - button for Lp's debug menu. TODO: better solution? */
        p.Seek(reinterpret_cast<uintptr_t>(reinterpret_cast<void(*)(Lp::Sys::DbgMode*)>(&Lp::Sys::DbgMode::calcChangeMode)) + 0x28 - base);
        p.WriteInst(exl::armv8::inst::Nop());
        /* Don't allow Lp to override sead's DebugMenu controller. TODO: should be easy to work around. */
        p.Seek(reinterpret_cast<uintptr_t>(reinterpret_cast<void(*)(Lp::Sys::Framework*, sead::TaskBase*)>(&Lp::Sys::Framework::createControllerMgr)) + 0x230 - base);
        p.WriteInst(exl::armv8::inst::Nop());
        /* Skip abort related to lift collision for model auto fixer*/
        p.Seek(reinterpret_cast<uintptr_t>(reinterpret_cast<void(*)(Game::Lift*)>(&Game::Lift::load_)) + 0xF24 - base);
        p.WriteInst(exl::armv8::inst::Nop());

        /* Stub out debug-only nnSdk things. */
        NnOeGetLaunchStorageInfo::InstallAtFuncPtr(&nn::oe::GetLaunchStorageInfoForDebug);
        NnPcmInit::InstallAtFuncPtr(&nn::pcm::Initialize);
        NnPcmSupported::InstallAtFuncPtr(&nn::pcm::IsSupported);

        LpCtrlCreate::InstallAtFuncPtr(&Lp::Sys::CtrlMgr::createCtrl);
        ViewerEnvChangerApply::InstallAtFuncPtr(&Cmn::ViewerEnvChanger::applyEnvSet);
        // PBRMgrLoad::InstallAtFuncPtr(&Cmn::PBRMgr::load);
        PBRMgrDebugDrawEnvMap::InstallAtFuncPtr(&Cmn::PBRMgr::setDebugDrawEnvMap);
        SeadGetEnv::InstallAtFuncPtr(&sead::EnvUtil::getEnvironmentVariable);
        SysInit::InstallAtFuncPtr(&Lp::Sys::SysInit::Init);
        HeapGroupCreate::InstallAtFuncPtr(&Lp::Sys::HeapGroup::createHeap);
    }
}