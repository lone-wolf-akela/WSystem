#include <pch.h>

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

	custom_code_defs.emplace(unit_type, def);
}

void CustomCodeManager::Begin_InGame(RavenSimulationProxy sim_proxy)
{
	custom_code_records.clear();
	this->sim_proxy = sim_proxy;
}

void CustomCodeManager::Tick()
{
	const auto& newly_born_units = entity_id_manager->GetNewlyBornEntity();
	const auto& newly_dead_units = entity_id_manager->GetNewlyDeadEntity();
	const auto current_tick = sim_proxy.SimulatingFrame;

	for (auto& id : newly_born_units)
	{
		const auto entity = entity_id_manager->FindEntity(id);
		const auto entity_name = entity.GetDataAssetNameNarrow();
		if (auto it = custom_code_defs.find(entity_name); it != custom_code_defs.end())
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

	for (auto& record : custom_code_records | std::views::values)
	{
		if (record.NextUpdateTick <= current_tick)
		{
			record.CallUpdate();
			record.NextUpdateTick += record.Def->UpdateTickInterval;
		}
	}
}

void CustomCodeManager::Initialize(sol::state_view* lua, EntityIdManager* entity_id_manager)
{
	this->lua = lua;
	this->entity_id_manager = entity_id_manager;

	auto custom_code_manager_t = lua->new_usertype<CustomCodeManager>(
		"CustomCodeManagerType",
		// functions
		"Register", &CustomCodeManager::Register
	);
}
