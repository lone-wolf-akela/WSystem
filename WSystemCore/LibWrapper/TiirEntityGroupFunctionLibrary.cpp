#include <pch.h>
#include "TiirEntityGroupFunctionLibrary.h"

void TiirEntityGroupFunctionLibrary::GroupMembers(const TiirEntityGroup& Group, UC::TArray<TiirEntity>& members, const std::source_location& location) const
{
	const auto func = FindFunction(STR("GroupMembers"), location);
	struct {
		TiirEntityGroup Group;
		UC::TArray<TiirEntity> members;
	} args{
		Group,
		std::move(members)
	};
	lib_class->ProcessEvent(func, &args);
	members = std::move(args.members);
}

void TiirEntityGroupFunctionLibrary::AddStatusEffect(const TiirEntityGroup& group, const StatusEffectStaticData status,
	UC::TArray<TiirStatusEffectHandle>& out_handles, const std::source_location& location) const
{
	const auto func = FindFunction(STR("AddStatusEffect"), location);
	struct {
		TiirEntityGroup group;
		StatusEffectStaticData status;
		UC::TArray<TiirStatusEffectHandle> out_handles;
	} args{
		group,
		status,
		std::move(out_handles)
	};
	lib_class->ProcessEvent(func, &args);
	out_handles = std::move(args.out_handles);
}
