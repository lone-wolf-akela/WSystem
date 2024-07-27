#pragma once
#include <pch.h>

#include <DataWrapper/RavenSimulationProxy.h>
#include <DataWrapper/RavenHUD.h>
#include <DataWrapper/WBP_BuildPanel.h>

#include <LibWrapper/TiirResearchFunctionLibrary.h>

struct BuildCondition
{
	std::vector<StringType> RequiredAllOfUnitsFleetwise;
	std::vector<StringType> RequiredNoneOfUnitsFleetwise;
	std::vector<StringType> RequiredAllOfUnitsThisShip;
	std::vector<StringType> RequiredNoneOfUnitsThisShip;
	std::vector<StringType> RequiredAllOfResearches;
	std::vector<StringType> RequiredNoneOfResearches;
};

enum class BuildConditionCheckResult
{
	Buildable,
	NotBuildable,
	DoNotCare,
};

struct BuildConditionGroup
{
	std::vector<BuildCondition> RequiredAnyOf;
};

struct BuildOptionList
{
	// ship_to_build -> conditions
	std::map<StringType, BuildConditionGroup, std::less<>> BuildOptions;
};

struct ResearchCondition
{
	std::vector<StringType> RequiredAllOfUnits;
	std::vector<StringType> RequiredNoneOfUnits;
	std::vector<StringType> RequiredAllOfResearches;
	std::vector<StringType> RequiredNoneOfResearches;
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

class BuildConditionController
{
public:
	// build_from_ship -> ship_to_build -> conditions
	std::map<StringType, BuildOptionList, std::less<>> BuildConditions;
	BuildConditionCheckResult CheckBuildCondition(
		StringViewType build_from_ship,
		StringViewType ship_to_build,
		const std::set<StringType>& fleet_owned_units,
		const std::set<StringType>& done_researches,
		const std::set<StringType>& this_ship_owned_units
		) const;
	std::vector<StringType> GetBuildOptionList(StringViewType build_from_ship) const;
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

	void Begin_InGame(RavenSimulationProxy sim_proxy, RavenHUD hud, WBP_BuildPanel build_panel);
	void Tick();
	bool EnableTick = false;
	ResearchConditionController ConditionController;
	BuildConditionController BuildController;
private:
	TiirResearchFunctionLibrary* tiir_research_function_library;
	RavenSimulationProxy sim_proxy = nullptr;
	RavenHUD hud = nullptr;
	WBP_BuildPanel build_panel = nullptr;
	bool functions_hooked = false;
	void PostBuildPanelGetBuildListOfProductionEntity(
		Unreal::UnrealScriptFunctionCallableContext& context,
		void* custom_data) const;
	// build_from_ship -> ship_to_build -> result
	std::map<std::uint64_t, std::map<StringType, BuildConditionCheckResult>> build_capability_cache;
	[[nodiscard]] BuildConditionCheckResult CanShipBuild(SimShip production_ship, ShipStaticData ship_to_build) const;
	void NotifyResearchChanged(SimPlayer player, const ResearchData& data) const;
	void UpdateResearchStatus(std::int32_t player_idx, SimPlayer player, const UC::TArray<ResearchData>& research_list, const std::set<StringType>& owned_ship_types, const std::set<StringType>& done_research_list) const;
	bool UpdateBuildStatus(const UC::TArray<SimEntity>& entity_list, const std::set<StringType>& owned_ship_types, const std::set<StringType>& done_research_list);
	void NotifyBuildListChanged() const;
};