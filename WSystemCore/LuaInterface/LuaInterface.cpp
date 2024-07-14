#include <boost/algorithm/string.hpp>

#include <boost/nowide/convert.hpp>
#include <sol/sol.hpp>

#include <Core/WSystemCore.h>

#include "LuaInterface.h"

LuaInterface::LuaInterface(WSystemCore* wsystem_core)
{
	this->wsystem_core = wsystem_core;
}

LuaInterface::LuaInterface(const LuaInterface& o): wsystem_core(o.wsystem_core)
{
}

LuaInterface& LuaInterface::operator=(const LuaInterface& o)
{
	wsystem_core= o.wsystem_core;
	return *this;
}

LuaInterface::LuaInterface(LuaInterface&& o) noexcept
{
	wsystem_core = o.wsystem_core;
	o.wsystem_core = nullptr;
}

LuaInterface& LuaInterface::operator=(LuaInterface&& o) noexcept
{
	wsystem_core = o.wsystem_core;
	o.wsystem_core = nullptr;
	return *this;
}

void LuaInterface::Initialize()
{
	auto& lua_state = *this->wsystem_core->lua;
	sol::usertype<LuaInterface> wsys_t = lua_state.new_usertype<LuaInterface>(
		"WSysType",
		sol::constructors<LuaInterface(WSystemCore*)>()
	); 

	wsys_t["AddResearchCondition"] = &LuaInterface::AddResearchCondition;
	
	wsys_t["Rule_Add"] = &LuaInterface::AddRule;
	wsys_t["Rule_AddInterval"] = &LuaInterface::AddRuleInterval;
	wsys_t["Rule_AddIntervalOneTime"] = &LuaInterface::AddRuleIntervalOneTime;
	wsys_t["Rule_Remove"] = &LuaInterface::RemoveRule;
	wsys_t["Rule_Exists"] = &LuaInterface::IsRuleExists;

	lua_state["WSys"] = *this;
}

void LuaInterface::ScanForResearchConditions() const
{
	RC::Output::send<LogLevel::Verbose>(STR("Loading Research Conditions...\n"));

	auto& research_manager = this->wsystem_core->research_manager;
	research_manager.ConditionController.ResearchConditions.clear();

	auto& lua_state = *this->wsystem_core->lua;
	if (const sol::protected_function scan = lua_state["WSys_SetupResearchConditions"]; scan.valid())
	{
		if (const auto result = scan(); !result.valid())
		{
			const sol::error err = result;
			RC::Output::send<LogLevel::Error>(STR("Error in WSys_SetupResearchConditions(): {}\n"), boost::nowide::widen(err.what()));
		}
	}
	else
	{
		RC::Output::send<LogLevel::Verbose>(STR("WSys_SetupResearchConditions() not found in Lua\n"));
	}
}

void LuaInterface::Rule_OnInit() const
{
	RC::Output::send<LogLevel::Verbose>(STR("Finding Rule_OnInit()...\n"));

	auto& lua_state = *this->wsystem_core->lua;
	if (const sol::protected_function init_func = lua_state["Rule_OnInit"]; init_func.valid())
	{
		if (const auto result = init_func(); !result.valid())
		{
			const sol::error err = result;
			RC::Output::send<LogLevel::Error>(STR("Error in Rule_OnInit(): {}\n"), boost::nowide::widen(err.what()));
		}
	}
	else
	{
		RC::Output::send<LogLevel::Verbose>(STR("Rule_OnInit() not found in Lua\n"));
	}
}

void LuaInterface::AddResearchCondition(
	std::string_view target_research,
	std::string_view all_of_units,
	std::string_view none_of_units,
	std::string_view all_of_researches,
	std::string_view none_of_researches) const
{
	RC::Output::send<LogLevel::Verbose>(
		STR("Registering research conditions for {}\n"), 
		boost::nowide::widen(target_research));
	auto& research_manager = this->wsystem_core->research_manager;
	
	std::vector<std::string> all_of_units_list;
	std::vector<std::string> none_of_units_list;
	std::vector<std::string> all_of_researches_list;
	std::vector<std::string> none_of_researches_list;

	split(all_of_units_list, all_of_units, boost::is_any_of(","));
	split(none_of_units_list, none_of_units, boost::is_any_of(","));
	split(all_of_researches_list, all_of_researches, boost::is_any_of(","));
	split(none_of_researches_list, none_of_researches, boost::is_any_of(","));

	const auto wide_research_name = boost::nowide::widen(target_research);

	if (!research_manager.ConditionController.ResearchConditions.contains(wide_research_name))
	{
		research_manager.ConditionController.ResearchConditions[wide_research_name] = {};
	}

	auto& group = research_manager.ConditionController.ResearchConditions[wide_research_name];

	ResearchCondition condition;

	for (auto& line : all_of_units_list)
	{
		boost::trim(line);
		if (!line.empty())
		{
			condition.RequiredAllOfUnits.push_back(boost::nowide::widen(line));
		}
	}

	for (auto& line : none_of_units_list)
	{
		boost::trim(line);
		if (!line.empty())
		{
			condition.RequiredNoneOfUnits.push_back(boost::nowide::widen(line));
		}
	}
	
	for (auto& line : all_of_researches_list)
	{
		boost::trim(line);
		if (!line.empty())
		{
			condition.RequiredAllOfResearches.push_back(boost::nowide::widen(line));
		}
	}

	for (auto& line : none_of_researches_list)
	{
		boost::trim(line);
		if (!line.empty())
		{
			condition.RequiredNoneOfResearches.push_back(boost::nowide::widen(line));
		}
	}

	group.RequiredAnyOf.push_back(std::move(condition));
}

void LuaInterface::AddRule(std::string_view name) const
{
	auto& rule_manager = this->wsystem_core->rule_manager;
	rule_manager.AddRule(name);
}

void LuaInterface::AddRuleInterval(std::string_view name, std::int64_t interval) const
{
	auto& rule_manager = this->wsystem_core->rule_manager;
	rule_manager.AddRuleInterval(name, interval);
}

void LuaInterface::AddRuleIntervalOneTime(std::string_view name, std::int64_t interval) const
{
	auto& rule_manager = this->wsystem_core->rule_manager;
	rule_manager.AddRuleIntervalOneTime(name, interval);
}

void LuaInterface::RemoveRule(std::string_view name) const
{
	auto& rule_manager = this->wsystem_core->rule_manager;
	rule_manager.RemoveRule(name);
}

bool LuaInterface::IsRuleExists(std::string_view name) const
{
	auto& rule_manager = this->wsystem_core->rule_manager;
	return rule_manager.IsRuleExists(name);
}
