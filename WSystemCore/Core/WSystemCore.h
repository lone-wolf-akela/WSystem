#pragma once
#include <pch.h>

#include <DataWrapper/RavenGameMode.h>
#include <DataWrapper/RavenSimulationProxy.h>
#include <DataWrapper/RTSLevelScriptActor.h>
#include <DataWrapper/RavenHUD.h>
#include <DataWrapper/UnitsInfoSubsystem.h>
#include <DataWrapper/WBP_BuildPanel.h>
#include <DataWrapper/RTSPlayerController.h>

#include <LibWrapper/Libs.h>

#include <LuaInterface/LuaInterface.h>

#include "ResearchManager.h"
#include "Database.h"

class WSystemCore final : public CppUserModBase
{
public:
    WSystemCore();
    ~WSystemCore() override = default;

    std::optional<sol::state_view> lua;

    bool first_game_mode_init = true;

    RavenGameMode raven_game_mode = nullptr;
    ELobbyState last_lobby_state = ELobbyState::Invalid;
    RavenSimulationProxy raven_simulation_proxy = nullptr;
    ARTSLevelScriptActor rts_level_script_actor = nullptr;
    RavenHUD raven_hud = nullptr;
    UnitsInfoSubsystem units_info_subsystem = nullptr;
    WBP_BuildPanel wbp_build_panel = nullptr;
    ARTSPlayerController rts_player_controller = nullptr;

    FunctionLibs function_libs;

    WSysResearchManager research_manager;
    std::shared_ptr<LuaInterface> lua_interface;
    Database database;

    void on_unreal_init() override;
    // void on_update() override;
    /**
         * Executes after a Lua mod of the same name is started.
         * @param lua This is the main Lua instance.
         * @param main_lua This is the main Lua thread instance.
         * @param async_lua This is the Lua instance for asynchronous things like ExecuteAsync and ExecuteWithDelay.
         * @param hook_luas This is a container of Lua instances that are used for game-thread hooks like ExecuteInGameThread.
         */
    void on_lua_start(LuaMadeSimple::Lua& lua,
        LuaMadeSimple::Lua& main_lua,
        LuaMadeSimple::Lua& async_lua,
        std::vector<LuaMadeSimple::Lua*>& hook_luas) override;

    /**
         * Executes before a Lua mod of the same name is about to be stopped.
         * @param lua This is the main Lua instance.
         * @param main_lua This is the main Lua thread instance.
         * @param async_lua This is the Lua instance for asynchronous things like ExecuteAsync and ExecuteWithDelay.
         * @param hook_luas This is a container of Lua instances that are used for game-thread hooks like ExecuteInGameThread.
         */
    void on_lua_stop(LuaMadeSimple::Lua& lua,
        LuaMadeSimple::Lua& main_lua,
        LuaMadeSimple::Lua& async_lua,
        std::vector<LuaMadeSimple::Lua*>& hook_luas) override;

    void On_GameModeInit(Unreal::AGameModeBase* gamemode);
    void OnFirst_GameModeInit();

    void Pre_InGameTick(Unreal::UnrealScriptFunctionCallableContext& context, void* custom_data);
    void Post_InGameTick(Unreal::UnrealScriptFunctionCallableContext& context, void* custom_data);

    void Pre_GameModeStateTransition(Unreal::UnrealScriptFunctionCallableContext& context, void* custom_data);
    void Post_GameModeStateTransition(Unreal::UnrealScriptFunctionCallableContext& context, void* custom_data);

    void Pre_TiirTick(Unreal::UnrealScriptFunctionCallableContext& context, void* custom_data);
    void Post_TiirTick(Unreal::UnrealScriptFunctionCallableContext& context, void* custom_data);

    void Begin_InitScenario();
    void Begin_InGame();
};
