#include <ThirdParty/UnrealContainers/UnrealContainers.h>

#include <DataWrapper/SimPlayer.h>
#include <DataWrapper/ResearchStaticData.h>
#include <DataWrapper/SimEntity.h>
#include <DataWrapper/SimShip.h>

#include "ResearchManager.h"

#include "Property/FMulticastDelegateProperty.hpp"

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

WSysResearchManager::WSysResearchManager(TiirResearchFunctionLibrary* tiir_research_function_library) : 
	tiir_research_function_library(tiir_research_function_library)
{
	/*ConditionController.ResearchConditions[STR("Skirmish_F01_Fighter02_Research")] = {};
	ConditionController.ResearchConditions[STR("Skirmish_F01_Fighter02_Research")]
		.RequiredAnyOf.emplace_back();
	ConditionController.ResearchConditions[STR("Skirmish_F01_Fighter02_Research")]
		.RequiredAnyOf.back().RequiredAllOf.Researches.emplace_back(STR("SA_F01_Fighter01"));*/
}

void WSysResearchManager::Bind(RavenSimulationProxy sim_proxy, RavenHUD hud)
{
	this->sim_proxy = sim_proxy;
	this->hud = hud;
}


void WSysResearchManager::Tick() const
{
	static std::set<RC::StringType> owned_ship_types;
	static std::set<RC::StringType> done_research_list;

	if (!sim_proxy.IsValid() || !EnableTick)
	{
		return;
	}

	auto players = sim_proxy.GetSimPlayers();

	for (int player_idx = 0; player_idx < players->Num(); player_idx++)
	{
		auto player = (*players)[player_idx];

		auto research_manager = player.GetResearchManager();

		auto research_list = research_manager->GetResearchList();
		auto entity_list = player.GetOwnedSimObjects();
		
		owned_ship_types.clear();
		done_research_list.clear();

		for (auto& entity : *entity_list)
		{
			if(!entity.IsShip() || !entity.IsAlive())
			{
				continue;
			}
			const SimShip ship = entity.obj;
			const auto ship_static_data = *ship.GetDataAsset();

			// name example: SA_F01_Fighter01 <-- this is hgn scout
			// name example: SA_F01_Probe <-- this is hgn probe
			owned_ship_types.emplace(ship_static_data->GetName());
		}

		for (auto& research : *research_list)
		{
			if (research.State == ResearchState::Done)
			{
				done_research_list.emplace(research.StaticData->GetName());
			}
		}

		for (auto& research : *research_list)
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
				RC::Output::send<RC::LogLevel::Verbose>(STR("[Player {}] Unlock Research: {}\n"), player_idx, name);
				break;
			}
			case ResearchConditionCheckResult::Locked:
			{
				if (research.State == ResearchState::Locked)
				{
					break;
				}

				research.State = ResearchState::Locked;
				NotifyResearchChanged(player, research);
				RC::Output::send<RC::LogLevel::Verbose>(STR("[Player {}] Lock Research: {}\n"), player_idx, name);
				break;
			}
			case ResearchConditionCheckResult::DoNotCare:
				break;
			}
		}
	}
}

void WSysResearchManager::NotifyResearchChanged(SimPlayer player, ResearchData data) const
{
	hud.ResearchChangedEvent(player, data, ResearchEvent::InstaResearchComplete, false);
}
