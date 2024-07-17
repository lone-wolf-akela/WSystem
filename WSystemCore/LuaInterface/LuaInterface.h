#pragma once
#include <memory>
#include <string>
#include <string_view>

#include "RuleLib.h"
#include "SobGroupLib.h"
#include "CustomCodeLib.h"

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
};