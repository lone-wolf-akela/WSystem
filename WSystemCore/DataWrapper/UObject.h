#pragma once
#include <pch.h>

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
    friend std::strong_ordering operator<=>(const UObjWrapper& lhs, const UObjWrapper& rhs) noexcept;
    friend bool operator==(const UObjWrapper& lhs, const UObjWrapper& rhs) noexcept;
    UObjWrapper* operator&() noexcept = delete;  // NOLINT(google-runtime-operator)
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
		return utils::call_unreal_function<Ret>(obj, func, std::forward<Args>(args)...);
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

    template<typename Ret, typename... Args>
    Ret CallFunctionRef(
        const TCHAR* name,
        const std::source_location& location,
        Args&&... args
    ) const
    {
        const auto func = FindFunction(name, location);
        return utils::call_unreal_function_ref<Ret>(obj, func, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void CallFunctionVoidRef(
        const TCHAR* name,
        const std::source_location& location,
        Args&&... args
    ) const
    {
        const auto func = FindFunction(name, location);
        utils::call_unreal_function_void_ref(obj, func, std::forward<Args>(args)...);
    }
};
