#pragma once
#include <Unreal/UObject.hpp>

namespace utils
{
    template<typename Head, typename... Tail>
    struct VariadicStruct {
        Head Value;
        VariadicStruct<Tail...> Rest;

        explicit VariadicStruct(Head head, Tail... tail) : Value(head), Rest(tail...) {}
    };

    template<typename Head>
    struct VariadicStruct<Head> {
        Head Value;

        explicit VariadicStruct(Head head) : Value(head) {}
    };

    template<typename Head, typename... Tail>
    auto& get_last_member(VariadicStruct<Head, Tail...>& vs) {
        return get_last_member(vs.Rest);
    }

    template<typename Head>
    Head& get_last_member(VariadicStruct<Head>& vs) {
        return vs.Value;
    }

    template<typename... Args>
    void call_unreal_function_void(RC::Unreal::UObject* obj, RC::Unreal::UFunction* func, Args... args) {
        if constexpr (sizeof...(Args) == 0)
        {
            obj->ProcessEvent(func, nullptr);
        }
        else
        {
            VariadicStruct args_struct(args...);
            obj->ProcessEvent(func, &args_struct);
        }
    }

    template<typename Ret, typename... Args>
    Ret call_unreal_function(RC::Unreal::UObject* obj, RC::Unreal::UFunction* func, Args... args) {
        VariadicStruct args_struct(args..., Ret{});
        obj->ProcessEvent(func, &args_struct);
        return get_last_member(args_struct);
    }
}


#define WSYS_DATA_PROPERTY(type, name) [[nodiscard]] auto Get##name(\
    const std::source_location& location = std::source_location::current()\
) const\
{\
	return GetPropertyValueByName<type>(STR(#name), location);\
}

#define WSYS_GET_MEMBER_FUNCTION(name) [[nodiscard]] RC::Unreal::UFunction* GetFunc##name(\
    const std::source_location& location = std::source_location::current()\
) const\
{\
    return FindFunction(STR(#name), location);\
}

// https://stackoverflow.com/questions/45756920/c-c-preprocessor-extract-every-second-variadic-parameter

#define WSYS_PARENS ()
#define WSYS_EXPAND(...) WSYS_EXPAND4(WSYS_EXPAND4(WSYS_EXPAND4(WSYS_EXPAND4(__VA_ARGS__))))
#define WSYS_EXPAND4(...) WSYS_EXPAND3(WSYS_EXPAND3(WSYS_EXPAND3(WSYS_EXPAND3(__VA_ARGS__))))
#define WSYS_EXPAND3(...) WSYS_EXPAND2(WSYS_EXPAND2(WSYS_EXPAND2(WSYS_EXPAND2(__VA_ARGS__))))
#define WSYS_EXPAND2(...) WSYS_EXPAND1(WSYS_EXPAND1(WSYS_EXPAND1(WSYS_EXPAND1(__VA_ARGS__))))
#define WSYS_EXPAND1(...) __VA_ARGS__

#define WSYS_FOR_EACH(macro, ...)                                    \
  __VA_OPT__(WSYS_EXPAND(WSYS_FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define WSYS_FOR_EACH_HELPER(macro, a1, a2, ...)                     \
  macro(a1, a2)                                                 \
  __VA_OPT__(, WSYS_FOR_EACH_AGAIN WSYS_PARENS (macro, __VA_ARGS__))
#define WSYS_FOR_EACH_AGAIN() WSYS_FOR_EACH_HELPER

#define WSYS_EXTRACT_SECOND(x, y) y
#define WSYS_EXTRACT_EACH_SECOND(...) WSYS_FOR_EACH(WSYS_EXTRACT_SECOND, __VA_ARGS__)

#define WSYS_CONCAT_2(x, y) x y
#define WSYS_CONCAT_EACH_PAIR(...) WSYS_FOR_EACH(WSYS_CONCAT_2, __VA_ARGS__)

#define WSYS_MEMBER_FUNCTION_VOID(name, ...) void name(\
    WSYS_CONCAT_EACH_PAIR(__VA_ARGS__),\
    const std::source_location& location = std::source_location::current()\
) const\
{\
    CallFunctionVoid(STR(#name), location, WSYS_EXTRACT_EACH_SECOND(__VA_ARGS__));\
}\
WSYS_GET_MEMBER_FUNCTION(name)

#define WSYS_MEMBER_FUNCTION_VOID_NOARGS(name) void name(\
    const std::source_location& location = std::source_location::current()\
) const\
{\
    CallFunctionVoid(STR(#name), location);\
}\
WSYS_GET_MEMBER_FUNCTION(name)

#define WSYS_MEMBER_FUNCTION(ret, name, ...) ret name(\
    WSYS_CONCAT_EACH_PAIR(__VA_ARGS__),\
    const std::source_location& location = std::source_location::current()\
) const\
{\
    return CallFunction<ret>(STR(#name), location, WSYS_EXTRACT_EACH_SECOND(__VA_ARGS__));\
}\
WSYS_GET_MEMBER_FUNCTION(name)


#define WSYS_MEMBER_FUNCTION_NOARGS(ret, name) ret name(\
 const std::source_location& location = std::source_location::current()\
) const\
{\
    return CallFunction<ret>(STR(#name), location);\
}\
WSYS_GET_MEMBER_FUNCTION(name)

