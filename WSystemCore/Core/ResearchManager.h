#pragma once

#include <vector>
#include <string>
#include <map>
#include <set>

#include <DataWrapper/RavenSimulationProxy.h>
#include <DataWrapper/RavenHUD.h>

#include <LibWrapper/TiirResearchFunctionLibrary.h>


struct ResearchCondition
{
	std::vector<RC::StringType> RequiredAllOfUnits;
	std::vector<RC::StringType> RequiredNoneOfUnits;
	std::vector<RC::StringType> RequiredAllOfResearches;
	std::vector<RC::StringType> RequiredNoneOfResearches;
};

struct ResearchConditionGroup
{
	std::vector<ResearchCondition> RequiredAnyOf;
};

enum class ResearchConditionCheckResult
{
	Unlocked,
	Locked,
	DoNotCare,
};

class ResearchConditionController
{
public:
	std::map<RC::StringType, ResearchConditionGroup, std::less<>> ResearchConditions;
	ResearchConditionCheckResult CheckResearchCondition(
		RC::StringViewType target_research,
		const std::set<RC::StringType>& owned_units,
		const std::set<RC::StringType>& done_researches
		) const;
};

class WSysResearchManager
{
public:
	explicit WSysResearchManager(TiirResearchFunctionLibrary* tiir_research_function_library);

	void Bind(RavenSimulationProxy sim_proxy, RavenHUD hud);
	void Tick() const;
	bool EnableTick = false;
	ResearchConditionController ConditionController;
private:
	TiirResearchFunctionLibrary* tiir_research_function_library;
	RavenSimulationProxy sim_proxy = nullptr;
	RavenHUD hud = nullptr;

	void NotifyResearchChanged(SimPlayer player, ResearchData data) const;
};