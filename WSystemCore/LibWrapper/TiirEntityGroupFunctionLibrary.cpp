#include <pch.h>
#include "TiirEntityGroupFunctionLibrary.h"

void TiirEntityGroupFunctionLibrary::GroupMembers(const TiirEntityGroup& Group, UC::TArray<TiirEntity>& members) const
{
	const auto func = FindFunction(STR("GroupMembers"));
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
	UC::TArray<TiirStatusEffectHandle>& out_handles) const
{
	const auto func = FindFunction(STR("AddStatusEffect"));
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
