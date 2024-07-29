#include <pch.h>
#include "ProductionComponent.h"

BuildJobType ProductionComponent::GetJobTypeState(const EntityStaticData UnitType, bool& bValid,
	const std::source_location& location) const
{
	const auto func = FindFunction(STR("GetJobTypeState"), location);
	struct {
		EntityStaticData UnitType;
		bool bValid;
		BuildJobType result;
	} args{
		UnitType,
		bValid,
		{}
	};
	obj->ProcessEvent(func, &args);
	bValid = args.bValid;
	return args.result;
}
