#pragma once
#include <utility>

#include <boost/nowide/convert.hpp>

#include <Unreal/UClass.hpp>
#include <Unreal/UFunction.hpp>

#include <utils.h>

template<typename T>
concept HasLibPath = requires
{
	{ T::LibPath } -> std::convertible_to<const TCHAR*>;
};

template<typename LibT>
class LibBase
{
public:
	[[nodiscard]] RC::Unreal::UClass* GetLibClass() const
	{
		return lib_class;
	}
	void Init(const std::source_location& location = std::source_location::current())
	{
		lib_class = RC::Unreal::UObjectGlobals::StaticFindObject<RC::Unreal::UClass*>(
			nullptr, 
			nullptr, 
			LibT::LibPath);
		if (!lib_class)
		{
			RC::Output::send<RC::LogLevel::LogLevel::Error>(
				STR("{}({}:{}) `{}`: Failed to find lib: {}\n"),
				boost::nowide::widen(location.file_name()),
				location.line(),
				location.column(),
				boost::nowide::widen(location.function_name()),
				LibT::LibPath);
		}
	}
protected:
	RC::Unreal::UClass* lib_class = nullptr;

	LibT* Lib()
	{ 
		return static_cast<LibT*>(this); 
	}

	[[nodiscard]] RC::Unreal::UFunction* FindFunction(
		const TCHAR* name,
		const std::source_location& location = std::source_location::current()
	) const
	{
		if (!lib_class)
		{
			RC::Output::send<RC::LogLevel::LogLevel::Error>(
				STR("{}({}:{}) `{}`: lib_class has not been initialized.\n"),
				boost::nowide::widen(location.file_name()),
				location.line(),
				location.column(),
				boost::nowide::widen(location.function_name()));
			return nullptr;
		}
		if (const auto func = RC::Unreal::UObjectGlobals::StaticFindObject<RC::Unreal::UFunction*>(
			nullptr, nullptr,
			fmt::format(STR("{}:{}"), LibT::LibPath, name).c_str()))
		{
			return func;
		}
		else
		{
			RC::Output::send<RC::LogLevel::LogLevel::Error>(
				STR("{}({}:{}) `{}`: Failed to find function `{}`.\n"),
				boost::nowide::widen(location.file_name()),
				location.line(),
				location.column(),
				boost::nowide::widen(location.function_name()),
				name);
			return nullptr;
		}
	}

	template<typename Ret, typename... Args>
	Ret CallFunction(
		const TCHAR* name,
		const std::source_location& location,
		Args&&... args
	) const
	{
		const auto func = FindFunction(name, location);
		return utils::call_unreal_function<Ret, Args...>(lib_class, func, std::forward<Args>(args)...);
	}

	template<typename... Args>
	void CallFunctionVoid(
		const TCHAR* name,
		const std::source_location& location,
		Args&&... args
	) const
	{
		const auto func = FindFunction(name, location);
		utils::call_unreal_function_void(lib_class, func, std::forward<Args>(args)...);
	}
};
