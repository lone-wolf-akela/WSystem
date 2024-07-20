#include <pch.h>
#include "TiirEntityFunctionLibrary.h"

bool TiirEntityFunctionLibrary::GetMetaDataValue(const TiirEntity& entity, const Unreal::FString& key,
	std::int32_t& value) const
{
	const auto func = FindFunction(STR("GetMetaDataValue"));
	struct {
		TiirEntity entity;
		Unreal::FString key;
		std::int32_t value;
		bool result;
	} args{
		entity,
		key,
		value,
		{}
	};
	lib_class->ProcessEvent(func, &args);
	value = args.value;
	return args.result;
}
