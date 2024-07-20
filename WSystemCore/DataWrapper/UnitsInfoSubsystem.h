#pragma once
#include <pch.h>

#include "UObject.h"
#include "SimPlayer.h"
#include "SimEntity.h"
#include "SimShip.h"
#include "UnitOrderStaticData.h"

class UnitsInfoSubsystem : public UObjWrapper
{
	using UObjWrapper::UObjWrapper;
public:
    WSYS_MEMBER_FUNCTION(bool, IsUnitProductionCapable, SimEntity, sob)
    WSYS_MEMBER_FUNCTION(bool, IsUnitCarrier, SimEntity, sob)
    WSYS_MEMBER_FUNCTION(bool, IsShipDockableOnShip, SimShip, docker, SimShip, dockee)
    WSYS_MEMBER_FUNCTION(std::int32_t, GetNumResourceControllersOfPlayer, const SimPlayer, sim_player)
    WSYS_MEMBER_FUNCTION(std::int32_t, GetNumIdleResourceControllersOfPlayer, const SimPlayer, sim_player)
    WSYS_MEMBER_FUNCTION(SimShip, GetAnyResourceController, const SimPlayer, sim_player)
    WSYS_MEMBER_FUNCTION(bool, CanSimPlayerDockShip, SimPlayer, sim_player, SimEntity, docker)

    void GetShipsFormationAndStance(const UC::TArray<SimShip>& ships, bool& single_formation, std::int32_t& formation_order_index, UnitOrderStaticData& formation_order, bool& single_stance, std::int32_t& stance_order_index, UnitOrderStaticData& stance_order, const std::source_location& location = std::source_location::current()) const;
    void IsUnitResourceController(const SimEntity sim_entity, const SimPlayer sim_player, bool& result, bool& belongs_to_player) const;
    void GetShipsToDockWith(SimPlayer sim_player, SimEntity docker, UC::TArray<SimShip>& out_dockees) const;
    void GetResourceControllersOfPlayer(const SimPlayer sim_player, UC::TArray<SimShip>& result) const;
    void GetProductionUnitsOfSimPlayer(SimPlayer sim_player, UC::TArray<SimEntity>& result) const;
    void GetProductionCapableUnitsCopy(UC::TArray<SimEntity>& result) const;
    void GetIdleResourceControllersOfPlayer(const SimPlayer sim_player, UC::TArray<SimShip>& result) const;
    void GetCarrierUnitsOfSimPlayer(SimPlayer sim_player, UC::TArray<SimEntity>& result) const;
    void GetCarrierUnitsCopy(UC::TArray<SimEntity>& result) const;
};