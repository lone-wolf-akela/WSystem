#pragma once
#include <pch.h>

#include <Core/Database.h>
#include <DataWrapper/RavenSimulationProxy.h>

#include "EntityIdManager.h"

struct CustomCodeDef
{
	std::string UnitTypeName;
	std::int64_t UpdateTickInterval;

	std::optional<sol::protected_function> OnCreate;
	std::optional<sol::protected_function> OnUpdate;
	std::optional<sol::protected_function> OnDestroy;

	void CallCreate(std::uint64_t entity_id) const;
	void CallUpdate(std::uint64_t entity_id) const;
	void CallDestroy(std::uint64_t entity_id) const;
};

struct CustomCodeRecord
{
	std::uint64_t EntityID;
	CustomCodeDef* Def;

	std::int64_t NextUpdateTick;

	void CallCreate() const;
	void CallUpdate() const;
	void CallDestroy() const;
};

class CustomCodeManager
{
public:
	void Register(std::string_view unit_type, std::string_view on_create, std::string_view on_update, std::string_view on_destroy, std::int64_t update_interval);
	
	void Begin_InGame(RavenSimulationProxy sim_proxy);
	void Tick();
	void Initialize(sol::state_view* lua, EntityIdManager* entity_id_manager);
private:
	sol::state_view* lua = nullptr;
	Database* database = nullptr;
	RavenSimulationProxy sim_proxy = nullptr;
	EntityIdManager* entity_id_manager = nullptr;

	std::map<std::string, CustomCodeDef> custom_code_defs;
	std::map<std::uint64_t, CustomCodeRecord> custom_code_records;
};