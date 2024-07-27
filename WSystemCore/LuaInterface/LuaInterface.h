#pragma once
#include <pch.h>

#include "RuleLib.h"
#include "SobGroupLib.h"
#include "CustomCodeLib.h"
#include "EntityLib.h"
#include "PlayerLib.h"
#include "UniverseLib.h"
#include "EntityIdManager.h"

class WSystemCore;

class LuaInterface : public std::enable_shared_from_this<LuaInterface>
{
public:
	explicit LuaInterface(WSystemCore* wsystem_core);

	LuaInterface(const LuaInterface& o) = delete;
	LuaInterface& operator=(const LuaInterface& o) = delete;
	LuaInterface(LuaInterface&& o) noexcept = default;
	LuaInterface& operator=(LuaInterface&& o) noexcept = default;
	~LuaInterface() = default;

	void Initialize();
	void Begin_InitScenario();
	void Begin_InGame();
	void Tick();
	bool EnableTick = false;

public:
	void AddResearchCondition(
		std::string_view target_research, 
		std::string_view all_of_units, 
		std::string_view none_of_units,
		std::string_view all_of_researches,
		std::string_view none_of_researches) const;
	void AddBuildCondition(
		std::string_view ship_to_build,
		std::string_view build_from_ships,	// cannot be empty
		std::string_view all_of_units_fleetwise,
		std::string_view none_of_units_fleetwise,
		std::string_view all_of_units_this_ship,
		std::string_view none_of_units_this_ship,
		std::string_view all_of_researches,
		std::string_view none_of_researches) const;
private:
	WSystemCore* wsystem_core;
	ScriptRuleManager rule_manager;
	SobGroupManager sobgroup_manager;
	CustomCodeManager custom_code_manager;
	EntityIdManager entity_id_manager;
	EntityLibInterface entity_lib_interface;
	PlayerLibInterface player_lib_interface;
	UniverseLib universe_lib;
};