#pragma once
#include <cstdint>
#include <string>
#include <string_view>
#include <map>
#include <set>
#include <optional>

#include <sol/sol.hpp>
#undef check

#include <Core/Database.h>
#include <DataWrapper/ShipStaticData.h>
#include <DataWrapper/SimShip.h>
#include <DataWrapper/RavenSimulationProxy.h>

#include "SobGroupLib.h"

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
	void ResetTickTimer(RavenSimulationProxy sim_proxy);
	void Tick();
	void BindLuaState(
		sol::state_view* lua, 
		Database* database);
private:
	sol::state_view* lua = nullptr;
	Database* database = nullptr;
	RavenSimulationProxy sim_proxy = nullptr;
	std::int64_t current_tick = 0;

	std::map<ShipStaticData, CustomCodeDef> custom_code_defs;
	std::map<SimShip, CustomCodeRecord> custom_code_records;

	std::set<SimShip> alive_units;
};