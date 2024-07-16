#include <boost/algorithm/string.hpp>

#include <boost/nowide/convert.hpp>
#include <sol/sol.hpp>

#include <Core/WSystemCore.h>

#include "LuaInterface.h"

LuaInterface::LuaInterface(WSystemCore* wsystem_core) : 
	wsystem_core(wsystem_core)
{
}

void LuaInterface::Initialize()
{
	auto& lua_state = *this->wsystem_core->lua;
	rule_manager.BindLuaState(&lua_state);
	sobgroup_manager.BindLuaState(
		&lua_state, 
		&this->wsystem_core->function_libs.EntityGroup,
		&this->wsystem_core->database
	);
	custom_code_manager.BindLuaState(
		&lua_state, 
		&this->wsystem_core->database, 
		this->wsystem_core->raven_simulation_proxy
	);

	auto wsys_t = lua_state.new_usertype<LuaInterface>(
		// ctor
		"WSysType",
		// functions
		"AddResearchCondition", &LuaInterface::AddResearchCondition,
		// members
		"Rule", sol::readonly(&LuaInterface::rule_manager),
		"SobGroup", sol::readonly(&LuaInterface::sobgroup_manager),
		"CustomCode", sol::readonly(&LuaInterface::custom_code_manager)
	); 

	lua_state["WSys"] = shared_from_this();
}

void LuaInterface::LoadRegistration() const
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

	RC::Output::send<LogLevel::Verbose>(STR("Loading CustomCode Registration...\n"));

	if (const sol::protected_function scan = lua_state["WSys_RegisterCustomCode"]; scan.valid())
	{
		if (const auto result = scan(); !result.valid())
		{
			const sol::error err = result;
			RC::Output::send<LogLevel::Error>(STR("Error in WSys_RegisterCustomCode(): {}\n"), boost::nowide::widen(err.what()));
		}
	}
	else
	{
		RC::Output::send<LogLevel::Verbose>(STR("WSys_RegisterCustomCode() not found in Lua\n"));
	}
}

void LuaInterface::Rule_OnInit()
{
	RC::Output::send<LogLevel::Verbose>(STR("Finding Rule_OnInit()...\n"));

	rule_manager.ResetTickTimer();
	custom_code_manager.ResetTickTimer();

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

void LuaInterface::Rule_Tick()
{
	if (!EnableTick)
	{
		return;
	}
	rule_manager.Tick();
	custom_code_manager.Tick();
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

