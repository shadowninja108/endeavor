#pragma once

#include "lua.hpp"
#include "Util.hpp"
#include "GlueArgument.hpp"

#include <concepts>
#include <tuple>
#include <utility>

namespace elua {

    /* My own implementation details, no gurantee it matches Nintendo's. */
    namespace impl::static_func {
        template<typename ReturnType, typename... Args>
        using FuncType = ReturnType (&)(Args...);

        template<typename ReturnType, typename... Args, size_t... Indicies>
        bool BindImpl(std::index_sequence<Indicies...>, lua_State* state, auto func) {
            static constexpr size_t ArgCount = sizeof...(Args);
            static constexpr bool HasReturnValue = !std::is_same_v<ReturnType, void>;

            /* Check if we have all the arguments. */
            if(!Util::checkCount(state, ArgCount)) {
                return false;
            }

            /* Check the types of all the arguments. */
            bool argTypeCheck = ( false || ... || !GlueArgument::checkType<Args>(state, Indicies+1) );
            if(argTypeCheck)
                return false;

            /* Collect all the args into a tuple. */
            auto args = std::tuple<Args...>(GlueArgument::get<Args>(state, Indicies+1)...);

            /* Special case void return, as `ret` can't be a void type. */
            if constexpr(HasReturnValue) {
                /* Call function with arguments, then push return value to stack. */
                ReturnType ret = std::apply(func, args);

                /* Pop arguments off stack. */
                for(size_t i = 0; i < ArgCount; i++)
                    Util::pop(state);

                /* Push return value onto stack. */
                GlueArgument::push(state, ret);
            } else {
                /* Just call the function with arguments. */
                std::apply(func, args);

                /* Pop arguments off stack. */
                for(size_t i = 0; i < ArgCount; i++)
                    Util::pop(state);
            }

            /* Successful, so return if there's a return value. */
            return HasReturnValue;
        }

        template<typename ReturnType, typename... Args>
        bool Bind(lua_State* state, FuncType<ReturnType, Args...> func) {
            return BindImpl<ReturnType, Args...>(std::make_index_sequence<sizeof...(Args)>{}, state, func);
        }
    }

    struct GlueStaticFunction {
        /* This is Nintendo's ABI, but my underlying implementation supports an arbitrary amount of arguments. */
        template<typename ReturnType, impl::static_func::FuncType<ReturnType> Func>
        struct Static0 {
            static bool Invoke(lua_State* state) {
                return impl::static_func::Bind<ReturnType>(state, Func);
            }
        };
        template<typename ReturnType, typename ArgType1, impl::static_func::FuncType<ReturnType, ArgType1> Func>
        struct Static1 {
            static bool Invoke(lua_State* state) {
                return impl::static_func::Bind<ReturnType, ArgType1>(state, Func);
            }
        };
        template<typename ReturnType, typename ArgType1, typename ArgType2, impl::static_func::FuncType<ReturnType, ArgType1, ArgType2> Func>
        struct Static2 {
            static bool Invoke(lua_State* state) {
                return impl::static_func::Bind<ReturnType, ArgType1, ArgType2>(state, Func);
            }
        };
        template<typename ReturnType, typename ArgType1, typename ArgType2, typename ArgType3, impl::static_func::FuncType<ReturnType, ArgType1, ArgType2, ArgType3> Func>
        struct Static3 {
            static bool Invoke(lua_State* state) {
                return impl::static_func::Bind<ReturnType, ArgType1, ArgType2, ArgType3>(state, Func);
            }
        };
        template<typename ReturnType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, impl::static_func::FuncType<ReturnType, ArgType1, ArgType2, ArgType3, ArgType4> Func>
        struct Static4 {
            static bool Invoke(lua_State* state) {
                return impl::static_func::Bind<ReturnType, ArgType1, ArgType2, ArgType3, ArgType4>(state, Func);
            }
        };

        template<typename ReturnType, impl::static_func::FuncType<ReturnType> Func>
        static bool Static(lua_State* state) {
            return Static0<ReturnType, Func>::Invoke(state);
        }
        template<typename ReturnType, typename ArgType1, impl::static_func::FuncType<ReturnType, ArgType1> Func>
        static bool Static(lua_State* state) {
            return Static1<ReturnType, ArgType1, Func>::Invoke(state);
        }
        template<typename ReturnType, typename ArgType1, typename ArgType2, impl::static_func::FuncType<ReturnType, ArgType1, ArgType2> Func>
        static bool Static(lua_State* state) {
            return Static2<ReturnType, ArgType1, ArgType2, Func>::Invoke(state);
        }
        template<typename ReturnType, typename ArgType1, typename ArgType2, typename ArgType3, impl::static_func::FuncType<ReturnType, ArgType1, ArgType2, ArgType3> Func>
        static bool Static(lua_State* state) {
            return Static3<ReturnType, ArgType1, ArgType2, ArgType3, Func>::Invoke(state);
        }
        template<typename ReturnType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, impl::static_func::FuncType<ReturnType, ArgType1, ArgType2, ArgType3, ArgType4> Func>
        static bool Static(lua_State* state) {
            return Static4<ReturnType, ArgType1, ArgType2, ArgType3, ArgType4, Func>::Invoke(state);
        }
    };
}