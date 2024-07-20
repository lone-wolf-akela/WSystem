#include <pch.h>

#include <Core/WSystemCore.h>

#include "LuaInterface.h"

namespace
{
	template <typename EnumType>
	void SolRegisterEnum(sol::state_view* lua, std::string_view name)
	{
		using index_seq = std::make_index_sequence<magic_enum::enum_count<EnumType>()>;
		SolRegisterEnumImpl<EnumType>(lua, name, index_seq{});
	}

	template <typename EnumType, std::size_t I>
	auto SolRegisterMakePair()
	{
		return std::make_pair(magic_enum::enum_name<EnumType>(static_cast<EnumType>(I)), static_cast<EnumType>(I));
	}

	template <typename EnumType, std::size_t... I>
	void SolRegisterEnumImpl(sol::state_view* lua, std::string_view name, std::index_sequence<I...>)
	{
		lua->new_enum(name, { SolRegisterMakePair<EnumType, I>()... });
	}
}

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
		&this->wsystem_core->database
	);
	entity_lib_interface.BindLuaState(
		&lua_state, 
		&this->wsystem_core->function_libs.Entity,
		&sobgroup_manager,
		&this->wsystem_core->database,
		this
	);
	player_lib_interface.BindLuaState(
		&lua_state, 
		&this->wsystem_core->function_libs.Player,
		&sobgroup_manager
	);

	auto wsys_t = lua_state.new_usertype<LuaInterface>(
		// ctor
		"WSysType",
		// functions
		"AddResearchCondition", &LuaInterface::AddResearchCondition,
		// members
		"Rule", sol::readonly(&LuaInterface::rule_manager),
		"SobGroup", sol::readonly(&LuaInterface::sobgroup_manager),
		"CustomCode", sol::readonly(&LuaInterface::custom_code_manager),
		"Entity", sol::readonly(&LuaInterface::entity_lib_interface),
		"Player", sol::readonly(&LuaInterface::player_lib_interface)
	); 

	SolRegisterEnum<SquadronTactics>(&lua_state, "SquadronTactics");
	SolRegisterEnum<SquadronStance>(&lua_state, "SquadronStance");
	SolRegisterEnum<AutoLaunchSetting>(&lua_state, "AutoLaunchSetting");
	SolRegisterEnum<RetaliationSetting>(&lua_state, "RetaliationSetting");
	SolRegisterEnum<SobPropertyType>(&lua_state, "SobPropertyType");
	SolRegisterEnum<MultiplierType>(&lua_state, "MultiplierType");
	SolRegisterEnum<AbilityType>(&lua_state, "AbilityType");
	SolRegisterEnum<InfluenceType>(&lua_state, "InfluenceType");
	SolRegisterEnum<ActivityRelation>(&lua_state, "ActivityRelation");
	SolRegisterEnum<ParadeMode>(&lua_state, "ParadeMode");

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

void LuaInterface::Rule_OnInit(RavenSimulationProxy sim_proxy)
{
	RC::Output::send<LogLevel::Verbose>(STR("Finding Rule_OnInit()...\n"));

	id_to_entity_map.clear();
	rule_manager.ResetTickTimer();
	custom_code_manager.ResetTickTimer(sim_proxy);

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
	id_to_entity_map.clear();
	rule_manager.Tick();
	custom_code_manager.Tick();
}


SimEntity LuaInterface::FindEntity(std::uint64_t entity_id)
{
	if (id_to_entity_map.empty())
	{
		std::vector<Unreal::UObject*> entities;
		Unreal::UObjectGlobals::FindAllOf(STR("SimEntity"), entities);
		for (auto entity : entities)
		{
			SimEntity sim_entity = entity;
			const auto id = static_cast<std::uint64_t>(*sim_entity.GetSimID());
			id_to_entity_map.emplace(id, sim_entity);
		}
	}
	if (const auto found = id_to_entity_map.find(entity_id); found != id_to_entity_map.end())
	{
		return found->second;
	}
	return nullptr;
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

