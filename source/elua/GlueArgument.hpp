#pragma once

#include <type_traits>

#include <common.hpp>
#include <sead/prim/seadSafeString.hpp>
#include <sead/math/seadVector.hpp>

#include "lua.hpp"

namespace elua {
    struct GlueArgument {
        template<typename T>
        static bool checkType(lua_State*, int) {
            static_assert(false, "Requires explicit implementation");
            return false;
        }
        template<typename T>
        static T get(lua_State*, int) {
            static_assert(false, "Requires explicit implementation");
            return {};
        }
        template<typename T>
        static void push(lua_State*, T) {
            static_assert(false, "Requires explicit implementation");
        }
    };

    #define DECL(type)                                      \
    template<>                                              \
    bool GlueArgument::checkType<type>(lua_State*, int);    \
    template<>                                              \
    type GlueArgument::get<type>(lua_State*, int);          \
    template<>                                              \
    void GlueArgument::push<type>(lua_State*, type)

    DECL(bool);
    DECL(signed char);
    DECL(short);
    DECL(int);
    DECL(long);
    DECL(uchar);
    DECL(ushort);
    DECL(uint);
    DECL(ulong);
    DECL(float);
    DECL(double);
    DECL(const char*);
    DECL(sead::SafeString const);
    DECL(sead::Vector3f*);
    DECL(sead::Vector3f&);
    DECL(sead::Vector3f);
    DECL(sead::Vector3f const*);
    DECL(sead::Vector3f const&);
    DECL(sead::Vector3f const);

    #undef DECL
}