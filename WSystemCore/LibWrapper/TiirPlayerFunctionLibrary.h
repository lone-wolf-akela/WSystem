#pragma once
#include <cstdint>

#include "LibBase.h"
#include "LibDataTypes.h"

class TiirPlayerFunctionLibrary : public LibBase<TiirPlayerFunctionLibrary>
{
public:
    static constexpr auto LibPath = STR("/Script/RavenSimulation.TiirPlayerFunctionLibrary");

    WSYS_MEMBER_FUNCTION_NOARGS(std::int32_t, PlayerCount)

    WSYS_MEMBER_FUNCTION_VOID(ResetCommanderSupply, std::int32_t, player_index)
    WSYS_MEMBER_FUNCTION_VOID(PlayerKill, std::int32_t, player_index)
    WSYS_MEMBER_FUNCTION(bool, PlayerIsAlive, std::int32_t, player_index)

    WSYS_MEMBER_FUNCTION(bool, PlayerHasShipWithBuildQueue, std::int32_t, player_index)
    WSYS_MEMBER_FUNCTION(bool, PlayerHasNonResourceShipWithBuildQueue, std::int32_t, player_index)
    WSYS_MEMBER_FUNCTION(bool, PlayerHasMothership, std::int32_t, player_index)

    WSYS_MEMBER_FUNCTION(std::int32_t, GetResourceUnits, std::int32_t, player_index)
    WSYS_MEMBER_FUNCTION_VOID(AddResourceUnits, std::int32_t, player_index, std::int32_t, resource_unit_count)
    WSYS_MEMBER_FUNCTION_VOID(SetResourceUnits, std::int32_t, player_index, std::int32_t, resource_unit_total)

    WSYS_MEMBER_FUNCTION(TiirEntityGroup, PlayerEntityGroup, std::int32_t, player_index)  
        
    WSYS_MEMBER_FUNCTION(bool, IsValid, TiirCommander*, player)
    WSYS_MEMBER_FUNCTION(bool, IsHuman, TiirCommander*, player)
    WSYS_MEMBER_FUNCTION(bool, IsEnvironment, TiirCommander*, player)
        
    WSYS_MEMBER_FUNCTION(std::int32_t, GetPlayerIndex, TiirCommander*, player)
    WSYS_MEMBER_FUNCTION(bool, GetPlayerFromIndex, std::int32_t, player_index, TiirCommander*, player)
    WSYS_MEMBER_FUNCTION_VOID(GetEnvironmentPlayer, TiirCommander*, player)
        
    WSYS_MEMBER_FUNCTION(bool, NotEqual_CommanderCommander, TiirCommander*, a, TiirCommander*, b)
    WSYS_MEMBER_FUNCTION(bool, EqualEqual_CommanderCommander, TiirCommander*, a, TiirCommander*, b)

    // WSYS_MEMBER_FUNCTION_VOID(SetCommanderSupply, std::int32_t, player_index, UC::TMap<RC::Unreal::TSoftObjectPtr<UnitSupplyFamily>, std::int32_t>*, supply_families)
    // WSYS_MEMBER_FUNCTION_VOID(AddCommanderSupply, std::int32_t, player_index, UC::TMap<TSoftObjectPtr<UnitSupplyFamily>, std::int32_t>, supply_families)

};