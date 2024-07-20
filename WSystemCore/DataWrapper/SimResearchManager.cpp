#include <pch.h>
#include "SimResearchManager.h"

ResearchData SimResearchManager::GetResearchState(ResearchStaticData research_data, bool& is_valid) const
{
	const auto func = FindFunction(STR("GetResearchState"));
	struct {
		ResearchStaticData research_data;
		bool is_valid;
		ResearchData result;
	} args{
		research_data,
		is_valid,
		ResearchData{}
	};
	obj->ProcessEvent(func, &args);
	is_valid = args.is_valid;
	return args.result;
}
