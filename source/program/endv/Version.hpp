#pragma once

#include <lib.hpp>

#include <sead/prim/seadEnum.h>

namespace endv::version {

    SEAD_ENUM_EX(
        Type,
        Pilot_2017_06_01_12_04_27, /* "Build 1" */
        Pilot_2017_06_09_12_02_10  /* "Build 2" */
    )

    namespace impl {
        inline uint s_Hash;
        inline int s_Index;
    }

    inline Type::ValueType GetValue() {
        return static_cast<Type::ValueType>(impl::s_Hash);
    }

    inline void Initialize() {
        auto text = exl::util::GetMainModuleInfo().m_Text;
        impl::s_Hash = exl::util::Crc32::Hash(std::span(
            reinterpret_cast<const std::byte*>(text.m_Start),
            text.m_Size
        ));
        impl::s_Index = Type::findRelativeIndex(GetValue());
    }
    inline Type Get() {
        return Type({}, impl::s_Index);
    }

    inline bool IsValid() {
        return impl::s_Index != -1;
    }
}