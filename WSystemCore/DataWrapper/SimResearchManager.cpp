#include <pch.h>
#include "SimResearchManager.h"

FResearchData USimResearchManager::GetResearchState(UResearchStaticData research_data, bool& is_valid, const std::source_location& location) const
{
	const auto func = FindFunction(STR("GetResearchState"), location);
	struct {
		UResearchStaticData research_data;
		bool is_valid;
		FResearchData result;
	} args{
		research_data,
		is_valid,
		{}
	};
	obj->ProcessEvent(func, &args);
	is_valid = args.is_valid;
	return args.result;
}
