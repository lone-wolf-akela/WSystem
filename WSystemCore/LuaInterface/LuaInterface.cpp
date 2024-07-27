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
	set_default_state(lua_state);

	rule_manager.Initialize(&lua_state);
	sobgroup_manager.Initialize(
		&lua_state, 
		&this->wsystem_core->function_libs.EntityGroup,
		&this->wsystem_core->database,
		&this->entity_id_manager,
		&this->entity_lib_interface
	);
	custom_code_manager.Initialize(
		&lua_state,
		&this->entity_id_manager
	);
	entity_lib_interface.Initialize(
		&lua_state, 
		&this->wsystem_core->function_libs.Entity,
		&this->sobgroup_manager,
		&this->wsystem_core->database,
		&this->entity_id_manager
	);
	player_lib_interface.Initialize(
		&lua_state,
		&this->wsystem_core->function_libs.Player,
		&this->sobgroup_manager
	);
	universe_lib.Initialize(&lua_state);

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
		"Player", sol::readonly(&LuaInterface::player_lib_interface),
		"Universe", sol::readonly(&LuaInterface::universe_lib)
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
	SolRegisterEnum<TurretDeploymentState>(&lua_state, "TurretDeploymentState");
	SolRegisterEnum<DockingStage>(&lua_state, "DockingStage");
	SolRegisterEnum<HyperspaceStatus>(&lua_state, "HyperspaceStatus");
	SolRegisterEnum<SobAnimationState>(&lua_state, "SobAnimationState");
	SolRegisterEnum<UCommandType>(&lua_state, "UCommandType");

	lua_state["WSys"] = shared_from_this();
}

void LuaInterface::Begin_InitScenario()
{
	entity_lib_interface.Begin_InitScenario(this->wsystem_core->units_info_subsystem);
	sobgroup_manager.Begin_InitScenario(this->wsystem_core->units_info_subsystem);
	
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

void LuaInterface::Begin_InGame()
{
	entity_id_manager.Begin_InGame(this->wsystem_core->raven_simulation_proxy);

	rule_manager.Begin_InGame(this->wsystem_core->raven_simulation_proxy);
	custom_code_manager.Begin_InGame(this->wsystem_core->raven_simulation_proxy);
	universe_lib.Begin_InGame(this->wsystem_core->raven_simulation_proxy);
	sobgroup_manager.Begin_InGame(this->wsystem_core->raven_simulation_proxy);
	player_lib_interface.Begin_InGame(this->wsystem_core->raven_simulation_proxy);

	auto& lua_state = *this->wsystem_core->lua;
	RC::Output::send<LogLevel::Verbose>(STR("Finding Rule_OnInit()...\n"));
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

void LuaInterface::Tick()
{
	if (!EnableTick)
	{
		return;
	}
	entity_id_manager.Tick();

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

