#pragma once
#include <memory>
#include <string>
#include <string_view>

#include "RuleLib.h"

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
	void ScanForResearchConditions() const;
	void Rule_OnInit();
	void Rule_Tick();

	// interface part
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
};