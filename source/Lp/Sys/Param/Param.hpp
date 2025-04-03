#pragma once

#include <agl/utl/param/ParameterObj.hpp>
#include <sead/gfx/seadColor.h>
#include <sead/prim/seadSafeString.hpp>

#include <type_traits>

#include "ParamNode.hpp"
#include "AglParam.hpp"

namespace Lp::Sys {

    /* Unoffical namespace. */
    namespace impl {
        template<typename T>
        struct TypeForAglParam { using Type = T; };

        /* WTF? */
        template <s32 StringSize>
        struct TypeForAglParam<sead::FixedSafeString<StringSize>> { using Type = sead::SafeString; };

        /* TODO: why doesn't this work? */
        // template <typename CharType, s32 StringSize>
        // struct TypeForAglParam<sead::FixedSafeStringBase<CharType, StringSize>> { using Type = sead::SafeStringBase<CharType>; };

        template<typename T>
        using TypeForAglParamT = TypeForAglParam<T>::Type;
    }

    template<typename T>
    struct Param : public ParamNode {
        SEAD_RTTI_OVERRIDE(Param<T>, ParamNode);

        T mData;
        AglParam<impl::TypeForAglParamT<T>> mAglParam;
        ulong unk;

        virtual uint typeId() const;
        virtual const char* typeName() const;
        virtual int size() const;
        virtual T& ref();
        virtual const T& ref() const;
        virtual T* ptr();
        virtual const T* ptr() const;
        virtual operator T&();
        virtual operator T const&() const;
        virtual T* operator->();
        virtual const T* operator->() const;
        virtual T* operator&();
        virtual const T* operator&() const;
        virtual T operator*();
        virtual T operator*() const;
        virtual bool operator==(Param<T> const&) const;
        virtual bool operator!=(Param<T> const&) const;
        virtual bool operator==(T const&) const;
        virtual bool operator!=(T const&) const;
        virtual bool readByamlArray(Lp::Utl::ByamlIter&, int);
        virtual void writeByamlArray(Lp::Utl::ByamlWriter&) const;
        virtual void writeYamlArray(Lp::Utl::YamlWriter&) const;
        virtual void writeStream_Label(sead::WriteStream&) const;
    };
    static_assert(offsetof(Param<int>, mData) == 0x4C);
    static_assert(sizeof(Param<int>) == 0xB0);
}

#undef COMMON_FUNCS