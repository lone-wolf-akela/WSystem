#include <pch.h>

#include <ThirdParty/UnrealContainers/UnrealContainers.h>
#include <DataWrapper/SimPlayer.h>

#include "WSystemCore.h"

WSystemCore::WSystemCore() : 
	research_manager(&this->function_libs.Research),
	lua_interface(std::make_shared<LuaInterface>(this))
{
	ModName = STR("WSystem");
	ModVersion = STR("0.0.3");
	ModDescription = STR("A Lua scripting system for Homeworld 3.");
	ModAuthors = STR("Lone Wolf Akela");
	// Do not change this unless you want to target a UE4SS version
	// other than the one you're currently building with somehow.
	//ModIntendedSDKVersion = STR("2.6");

	RC::Output::send<LogLevel::Verbose>(STR("WSystem mod loaded!\n"));
}

void WSystemCore::On_GameModeInit([[maybe_unused]] Unreal::AGameModeBase* gamemode)
{
	if(first_game_mode_init)
	{
		OnFirst_GameModeInit();
	}

	RC::Output::send<LogLevel::Verbose>(STR("Game mode initialized\n"));
	raven_game_mode = Unreal::UObjectGlobals::FindFirstOf(STR("RavenGameMode_C"));
	if (raven_game_mode.IsValid())
	{
		RC::Output::send<LogLevel::Verbose>(STR("Got RavenGameMode_C\n"));
	}
	else
	{
		RC::Output::send<LogLevel::Verbose>(STR("No RavenGameMode_C\n"));
	}
}

void WSystemCore::OnFirst_GameModeInit()
{
	if (!first_game_mode_init)
	{
		return;
	}

	RC::Output::send<LogLevel::Verbose>(STR("on_first_game_mode_init\n"));

	Unreal::UObjectGlobals::RegisterHook(
		STR("/Game/Assets/Gameplay/RavenGameMode.RavenGameMode_C:Tick In Game State"),
		std::bind_front(&WSystemCore::Pre_InGameTick, this),
		std::bind_front(&WSystemCore::Post_InGameTick, this),
		nullptr);
	Unreal::UObjectGlobals::RegisterHook(
		STR("/Game/Assets/Gameplay/BP_MultiplayerRavenGameMode.BP_MultiplayerRavenGameMode_C:Tick In Game State"),
		std::bind_front(&WSystemCore::Pre_InGameTick, this),
		std::bind_front(&WSystemCore::Post_InGameTick, this),
		nullptr);
	Unreal::UObjectGlobals::RegisterHook(
		STR("/Game/Assets/Audio/RavenAudioSubsystem.RavenAudioSubsystem_C:OnGameModeStateTransition"),
		std::bind_front(&WSystemCore::Pre_GameModeStateTransition, this),
		std::bind_front(&WSystemCore::Post_GameModeStateTransition, this),
		nullptr);

	database.ScanData();

	first_game_mode_init = false;
}

void WSystemCore::Pre_InGameTick(
	[[maybe_unused]] Unreal::UnrealScriptFunctionCallableContext& context,
	[[maybe_unused]] void* custom_data)
{
}

void WSystemCore::Post_InGameTick(
	[[maybe_unused]] Unreal::UnrealScriptFunctionCallableContext& context,
	[[maybe_unused]] void* custom_data)
{
}

void WSystemCore::Pre_GameModeStateTransition(
	[[maybe_unused]] Unreal::UnrealScriptFunctionCallableContext& context,
	[[maybe_unused]] void* custom_data) 
{
}

void WSystemCore::Post_GameModeStateTransition(
	[[maybe_unused]] Unreal::UnrealScriptFunctionCallableContext& context,
	[[maybe_unused]] void* custom_data)
{
	const auto p_state = raven_game_mode.GetLobbyState();
	const auto state = p_state ? *p_state : LobbyState::Invalid;
	RC::Output::send<LogLevel::Verbose>(
		STR("post_game_mode_state_transition: {} -> {}\n"), 
		boost::nowide::widen(magic_enum::enum_name(last_lobby_state)),
		boost::nowide::widen(magic_enum::enum_name(state)));
	last_lobby_state = state;

	if (!raven_game_mode.IsValid() || raven_game_mode.IsLobbyRavenGameMode())
	{
		return;
	}

	if (state == LobbyState::InitScenario)
	{
		Begin_InitScenario();
	}
	else if (state == LobbyState::InGame)
	{
		Begin_InGame();
	}
}

void WSystemCore::Pre_TiirTick(
	[[maybe_unused]] Unreal::UnrealScriptFunctionCallableContext& context, 
	[[maybe_unused]] void* custom_data)
{
}

void WSystemCore::Post_TiirTick(
	[[maybe_unused]] Unreal::UnrealScriptFunctionCallableContext& context, 
	[[maybe_unused]] void* custom_data)
{
	research_manager.Tick();
	lua_interface->Tick();
}

void WSystemCore::Begin_InitScenario()
{
	RC::Output::send<LogLevel::Verbose>(STR("on_init_scenario_begin\n"));

	research_manager.EnableTick = false;
	lua_interface->EnableTick = false;

	std::vector<Unreal::UObject*> actors;
	Unreal::UObjectGlobals::FindAllOf(STR("RTSLevelScriptActor"), actors);

	RC::Output::send<LogLevel::Verbose>(STR("It's normal to see \"Failed to find function `TiirTick`\" error below. Don't panic.\n"));

	Unreal::UFunction* tiir_tick = nullptr;
	for (const auto& actor : actors)
	{
		rts_level_script_actor = actor;
		if (rts_level_script_actor.IsValid())
		{
			tiir_tick = rts_level_script_actor.GetFuncTiirTick();
			if (tiir_tick)
			{
				break;
			}
		}
	}
	if (!tiir_tick)
	{
		RC::Output::send<LogLevel::Error>(STR("All attempts to find tiir_tick func has failed.\n"));
		throw std::runtime_error("All attempts to find tiir_tick func has failed.");
	}
	Unreal::UObjectGlobals::RegisterHook(
		tiir_tick,
		std::bind_front(&WSystemCore::Pre_TiirTick, this),
		std::bind_front(&WSystemCore::Post_TiirTick, this),
		nullptr);

	units_info_subsystem = Unreal::UObjectGlobals::FindFirstOf(STR("UnitsInfoSubsystem"));
	if (!units_info_subsystem.IsValid())
	{
		RC::Output::send<LogLevel::Error>(STR("UnitsInfoSubsystem not found!\n"));
	}

	lua_interface->Begin_InitScenario();
}

void WSystemCore::Begin_InGame()
{
	raven_simulation_proxy = Unreal::UObjectGlobals::FindFirstOf(STR("RavenSimulationProxy_C"));
	if (!raven_simulation_proxy.IsValid())
	{
		RC::Output::send<LogLevel::Error>(STR("No RavenSimulationProxy_C\n"));
		return;
	}
	raven_hud = Unreal::UObjectGlobals::FindFirstOf(STR("RavenHUD_C"));
	if (!raven_hud.IsValid())
	{
		RC::Output::send<LogLevel::Error>(STR("No RavenHUD_C\n"));
		return;
	}

	research_manager.Begin_InGame(raven_simulation_proxy, raven_hud);
	lua_interface->Begin_InGame();
	
	research_manager.EnableTick = true;
	lua_interface->EnableTick = true;
}

void WSystemCore::on_unreal_init()
{
	RC::Output::send<LogLevel::Verbose>(STR("WSystem initializing...\n"));

	UC::FMemory::Init(Unreal::FMemory::Realloc);  // NOLINT(clang-diagnostic-microsoft-cast)
	Unreal::Hook::RegisterInitGameStatePostCallback(std::bind_front(&WSystemCore::On_GameModeInit, this));
	
	function_libs.Init();
}

void WSystemCore::on_lua_start(LuaMadeSimple::Lua& lua, LuaMadeSimple::Lua& main_lua, LuaMadeSimple::Lua& async_lua,
	std::vector<LuaMadeSimple::Lua*>& hook_luas)
{
	this->lua = lua.get_lua_state();
	this->lua_interface->Initialize();

	RC::Output::send<LogLevel::Verbose>(STR("WSystem Lua Mod Loaded.\n"));
}
