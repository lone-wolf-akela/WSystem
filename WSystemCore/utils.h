#pragma once
#include <pch.h>

namespace utils
{
    template <typename T = void>
    struct const_ref_or_value_t {
        static constexpr bool value = std::disjunction_v<
            std::is_const<std::remove_reference_t<T>>,
            std::negation<std::is_reference<T>>
        >;
    };

    template <>
    struct const_ref_or_value_t<void> {
        static constexpr bool value = true;
    };

    template <typename ... Types>
    struct VariadicStructFactory
    {
        using TypeList = std::tuple<Types...>;

        template <std::size_t Index>
        using NthType = decltype(std::get<Index>(std::declval<TypeList>()));

        template <std::size_t Index>
        struct Field
        {
            using FieldType = std::remove_cvref_t<NthType<Index>>;
            FieldType field;

            explicit Field(const FieldType& arg) : field(arg) {}
            explicit Field(FieldType&& arg) : field(std::move(arg)) {}
        };

        template <std::size_t ... I>
        struct VariadicStructImpl : Field<I>...
        {
            constexpr static size_t NumFields = sizeof...(Types);

            template <std::size_t Index>
            auto& GetN() { return static_cast<Field<Index>*>(this)->field; }

            auto& GetFirstMember() { return GetN<0>(); }
            auto& GetLastMember() { return GetN<NumFields - 1>(); }

            template<typename... ArgTypes>
            explicit VariadicStructImpl(ArgTypes&&... args) : Field<I>{ std::forward<ArgTypes>(args) }... {}
        };

        template <std::size_t ... I>
        constexpr static VariadicStructImpl<I...> FromList(std::index_sequence<I...>); // intentional not implemented

        using Ret = decltype(FromList(std::make_index_sequence<sizeof...(Types)>{}));
    };

    template <typename ... Types>
    using VariadicStruct = typename VariadicStructFactory<Types...>::Ret;

    template<typename... Args>
    void call_unreal_function_void(RC::Unreal::UObject* obj, RC::Unreal::UFunction* func, Args&&... args)
    {
        if constexpr (sizeof...(Args) == 0)
        {
            obj->ProcessEvent(func, nullptr);
        }
        else
        {
            VariadicStruct<Args...> args_struct(std::forward<Args>(args)...);
            obj->ProcessEvent(func, &args_struct);
        }
    }

    template<typename Ret, typename... Args>
    Ret call_unreal_function(RC::Unreal::UObject* obj, RC::Unreal::UFunction* func, Args&&... args)
    {
        VariadicStruct<Args..., Ret> args_struct(std::forward<Args>(args)..., Ret{});
        obj->ProcessEvent(func, &args_struct);
        return std::move(args_struct.GetLastMember());
    }

    template<typename RefArg, typename... Args>
    void call_unreal_function_void_ref(RC::Unreal::UObject* obj, RC::Unreal::UFunction* func, RefArg& ref_arg, Args&&... args)
    {
        VariadicStruct<std::add_rvalue_reference_t<std::remove_cvref_t<RefArg>>, Args...> args_struct(std::move(ref_arg), std::forward<Args>(args)...);
        obj->ProcessEvent(func, &args_struct);
        ref_arg = std::move(args_struct.GetFirstMember());
    }

	template<typename Ret, typename RefArg, typename... Args>
	Ret call_unreal_function_ref(RC::Unreal::UObject* obj, RC::Unreal::UFunction* func, RefArg& ref_arg, Args&&... args)
    {
		VariadicStruct<std::add_rvalue_reference_t<std::remove_cvref_t<RefArg>>, Args..., Ret> args_struct(std::move(ref_arg), std::forward<Args>(args)..., Ret{});
		obj->ProcessEvent(func, &args_struct);
        ref_arg = std::move(args_struct.GetFirstMember());
		return std::move(args_struct.GetLastMember());
	}
}


#define WSYS_DATA_PROPERTY(type, name) \
[[nodiscard]] type& Internal_Get##name() const\
{\
	return *GetPropertyValueByName<type>(STR(#name));\
}\
type& Internal_Set##name(const type& value)\
{\
	return *GetPropertyValueByName<type>(STR(#name)) = value;\
}\
type& Internal_Set##name(type&& value)\
{\
	return *GetPropertyValueByName<type>(STR(#name)) = std::move(value);\
}\
__declspec(property(get = Internal_Get##name, put = Internal_Set##name)) type& name;

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

#define WSYS_EXTRACT_FIRST(x, y) x
#define WSYS_EXTRACT_EACH_PAIR_FIRST(...) WSYS_FOR_EACH(WSYS_EXTRACT_FIRST, __VA_ARGS__)

#define WSYS_CHECKTYPE_OP(s, state, x) state static_assert(utils::const_ref_or_value_t<x>::value);
#define WSYS_CHECKTYPE_IMPL(...) BOOST_PP_SEQ_FOLD_LEFT(WSYS_CHECKTYPE_OP, ;, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#define WSYS_CHECKTYPE_LIST(...) WSYS_CHECKTYPE_IMPL(WSYS_EXTRACT_EACH_PAIR_FIRST(__VA_ARGS__))

#define WSYS_MEMBER_FUNCTION_VOID(name, ...) void name(\
    WSYS_CONCAT_EACH_PAIR(__VA_ARGS__),\
    const std::source_location& location = std::source_location::current()\
) const\
{\
    WSYS_CHECKTYPE_LIST(__VA_ARGS__)\
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
    WSYS_CHECKTYPE_LIST(__VA_ARGS__)\
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

// special ref functions

#define WSYS_MEMBER_FUNCTION_VOID_REF(name, reftype, refarg,...) void name(\
    reftype refarg __VA_OPT__(,) WSYS_CONCAT_EACH_PAIR(__VA_ARGS__),\
    const std::source_location& location = std::source_location::current()\
) const\
{\
    static_assert(std::is_reference_v<reftype>);\
    WSYS_CHECKTYPE_LIST(__VA_ARGS__)\
    CallFunctionVoidRef(STR(#name), location, refarg __VA_OPT__(,) WSYS_EXTRACT_EACH_SECOND(__VA_ARGS__));\
}\
WSYS_GET_MEMBER_FUNCTION(name)

#define WSYS_MEMBER_FUNCTION_REF(ret, name, reftype, refarg,...) ret name(\
    reftype refarg __VA_OPT__(,) WSYS_CONCAT_EACH_PAIR(__VA_ARGS__),\
    const std::source_location& location = std::source_location::current()\
) const\
{\
    static_assert(std::is_reference_v<reftype>);\
    WSYS_CHECKTYPE_LIST(__VA_ARGS__)\
    return CallFunctionRef<ret>(STR(#name), location, refarg __VA_OPT__(,) WSYS_EXTRACT_EACH_SECOND(__VA_ARGS__));\
}\
WSYS_GET_MEMBER_FUNCTION(name)





