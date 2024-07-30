#include <pch.h>
#include "ProductionComponent.h"

FBuildJobType UProductionComponent::GetJobTypeState(const UEntityStaticData UnitType, bool& bValid,
	const std::source_location& location) const
{
	const auto func = FindFunction(STR("GetJobTypeState"), location);
	struct {
		UEntityStaticData UnitType;
		bool bValid;
		FBuildJobType result;
	} args{
		UnitType,
		bValid,
		{}
	};
	obj->ProcessEvent(func, &args);
	bValid = args.bValid;
	return args.result;
}
