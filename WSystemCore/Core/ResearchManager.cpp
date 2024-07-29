#include <pch.h>

#include <DataWrapper/SimPlayer.h>
#include <DataWrapper/ResearchStaticData.h>
#include <DataWrapper/SimEntity.h>
#include <DataWrapper/SimShip.h>

#include "ResearchManager.h"

BuildConditionCheckResult BuildConditionController::CheckBuildCondition(
	StringViewType build_from_ship,
	StringViewType ship_to_build, 
	const std::set<StringType>& fleet_owned_units,
	const std::set<StringType>& done_researches, 
	const std::set<StringType>& this_ship_owned_units) const
{
	if (!BuildConditions.contains(build_from_ship))
	{
		return BuildConditionCheckResult::DoNotCare;
	}
	auto& build_option_list = BuildConditions.find(build_from_ship)->second;
	if (!build_option_list.BuildOptions.contains(ship_to_build))
	{
		return BuildConditionCheckResult::DoNotCare;
	}
	auto& build_condition_group = build_option_list.BuildOptions.find(ship_to_build)->second;

	for (auto& condition : build_condition_group.RequiredAnyOf)
	{
		for (auto& unit : condition.RequiredAllOfUnitsFleetwise)
		{
			if (!fleet_owned_units.contains(unit))
			{
				goto next_condition;
			}
		}
		for (auto& unit : condition.RequiredNoneOfUnitsFleetwise)
		{
			if (fleet_owned_units.contains(unit))
			{
				goto next_condition;
			}
		}
		for (auto& unit : condition.RequiredAllOfUnitsThisShip)
		{
			if (!this_ship_owned_units.contains(unit))
			{
				goto next_condition;
			}
		}
		for (auto& unit : condition.RequiredNoneOfUnitsThisShip)
		{
			if (this_ship_owned_units.contains(unit))
			{
				goto next_condition;
			}
		}
		for (auto& research : condition.RequiredAllOfResearches)
		{
			if (!done_researches.contains(research))
			{
				goto next_condition;
			}
		}
		for (auto& research : condition.RequiredNoneOfResearches)
		{
			if (done_researches.contains(research))
			{
				goto next_condition;
			}
		}
		return BuildConditionCheckResult::Buildable;
	next_condition:
		;
	}
	return BuildConditionCheckResult::NotBuildable;
}

std::vector<StringType> BuildConditionController::GetBuildOptionList(StringViewType build_from_ship) const
{
	std::vector<StringType> build_options;
	if (const auto found = BuildConditions.find(build_from_ship); found != BuildConditions.end())
	{
		for(const auto& ship_to_build : found->second.BuildOptions | std::views::keys)
		{
			build_options.emplace_back(ship_to_build);
		}
	}

	return build_options;
}

ResearchConditionCheckResult ResearchConditionController::CheckResearchCondition(
	RC::StringViewType target_research,
	const std::set<RC::StringType>& owned_units,
	const std::set<RC::StringType>& done_researches) const
{
	const auto research_condition = ResearchConditions.find(target_research);
	if (research_condition == ResearchConditions.end())
	{
		return ResearchConditionCheckResult::DoNotCare;
	}

	for (auto& condition : research_condition->second.RequiredAnyOf)
	{
		for (auto& unit : condition.RequiredAllOfUnits)
		{
			if (!owned_units.contains(unit))
			{
				goto next_condition;
			}
		}
		for (auto& ship : condition.RequiredNoneOfUnits)
		{
			if (owned_units.contains(ship))
			{
				goto next_condition;
			}
		}
		for (auto& research : condition.RequiredAllOfResearches)
		{
			if (!done_researches.contains(research))
			{
				goto next_condition;
			}
		}
		for (auto& research : condition.RequiredNoneOfResearches)
		{
			if (done_researches.contains(research))
			{
				goto next_condition;
			}
		}
		return ResearchConditionCheckResult::Unlocked;
	next_condition:
		;
	}

	return ResearchConditionCheckResult::Locked;
}

WSysResearchManager::WSysResearchManager(TiirResearchFunctionLibrary* tiir_research_function_library, SimOrderFactory* sim_order_factory, Database* database) :
	tiir_research_function_library(tiir_research_function_library),
	sim_order_factory(sim_order_factory),
	database(database)
{
}

void WSysResearchManager::Begin_InGame(RavenSimulationProxy sim_proxy, RavenHUD hud, WBP_BuildPanel build_panel, RTSPlayerUnitOrderComponent unit_order_component)
{
	this->sim_proxy = sim_proxy;
	this->hud = hud;
	this->build_panel = build_panel;
	this->unit_order_component = unit_order_component;

	if (!functions_hooked)
	{
		Unreal::UObjectGlobals::RegisterHook(
			STR("/Game/Assets/UI/Shared/WBP_Base_BuildPanel.WBP_Base_BuildPanel_C:GetBuildListOfProductionEntity"),
			[](auto a, auto b) { /* do nothing*/ },
			std::bind_front(&WSysResearchManager::PostBuildPanelGetBuildListOfProductionEntity, this),
			nullptr);

		functions_hooked = true;
	}
}

namespace
{
	Generator<SimShip> alive_ships(const UC::TArray<SimEntity>& entity_list)
	{
		for (auto& entity : entity_list)
		{
			if (entity.IsValid() && entity.IsShip() && entity.IsAlive())
			{
				co_yield entity.obj;
			}
		}
	}
}

void WSysResearchManager::Tick()
{
	static std::set<StringType> owned_ship_types;
	static std::set<StringType> done_research_list;

	if (!sim_proxy.IsValid() || !EnableTick)
	{
		return;
	}

	auto players = sim_proxy.GetSimPlayers();
	bool build_options_has_update = false;

	for (std::int32_t player_idx = 0; player_idx < players->Num(); player_idx++)
	{
		auto player = (*players)[player_idx];

		auto research_manager = player.GetResearchManager();

		auto research_list = research_manager->GetResearchList();
		auto entity_list = player.GetOwnedSimObjects();
		
		owned_ship_types.clear();
		done_research_list.clear();

		for (auto& ship : alive_ships(*entity_list))
		{
			const auto ship_static_data = *ship.GetDataAsset();
			owned_ship_types.emplace(ship_static_data->GetName());
		}

		for (auto& research : *research_list)
		{
			if (research.State == ResearchState::Done)
			{
				done_research_list.emplace(research.StaticData->GetName());
			}
		}

		UpdateResearchStatus(player_idx, player, *research_list, owned_ship_types, done_research_list);
		build_options_has_update |= UpdateBuildStatus(player, *entity_list, owned_ship_types, done_research_list);
	}

	if (build_options_has_update)
	{
		NotifyBuildListChanged();
	}
}

void WSysResearchManager::PostBuildPanelGetBuildListOfProductionEntity(
	Unreal::UnrealScriptFunctionCallableContext& context, [[maybe_unused]] void* custom_data) const
{
	const auto& production_entity = context.GetParams<SimEntity>();
	auto& frame = context.TheStack;
	const auto outprop_0 = frame.OutParms();
	const auto outprop_1 = frame.OutParms()->NextOutParm;
	auto& manual_build_list = *reinterpret_cast<UC::TArray<ShipStaticData>*>(outprop_0->PropAddr);
	auto& native_build_list = *reinterpret_cast<UC::TArray<ShipStaticData>*>(outprop_1->PropAddr);
	if (!production_entity.IsShip()) { return; }
	for (std::int32_t i = 0; i < manual_build_list.Num(); i++)
	{
		if (CanShipBuild(production_entity.obj, manual_build_list[i]) == BuildConditionCheckResult::NotBuildable)
		{
			manual_build_list.Remove(i);
			i--;
		}
	}
	for (std::int32_t i = 0; i < native_build_list.Num(); i++)
	{
		if (CanShipBuild(production_entity.obj, native_build_list[i]) == BuildConditionCheckResult::NotBuildable)
		{
			native_build_list.Remove(i);
			i--;
		}
	}
}

BuildConditionCheckResult WSysResearchManager::CanShipBuild(SimShip production_ship, ShipStaticData ship_to_build) const
{
	const auto ship_id = *production_ship.GetSimID();
	if (const auto production_ship_cache = build_capability_cache.find(ship_id); production_ship_cache != build_capability_cache.end())
	{
		if (const auto record = production_ship_cache->second.find(ship_to_build->GetName()); record != production_ship_cache->second.end())
		{
			return record->second;
		}
	}
	return BuildConditionCheckResult::DoNotCare;
}

void WSysResearchManager::NotifyResearchChanged(SimPlayer player, const ResearchData& data) const
{
	hud.ResearchChangedEvent(player, data, ResearchEvent::InstaResearchComplete, false);
}

void WSysResearchManager::UpdateResearchStatus(
	std::int32_t player_idx, 
	SimPlayer player, 
	const UC::TArray<ResearchData>& research_list, 
	const std::set<StringType>& owned_ship_types,
	const std::set<StringType>& done_research_list) const
{
	for (auto& research : research_list)
	{
		const auto research_static_data = research.StaticData;

		// name example: Skirmish_F01_Fighter01_Research <-- this is hgn scout
		// name example: Skirmish_F01_Fighter02_Research <-- this is hgn interceptor
		auto name = research_static_data->GetName();
		switch (ConditionController.CheckResearchCondition(
			name,
			owned_ship_types,
			done_research_list))
		{
		case ResearchConditionCheckResult::Unlocked:
		{
			if (research.State == ResearchState::Done)
			{
				break;
			}

			std::ignore = tiir_research_function_library->UnlockResearchForPlayer(player_idx, research_static_data);
			research.State = ResearchState::Done;
			NotifyResearchChanged(player, research);
			break;
		}
		case ResearchConditionCheckResult::Locked:
		{
			if (research.State == ResearchState::Locked)
			{
				break;
			}

			tiir_research_function_library->CancelResearchForPlayer(player_idx, research_static_data);
			research.State = ResearchState::Locked;
			NotifyResearchChanged(player, research);
			break;
		}
		case ResearchConditionCheckResult::DoNotCare:
			break;
		}
	}
}

namespace
{

	std::map<SimShip, std::set<StringType>> find_docked_ships(const UC::TArray<SimEntity>& entity_list)
	{
		std::map<SimShip, std::set<StringType>> docked_ships;
		for (auto& ship : alive_ships(entity_list))
		{
			if (!*ship.GetIsDocked())
			{
				continue;
			}
			const auto dock_with = *ship.GetDockWith();
			if (!docked_ships.contains(dock_with))
			{
				docked_ships[dock_with] = {};
			}
			docked_ships[dock_with].emplace((*ship.GetDataAsset())->GetName());
		}
		return docked_ships;
	}
}

bool WSysResearchManager::UpdateBuildStatus(
	SimPlayer player,
	const UC::TArray<SimEntity>& entity_list,
	const std::set<StringType>& owned_ship_types,
	const std::set<StringType>& done_research_list)
{
	// ship holder -> docked ships
	auto docked_ships = find_docked_ships(entity_list);

	bool build_options_has_update = false;
	for (auto& build_from_ship : alive_ships(entity_list))
	{
		const auto ship_static_data = *build_from_ship.GetDataAsset();
		if (const auto& production_families = *ship_static_data.GetProductionFamilies(); 
			production_families.Num() == 0)
		{
			// not a production ship
			continue;
		}

		const auto build_from_ship_id = *build_from_ship.GetSimID();
		const auto build_from_ship_name = ship_static_data->GetName();
		if (!build_capability_cache.contains(build_from_ship_id))
		{
			build_capability_cache[build_from_ship_id] = {};
		}
		auto& build_capability_cache_this_ship = build_capability_cache[build_from_ship_id];

		for (const auto& managed_build_options = BuildController.GetBuildOptionList(build_from_ship_name); 
			const auto& build_option : managed_build_options)
		{
			auto old_result = BuildConditionCheckResult::DoNotCare;
			if (const auto found = build_capability_cache_this_ship.find(build_option); found != build_capability_cache_this_ship.end())
			{
				old_result = found->second;
			}
			const auto new_result = BuildController.CheckBuildCondition(
				build_from_ship_name,
				build_option,
				owned_ship_types,
				done_research_list,
				docked_ships[build_from_ship]);
			if (new_result != old_result) 
			{
				build_capability_cache_this_ship[build_option] = new_result;
				build_options_has_update = true;
			}

			if (new_result == BuildConditionCheckResult::NotBuildable)
			{
				CancelBuild(player, build_from_ship, database->GetShipData(boost::nowide::narrow(build_option)));
			}
		}
	}

	return build_options_has_update;
}

void WSysResearchManager::NotifyBuildListChanged() const
{
	build_panel.PopulateProductionCategories();
}



void WSysResearchManager::CancelBuild(SimPlayer player, SimShip builder, ShipStaticData ship_to_build) const
{
	const auto production = *builder.GetProductionComponent();
	bool valid;
	const auto build_jobs = production.GetJobTypeState(ship_to_build, valid);
	if (!valid)
	{
		return;
	}

	for(std::int32_t i = build_jobs.Jobs.Num() - 1; i >= 0; i--)
	{
		const auto& job = build_jobs.Jobs[i];
		auto order = sim_order_factory->MakeCancelBuildOrder(player, builder.obj, BuildCancelType::Job, job.ID, nullptr);
		unit_order_component.SendOrder(order);
	}
}
