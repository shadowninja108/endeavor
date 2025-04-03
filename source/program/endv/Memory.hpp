#pragma once

#include <lib.hpp>

/* I am writing these utilities against my will. I assure you, I hate it more than you do. */
namespace endv::memory {

    bool QueryMemory(MemoryInfo* out, uintptr_t pointer) {
        u32 pageInfo;
        return R_SUCCEEDED(svcQueryMemory(out, &pageInfo, pointer));
    }

    template<typename T>
    bool QueryMemory(MemoryInfo* out, T* pointer) { return QueryMemory(out, reinterpret_cast<uintptr_t>(pointer)); }

    bool IsPointerMapped(uintptr_t pointer) {
        MemoryInfo info;
        if(!QueryMemory(&info, pointer))
            return false;

        return info.type != MemType_Unmapped;
    }

    template<typename T>
    bool IsPointerMapped(T* pointer) { return IsPointerMapped(reinterpret_cast<uintptr_t>(pointer)); }

    /* TODO: can we assume ASCII? If so, ideally do some validation with the chars themselves. */
    bool IsValidStringPointer(const char* pointer) {
        /* Maximum length we will try to infer is a string. */
        static constexpr size_t MaxLength = 512;

        size_t size = 0;
        auto p = pointer;


        while(true) {
            /* First, probe the memory this is pointing to. */
            MemoryInfo info;
            if(!QueryMemory(&info, p))
                return false;

            /* If it's unmapped, then it's just invalid. */
            if(info.type == MemType_Unmapped)
                return false;
            
            /* Calculate the memory left within this range that we can safely access. */
            ptrdiff_t offsetInRange = reinterpret_cast<uintptr_t>(p) - info.addr;
            size_t leftInRange = info.size - offsetInRange;

            /* Scan for null terminator in the memory we can safely access. */
            for(size_t i = 0; i < leftInRange; i++) {
                /* If we find a null terminator, then this string is fully mapped and terminates sanely. */
                if(*p == '\0')
                    return true;

                /* Move to next char. */
                size++;
                p++;

                /* If this string is too long, assume it's just junk data. */
                if(size >= MaxLength)
                    return false;
            }

            /* If we hit here, we fell out of the found memory range before finding the null terminator. Loop around to check if there is an adjacent region to continue searching. */
        }

        /* TODO: Can we hit here? */
        EXL_ABORT("Unreachable case");
        return false;
    }
}