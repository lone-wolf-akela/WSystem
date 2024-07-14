#include <boost/nowide/convert.hpp>

#include "UObject.h"

UObjWrapper::UObjWrapper(RC::Unreal::UObject* obj) :
	obj(obj)
{
}

bool UObjWrapper::IsValid() const noexcept
{
	return obj != nullptr;
}

RC::Unreal::UObject* UObjWrapper::operator->() const
{
	return obj;
}

RC::Unreal::FProperty* UObjWrapper::FindProperty(const TCHAR* name, const std::source_location& location) const
{
	if (!IsValid())
	{
		RC::Output::send<RC::LogLevel::LogLevel::Error>(
			STR("{}({}:{}) `{}`: Invalid object.\n"),
			boost::nowide::widen(location.file_name()),
			location.line(),
			location.column(),
			boost::nowide::widen(location.function_name()));
		return nullptr;
	}
	if (const auto prop = obj->GetPropertyByNameInChain(name))
	{
		return prop;
	}
	else
	{
		RC::Output::send<RC::LogLevel::LogLevel::Error>(
			STR("{}({}:{}) `{}`: Failed to find property `{}`.\n"),
			boost::nowide::widen(location.file_name()),
			location.line(),
			location.column(),
			boost::nowide::widen(location.function_name()),
			name);
		return nullptr;
	}
}

void* UObjWrapper::GetPropertyValue(RC::Unreal::FProperty* prop, const std::source_location& location) const
{
	if (!prop)
	{
		return nullptr;
	}
	if(!IsValid())
	{
		RC::Output::send<RC::LogLevel::LogLevel::Error>(
			STR("{}({}:{}) `{}`: Invalid object.\n"),
			boost::nowide::widen(location.file_name()),
			location.line(),
			location.column(),
			boost::nowide::widen(location.function_name()));
		return nullptr;
	}

	if (const auto value = prop->ContainerPtrToValuePtr<void>(obj))
	{
		return value;
	}
	else
	{
		RC::Output::send<RC::LogLevel::LogLevel::Error>(
			STR("{}({}:{}) `{}`: Failed to get property value.\n"),
			boost::nowide::widen(location.file_name()),
			location.line(),
			location.column(),
			boost::nowide::widen(location.function_name()));
		return nullptr;
	}
}

RC::Unreal::UFunction* UObjWrapper::FindFunction(const TCHAR* name, const std::source_location& location) const
{
	if (!IsValid())
	{
		RC::Output::send<RC::LogLevel::LogLevel::Error>(
			STR("{}({}:{}) `{}`: Invalid object.\n"),
			boost::nowide::widen(location.file_name()),
			location.line(),
			location.column(),
			boost::nowide::widen(location.function_name()));
		return nullptr;
	}
	if (const auto func = obj->GetFunctionByNameInChain(name))
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

std::strong_ordering operator<=>(const UObjWrapper& lhs, const UObjWrapper& rhs) noexcept
{
	return lhs.obj <=> rhs.obj;
}
