#pragma once
#include <pch.h>

#include "RuleLib.h"
#include "SobGroupLib.h"
#include "CustomCodeLib.h"
#include "EntityLib.h"
#include "PlayerLib.h"

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
	void LoadRegistration() const;
	void Rule_OnInit(RavenSimulationProxy sim_proxy);
	void Rule_Tick();
	bool EnableTick = false;

	SimEntity FindEntity(std::uint64_t entity_id);
public:
	void AddResearchCondition(
		std::string_view target_research, 
		std::string_view all_of_units, 
		std::string_view none_of_units,
		std::string_view all_of_researches,
		std::string_view none_of_researches) const;
private:
	WSystemCore* wsystem_core;
	ScriptRuleManager rule_manager;
	SobGroupManager sobgroup_manager;
	CustomCodeManager custom_code_manager;
	EntityLibInterface entity_lib_interface;
	PlayerLibInterface player_lib_interface;

	std::map<std::uint64_t, SimEntity> id_to_entity_map;
};