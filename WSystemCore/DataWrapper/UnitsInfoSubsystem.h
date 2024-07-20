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
	WSYS_MEMBER_FUNCTION_VOID(IsUnitResourceController, SimEntity, sim_entity, SimPlayer, sim_player, bool*, result, bool*, belongs_to_player)
    WSYS_MEMBER_FUNCTION(bool, IsUnitProductionCapable, SimEntity, sob)
    WSYS_MEMBER_FUNCTION(bool, IsUnitCarrier, SimEntity, sob)
    WSYS_MEMBER_FUNCTION(bool, IsShipDockableOnShip, SimShip, docker, SimShip, dockee)
    WSYS_MEMBER_FUNCTION_VOID(GetShipsToDockWith, SimPlayer, sim_player, SimEntity, docker, UC::TArray<SimShip>*, out_dockees)
    WSYS_MEMBER_FUNCTION_VOID(GetShipsFormationAndStance, const UC::TArray<SimShip>&, ships, bool*, single_formation, std::int32_t*, formation_order_index, UnitOrderStaticData*, formation_order, bool*, single_stance, std::int32_t*, stance_order_index, UnitOrderStaticData*, stance_order)
    WSYS_MEMBER_FUNCTION_VOID(GetResourceControllersOfPlayer, const SimPlayer, sim_player, UC::TArray<SimShip>*, result)
    WSYS_MEMBER_FUNCTION_VOID(GetProductionUnitsOfSimPlayer, SimPlayer, sim_player, UC::TArray<SimEntity>*, result)
    WSYS_MEMBER_FUNCTION_VOID(GetProductionCapableUnitsCopy, UC::TArray<SimEntity>*, result)
    WSYS_MEMBER_FUNCTION(std::int32_t, GetNumResourceControllersOfPlayer, const SimPlayer, sim_player)
    WSYS_MEMBER_FUNCTION(std::int32_t, GetNumIdleResourceControllersOfPlayer, const SimPlayer, sim_player)
    WSYS_MEMBER_FUNCTION_VOID(GetIdleResourceControllersOfPlayer, const SimPlayer, sim_player, UC::TArray<SimShip>*, result)
    WSYS_MEMBER_FUNCTION_VOID(GetCarrierUnitsOfSimPlayer, SimPlayer, sim_player, UC::TArray<SimEntity>*, result)
    WSYS_MEMBER_FUNCTION_VOID(GetCarrierUnitsCopy, UC::TArray<SimEntity>*, result)
    WSYS_MEMBER_FUNCTION(SimShip, GetAnyResourceController, const SimPlayer, sim_player)
    WSYS_MEMBER_FUNCTION(bool, CanSimPlayerDockShip, SimPlayer, sim_player, SimEntity, docker)
};