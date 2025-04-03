#pragma once

#include <lib.hpp>
#include <sead/prim/seadEnum.h>

namespace endv {
    enum class LpParamType : uint {
        U8 = exl::util::Crc32::Hash("u8"),
        S8 = exl::util::Crc32::Hash("s8"),
        U16 = exl::util::Crc32::Hash("u16"),
        S16 = exl::util::Crc32::Hash("s16"),
        U32 = exl::util::Crc32::Hash("u32"),
        S32 = exl::util::Crc32::Hash("s32"),
        F32 = exl::util::Crc32::Hash("f32"),
        U64 = exl::util::Crc32::Hash("u64"),
        S64 = exl::util::Crc32::Hash("s64"),
        F64 = exl::util::Crc32::Hash("f64"),
        Bool = exl::util::Crc32::Hash("bool"),  /* `bool` is a keyword so I do need to do Bool here lol. */
        Str = exl::util::Crc32::Hash("Str"),
        Bit = exl::util::Crc32::Hash("Bit"),
        Enum = exl::util::Crc32::Hash("Enum"),
        V2f = exl::util::Crc32::Hash("V2f"),
        V2i = exl::util::Crc32::Hash("V2i"),
        V3f = exl::util::Crc32::Hash("V3f"),
        V3i = exl::util::Crc32::Hash("V3i"),
        V4f = exl::util::Crc32::Hash("V4f"),
        V4i = exl::util::Crc32::Hash("V4i"),
        Q4f = exl::util::Crc32::Hash("Q4f"),
        Curvef = exl::util::Crc32::Hash("Curvef"),
        Rangef = exl::util::Crc32::Hash("Rangef"),
        Rangei = exl::util::Crc32::Hash("Rangei"),
        C4f = exl::util::Crc32::Hash("C4f"),
        C4u8 = exl::util::Crc32::Hash("C4u8"),
    };
    
}