#pragma once

#include <lib.hpp>
#include <nn.hpp>

#include <optional>

namespace endv {
    class StackTraceIterator : public exl::util::stack_trace::AbstractIterator<StackTraceIterator> {
        mutable u32 m_PageInfo;
        mutable MemoryInfo m_MemoryInfo;

        public:
        inline bool IsValidLr(uintptr_t lr) const {
            /* Try to inspect pointer. */
            if(!R_SUCCEEDED(svcQueryMemory(&m_MemoryInfo, &m_PageInfo, lr)))
                return false;

            /* Inspect if the pointer points to executable memory. */
            if(m_MemoryInfo.perm != Perm_Rx)
                return false;

            return true;
        }
        template<typename T>
        inline bool IsValidPointer(const T* pointer) const {
            auto integer = reinterpret_cast<uintptr_t>(pointer);

            /* Try to inspect pointer. */
            if(!R_SUCCEEDED(svcQueryMemory(&m_MemoryInfo, &m_PageInfo, integer)))
                return false;

            /* Pointer to end of structure (exclusive). */
            auto end = integer + sizeof(T);

            /* If the object would extend outside the memory range, it's invalid. */
            if(end > (m_MemoryInfo.addr + m_MemoryInfo.size))
                return false;

            return true;
        }

        StackTraceIterator(uintptr_t fp, uintptr_t lr, nn::os::ThreadType* thread) : AbstractIterator(
            fp,
            lr,
            {
                reinterpret_cast<uintptr_t>(thread->aliased_stack),
                thread->stack_size
            }
        ) {}

        ALWAYS_INLINE StackTraceIterator() : StackTraceIterator(
            exl::util::stack_trace::GetFp(),
            0ul,
            nn::os::GetCurrentThread()
        ) {}
    };

    ALWAYS_INLINE void LogStackTrace() {
        endv::StackTraceIterator it;
        size_t i = 0;
        it.Walk([&]() {
            auto lr = it.GetReturnAddress();

            /* If there's no LR available on the first step, skip printing it. */
            if(lr == 0 && i == 0) {
                i++;
                return;
            }

            /* Try to infer module this is pointing within. */
            auto module = exl::util::TryGetModule(lr);
            if(module != nullptr) {
                /* Print module name along with offset within it. */
                char nameBuffer[exl::util::ModuleInfo::s_ModulePathLengthMax+1];
                exl::util::CopyString(nameBuffer, module->GetModuleName());
                Logging.Log("[%d] %s+%08llx", i, nameBuffer, lr - module->m_Total.m_Start);
            } else {
                /* Couldn't find module, print as-is. */
                Logging.Log("[%d] (unknown) %08llx", i, lr);
            }
            i++;
        });

    }

    inline std::optional<uintptr_t> TryGetOffsetInModule(uintptr_t pointer, exl::util::ModuleIndex index) {
        auto module = exl::util::GetModuleInfo(index);
        if(!module.m_Total.InRange(pointer))
            return {};

        return std::make_optional(pointer - module.m_Total.m_Start);
    }
}