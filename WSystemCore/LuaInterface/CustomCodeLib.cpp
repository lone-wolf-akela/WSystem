#include <pch.h>

#include <DataWrapper/SimShip.h>
#include "CustomCodeLib.h"

void CustomCodeDef::CallCreate(std::uint64_t entity_id) const
{
	if(!OnCreate)
	{
		return;
	}
	if (const auto result = OnCreate.value()(entity_id); !result.valid())
	{
		const sol::error err = result;
		RC::Output::send<RC::LogLevel::Error>(
			STR("CustomCode OnCreate function failed: {}\n"),
			boost::nowide::widen(err.what()));
	}
}

void CustomCodeDef::CallUpdate(std::uint64_t entity_id) const
{
	if (!OnUpdate)
	{
		return;
	}
	if (const auto result = OnUpdate.value()(entity_id); !result.valid())
	{
		const sol::error err = result;
		RC::Output::send<RC::LogLevel::Error>(
			STR("CustomCode OnUpdate function failed: {}\n"),
			boost::nowide::widen(err.what()));
	}
}

void CustomCodeDef::CallDestroy(std::uint64_t entity_id) const
{
	if (!OnDestroy)
	{
		return;
	}
	if (const auto result = OnDestroy.value()(entity_id); !result.valid())
	{
		const sol::error err = result;
		RC::Output::send<RC::LogLevel::Error>(
			STR("CustomCode OnDestroy function failed: {}\n"),
			boost::nowide::widen(err.what()));
	}
}

void CustomCodeRecord::CallCreate() const
{
	Def->CallCreate(EntityID);
}

void CustomCodeRecord::CallUpdate() const
{
	Def->CallUpdate(EntityID);
}

void CustomCodeRecord::CallDestroy() const
{
	Def->CallDestroy(EntityID);
}

void CustomCodeManager::Register(
	std::string_view unit_type, 
	std::string_view on_create, 
	std::string_view on_update,
	std::string_view on_destroy, 
	std::int64_t update_interval)
{
	CustomCodeDef def
	{
		.UnitTypeName = std::string(unit_type),
		.UpdateTickInterval = update_interval
	};

	if (!on_create.empty())
	{
		def.OnCreate = (*lua)[on_create];
		if (!def.OnCreate.value().valid())
		{
			const auto err_msg = std::format("Lua function not found: {}\n", on_update);
			throw std::runtime_error(err_msg);
		}
	}

	if (!on_update.empty())
	{
		def.OnUpdate = (*lua)[on_update];
		if (!def.OnUpdate.value().valid())
		{
			const auto err_msg = std::format("Lua function not found: {}\n", on_update);
			throw std::runtime_error(err_msg);
		}
	}

	if (!on_destroy.empty())
	{
		def.OnDestroy = (*lua)[on_destroy];
		if (!def.OnDestroy.value().valid())
		{
			const auto err_msg = std::format("Lua function not found: {}\n", on_update);
			throw std::runtime_error(err_msg);
		}
	}

	auto ship_data = database->GetShipData(unit_type);

	custom_code_defs.emplace(ship_data, def);
}

void CustomCodeManager::Begin_InGame(RavenSimulationProxy sim_proxy)
{
	current_tick = 0;
	alive_units.clear();
	custom_code_records.clear();
	this->sim_proxy = sim_proxy;
}

void CustomCodeManager::Tick()
{
	static std::set<std::uint64_t> new_alive_units;
	static std::map<std::uint64_t, SimShip> id_to_ship_map;
	static std::vector<std::uint64_t> newly_born_units;
	static std::vector<std::uint64_t> newly_dead_units;

	new_alive_units.clear();
	id_to_ship_map.clear();
	newly_born_units.clear();
	newly_dead_units.clear();
		
	current_tick++;

	auto players = sim_proxy.GetSimPlayers();
	for (auto& player : *players)
	{
		for (auto& entity : *player.GetOwnedSimObjects())
		{
			if (entity.IsShip() && entity.IsAlive())
			{
				const auto entity_id = static_cast<std::uint64_t>(*entity.GetSimID());
				const SimShip ship = entity.obj;
				new_alive_units.emplace(entity_id);
				id_to_ship_map.emplace(entity_id, ship);
			}
		}
	}

	std::ranges::set_difference(new_alive_units, alive_units, std::back_inserter(newly_born_units));
	std::ranges::set_difference(alive_units, new_alive_units, std::back_inserter(newly_dead_units));

	for (auto& id : newly_born_units)
	{
		const auto ship = id_to_ship_map.at(id);
		const auto static_data = *ship.GetDataAsset();
		if (auto it = custom_code_defs.find(static_data); it != custom_code_defs.end())
		{
			auto& def = it->second;

			CustomCodeRecord record
			{
				.EntityID = id,
				.Def = &def,
				.NextUpdateTick = current_tick + def.UpdateTickInterval
			};
			custom_code_records.emplace(id, record);
			record.CallCreate();
		}
	}

	for (auto& ship : newly_dead_units)
	{
		if (auto it = custom_code_records.find(ship); it != custom_code_records.end())
		{
			auto& record = it->second;
			record.CallDestroy();
			custom_code_records.erase(it);
		}
	}

	alive_units = std::move(new_alive_units);

	for (auto& record : custom_code_records | std::views::values)
	{
		if (record.NextUpdateTick <= current_tick)
		{
			record.CallUpdate();
			record.NextUpdateTick += record.Def->UpdateTickInterval;
		}
	}
}

void CustomCodeManager::Initialize(
	sol::state_view* lua, 
	Database* database)
{
	this->lua = lua;
	this->database = database;

	auto custom_code_manager_t = lua->new_usertype<CustomCodeManager>(
		"CustomCodeManagerType",
		// functions
		"Register", &CustomCodeManager::Register
	);
}
