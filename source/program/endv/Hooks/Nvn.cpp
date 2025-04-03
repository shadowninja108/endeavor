#include "Nvn.hpp"

#include "../StackTrace.hpp"

#include <nvn/nvn.hpp>
#include <lib.hpp>

#include <cstring>
#include <string_view>
#include <concepts>

namespace endv::hooks::nvn {
    namespace {
        template<typename Derived, auto GamePtr, char const* _Name>
        struct NvnFuncHook {

            using FuncType = std::remove_pointer_t<decltype(GamePtr)>;

            template<typename T = Derived>
            using CallbackFuncPtr = decltype(&T::Callback);

            static constexpr const char* Name = _Name;

            static inline FuncType s_OrigPtr = nullptr;

            static inline auto OrigPtr() {
                return s_OrigPtr;
            }

            template<typename... Args>
            static auto Orig(Args&&... args) {
                static_assert(std::is_same_v<CallbackFuncPtr<>, FuncType>, "Callback arguments do not match!");
                EXL_ASSERT(OrigPtr() != nullptr);
                return OrigPtr()(std::forward<Args>(args)...);
            }
        };
    }

    template<typename Delegate>
    static void* TryGetHook(const char*, Delegate getter);

    #define NVN_HOOK(name) \
        struct name : public NvnFuncHook<name, &pfnc_nvn##name, pfnc_nvn##name##_name>

    NVN_HOOK(CommandBufferClearColor) {
        static void Callback(NVNcommandBuffer* cmdBuf, int index, const float* colorPtr, int mas) {
            StackTraceIterator it;
            if(!it.StepN(3)) {
                Orig(cmdBuf, index, colorPtr, mas);
                return;
            }

            auto lr = it.GetReturnAddress();
            auto offset = TryGetOffsetInModule(lr, exl::util::ModuleIndex::Main);
            if(!offset.has_value() || *offset != 0x0120CD3C) {
                Orig(cmdBuf, index, colorPtr, mas);
                return;
            }

            // Logging.Log(__PRETTY_FUNCTION__ );
            float color[4] = {
                0.0,
                1.0,
                0.0,
                1.0
            };
            Orig(cmdBuf, index, color, mas);
        }
    };

    NVN_HOOK(DeviceGetProcAddress) {
        static void* Callback(NVNdevice* device, const char* name) {
            Logging.Log(__PRETTY_FUNCTION__);
            /* If there's a hook to use, use that. */
            auto hooked = TryGetHook(name, [device](auto name) { return Orig(device, name); });
            if(hooked != nullptr)
                return hooked;

            /* Otherwise, call original. */
            return Orig(device, name);
        }
    };

    #define CHECK(compareName)                                                              \
        else if(std::strcmp(name, compareName::Name) == 0) {                                \
            compareName::s_OrigPtr = reinterpret_cast<compareName::FuncType>(getter(name)); \
            return reinterpret_cast<void*>(compareName::Callback);                          \
        }

    template<typename Delegate>
    static void* TryGetHook(const char* name, Delegate getter) {
        Logging.Log(__PRETTY_FUNCTION__);
        if (false) {}
        CHECK(DeviceGetProcAddress)
        // CHECK(CommandBufferClearColor)
        return nullptr;
    }

    #undef CHECK
    #undef NVN_HOOK

    HOOK_DEFINE_TRAMPOLINE(NvnBootstrap) {
        static void* Callback(const char* name) {
            Logging.Log(__PRETTY_FUNCTION__);
            endv::LogStackTrace();
            auto hooked = TryGetHook(name, [](auto name) { return Orig(name); });
            if(hooked != nullptr)
                return hooked;
            
            return Orig(name);
        }
    };
    
    void Install() {
        NvnBootstrap::InstallAtFuncPtr(&nvnBootstrapLoader);
    }
}