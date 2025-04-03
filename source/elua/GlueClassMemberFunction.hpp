#pragma once

#include <lib.hpp>

#include "lua.hpp"
#include "GlueStaticFunction.hpp"

namespace elua {

    /* My own implementation details, no gurantee it matches Nintendo's. */
    namespace impl::member_func {
        template<typename ThisType, typename ReturnType, typename... Args>
        using FuncType = ReturnType (ThisType::*)(Args...);
        template<typename ThisType, typename ReturnType, typename... Args>
        using ConstFuncType = ReturnType (ThisType::*)(Args...) const;

        /* Need to special case const and non-const function pointers. :( */
        template<typename ThisType, typename ReturnType, size_t... Indicies, typename... Args>
        bool BindImpl(std::index_sequence<Indicies...> indicies, lua_State* state, FuncType<ThisType, ReturnType, Args...> func) {
            return impl::static_func::BindImpl<ReturnType, ThisType*, Args...>(indicies, state, func);
        }

        template<typename ThisType, typename ReturnType, size_t... Indicies, typename... Args>
        bool BindImpl(std::index_sequence<Indicies...> indicies, lua_State* state, ConstFuncType<ThisType, ReturnType, Args...> func) {
            return impl::static_func::BindImpl<ReturnType, const ThisType*, Args...>(indicies, state, func);
        }

        /* +1 because we'll be adding the this pointer to the args. */
        template<typename ThisType, typename ReturnType, typename... Args>
        bool Bind(lua_State* state, FuncType<ThisType, ReturnType, Args...> func) {
            return BindImpl(std::make_index_sequence<sizeof...(Args)+1>{}, state, func);
        }
        template<typename ThisType, typename ReturnType, typename... Args>
        bool Bind(lua_State* state, ConstFuncType<ThisType, ReturnType, Args...> func) {
            return BindImpl(std::make_index_sequence<sizeof...(Args)+1>{}, state, func);
        }
    }

    struct GlueClassMemberFunction {
        /* This is Nintendo's ABI, but my underlying implementation supports an arbitrary amount of arguments. */
        template<typename ThisType, typename ReturnType, impl::member_func::FuncType<ThisType, ReturnType> Func>
        struct Member0 {
            static bool Invoke(lua_State* state) {
                return impl::member_func::Bind<ThisType, ReturnType>(state, Func);
            }
        };
        template<typename ThisType, typename ReturnType, impl::member_func::ConstFuncType<ThisType, ReturnType> Func>
        struct MemberConst0 {
            static bool Invoke(lua_State* state) {
                return impl::member_func::Bind<ThisType, ReturnType>(state, Func);
            }
        };
        template<typename ThisType, typename ReturnType, typename ArgType1, impl::member_func::FuncType<ThisType, ReturnType, ArgType1> Func>
        struct Member1 {
            static bool Invoke(lua_State* state) {
                return impl::member_func::Bind<ThisType, ReturnType, ArgType1>(state, Func);
            }
        };
        template<typename ThisType, typename ReturnType, typename ArgType1, impl::member_func::ConstFuncType<ThisType, ReturnType, ArgType1> Func>
        struct MemberConst1 {
            static bool Invoke(lua_State* state) {
                return impl::member_func::Bind<ThisType, ReturnType, ArgType1>(state, Func);
            }
        };
        template<typename ThisType, typename ReturnType, typename ArgType1, typename ArgType2, impl::member_func::FuncType<ThisType, ReturnType, ArgType1, ArgType2> Func>
        struct Member2 {
            static bool Invoke(lua_State* state) {
                return impl::member_func::Bind<ThisType, ReturnType, ArgType1, ArgType2>(state, Func);
            }
        };
        template<typename ThisType, typename ReturnType, typename ArgType1, typename ArgType2, impl::member_func::ConstFuncType<ThisType, ReturnType, ArgType1, ArgType2> Func>
        struct MemberConst2 {
            static bool Invoke(lua_State* state) {
                return impl::member_func::Bind<ThisType, ReturnType, ArgType1, ArgType2>(state, Func);
            }
        };

        template<typename ThisType, typename ReturnType, impl::member_func::FuncType<ThisType, ReturnType> Func>
        static bool Member(lua_State* state) {
            return Member0<ThisType, ReturnType, Func>::Invoke(state);
        }
        template<typename ThisType, typename ReturnType, impl::member_func::ConstFuncType<ThisType, ReturnType> Func>
        static bool Member(lua_State* state) {
            return MemberConst0<ThisType, ReturnType, Func>::Invoke(state);
        }
        template<typename ThisType, typename ReturnType, typename ArgType1, impl::member_func::FuncType<ThisType, ReturnType, ArgType1> Func>
        static bool Member(lua_State* state) {
            return Member1<ThisType, ReturnType, ArgType1, Func>::Invoke(state);
        }
        template<typename ThisType, typename ReturnType, typename ArgType1, impl::member_func::ConstFuncType<ThisType, ReturnType, ArgType1> Func>
        static bool Member(lua_State* state) {
            return MemberConst1<ThisType, ReturnType, ArgType1, Func>::Invoke(state);
        }
        template<typename ThisType, typename ReturnType, typename ArgType1, typename ArgType2, impl::member_func::FuncType<ThisType, ReturnType, ArgType1, ArgType2> Func>
        static bool Member(lua_State* state) {
            return Member2<ThisType, ReturnType, ArgType1, ArgType2, Func>::Invoke(state);
        }
        template<typename ThisType, typename ReturnType, typename ArgType1, typename ArgType2, impl::member_func::ConstFuncType<ThisType, ReturnType, ArgType1, ArgType2> Func>
        static bool Member(lua_State* state) {
            return MemberConst2<ThisType, ReturnType, ArgType1, ArgType2, Func>::Invoke(state);
        }
    };
}