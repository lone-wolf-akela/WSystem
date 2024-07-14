#pragma once
#include <utility>
#include <source_location>

#include <Unreal/UObject.hpp>
#include <Unreal/FProperty.hpp>
#include <Unreal/UFunction.hpp>

#include <utils.h>

class UObjWrapper
{
public:
    RC::Unreal::UObject* obj;

    UObjWrapper() : obj(nullptr) {}
    // ReSharper disable once CppNonExplicitConvertingConstructor
    UObjWrapper(RC::Unreal::UObject* obj);
    [[nodiscard]] bool IsValid() const noexcept;
    RC::Unreal::UObject* operator->() const;

protected:
    [[nodiscard]] RC::Unreal::FProperty* FindProperty(
        const TCHAR* name,
        const std::source_location& location = std::source_location::current()
    ) const;
    [[nodiscard]] void* GetPropertyValue(
        RC::Unreal::FProperty* prop, 
        const std::source_location& location = std::source_location::current()
    ) const;
    [[nodiscard]] RC::Unreal::UFunction* FindFunction(
        const TCHAR* name,
        const std::source_location& location = std::source_location::current()
    ) const;


    template<typename T>
    [[nodiscard]] T* GetPropertyValueWithType(
        RC::Unreal::FProperty* prop,
        const std::source_location& location = std::source_location::current()
    ) const
    {
        const auto value = GetPropertyValue(prop, location);
        return static_cast<T*>(value);
    }

    template<typename T>
    [[nodiscard]] T* GetPropertyValueByName(
		const TCHAR* name,
		const std::source_location& location = std::source_location::current()
	) const
	{
		auto prop = FindProperty(name, location);
		return GetPropertyValueWithType<T>(prop, location);
	}

	template<typename Ret, typename... Args>
	Ret CallFunction(
		const TCHAR* name,
        const std::source_location& location,
		Args&&... args
	) const
	{
		const auto func = FindFunction(name, location);
		return utils::call_unreal_function<Ret, Args...>(obj, func, std::forward<Args>(args)...);
	}

    template<typename... Args>
    void CallFunctionVoid(
		const TCHAR* name,
        const std::source_location& location,
		Args&&... args
	) const
	{
		const auto func = FindFunction(name, location);
		utils::call_unreal_function_void(obj, func, std::forward<Args>(args)...);
	}
};
