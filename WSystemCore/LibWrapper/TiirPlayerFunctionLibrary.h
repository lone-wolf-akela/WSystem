#pragma once
#include <pch.h>

#include "LibBase.h"
#include "LibDataTypes.h"

class TiirPlayerFunctionLibrary : public LibBase<TiirPlayerFunctionLibrary>
{
public:
    static constexpr auto LibPath = STR("/Script/RavenSimulation.TiirPlayerFunctionLibrary");
    WSYS_MEMBER_FUNCTION_VOID(SetResourceUnits, std::int32_t, player_index, std::int32_t, resource_unit_total)

    // todo bound to lua
    // WSYS_MEMBER_FUNCTION_VOID(SetCommanderSupply, std::int32_t, player_index, const TMap<TSoftObjectPtr<UUnitSupplyFamily>, std::int32_t>&, supply_families)

    WSYS_MEMBER_FUNCTION_VOID(ResetCommanderSupply, std::int32_t, player_index)

    WSYS_MEMBER_FUNCTION_VOID(PlayerKill, std::int32_t, player_index)

    WSYS_MEMBER_FUNCTION(bool, PlayerIsAlive, std::int32_t, player_index)

    WSYS_MEMBER_FUNCTION(bool, PlayerHasShipWithBuildQueue, std::int32_t, player_index)

    WSYS_MEMBER_FUNCTION(bool, PlayerHasNonResourceShipWithBuildQueue, std::int32_t, player_index)

    WSYS_MEMBER_FUNCTION(bool, PlayerHasMothership, std::int32_t, player_index)

    WSYS_MEMBER_FUNCTION(TiirEntityGroup, PlayerEntityGroup, std::int32_t, player_index)

    WSYS_MEMBER_FUNCTION_NOARGS(std::int32_t, PlayerCount)

    // not bound to lua
    WSYS_MEMBER_FUNCTION(bool, NotEqual_CommanderCommander, const TiirCommander&, a, const TiirCommander&, b)

    WSYS_MEMBER_FUNCTION(bool, IsValid, const TiirCommander&, player)

    WSYS_MEMBER_FUNCTION(bool, IsHuman, const TiirCommander&, player)

    WSYS_MEMBER_FUNCTION(bool, IsEnvironment, const TiirCommander&, player)

    WSYS_MEMBER_FUNCTION(std::int32_t, GetResourceUnits, std::int32_t, player_index)

    WSYS_MEMBER_FUNCTION(std::int32_t, GetPlayerIndex, const TiirCommander&, player)

    bool GetPlayerFromIndex(std::int32_t player_index, TiirCommander& player) const;

    WSYS_MEMBER_FUNCTION_VOID_REF(GetEnvironmentPlayer, TiirCommander&, player)

    // not bound to lua
    WSYS_MEMBER_FUNCTION(bool, EqualEqual_CommanderCommander, const TiirCommander&, a, const TiirCommander&, b)

    WSYS_MEMBER_FUNCTION_VOID(AddResourceUnits, std::int32_t, player_index, std::int32_t, resource_unit_count)

    // todo bound to lua
    //WSYS_MEMBER_FUNCTION_VOID(AddCommanderSupply, std::int32_t, player_index, const TMap<TSoftObjectPtr<UUnitSupplyFamily>, std::int32_t>&, supply_families)
};