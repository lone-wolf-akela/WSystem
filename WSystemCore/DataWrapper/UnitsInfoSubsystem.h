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
    WSYS_MEMBER_FUNCTION(bool, IsUnitProductionCapable, ASimEntity, sob)
    WSYS_MEMBER_FUNCTION(bool, IsUnitCarrier, ASimEntity, sob)
    WSYS_MEMBER_FUNCTION(bool, IsShipDockableOnShip, ASimShip, docker, ASimShip, dockee)
    WSYS_MEMBER_FUNCTION(std::int32_t, GetNumResourceControllersOfPlayer, const USimPlayer, sim_player)
    WSYS_MEMBER_FUNCTION(std::int32_t, GetNumIdleResourceControllersOfPlayer, const USimPlayer, sim_player)
    WSYS_MEMBER_FUNCTION(ASimShip, GetAnyResourceController, const USimPlayer, sim_player)
    WSYS_MEMBER_FUNCTION(bool, CanSimPlayerDockShip, USimPlayer, sim_player, ASimEntity, docker)

    void GetShipsFormationAndStance(const UC::TArray<ASimShip>& ships, bool& single_formation, std::int32_t& formation_order_index, UUnitOrderStaticData& formation_order, bool& single_stance, std::int32_t& stance_order_index, UUnitOrderStaticData& stance_order, const std::source_location& location = std::source_location::current()) const;
    void IsUnitResourceController(const ASimEntity sim_entity, const USimPlayer sim_player, bool& result, bool& belongs_to_player, const std::source_location& location = std::source_location::current()) const;
    void GetShipsToDockWith(USimPlayer sim_player, ASimEntity docker, UC::TArray<ASimShip>& out_dockees, const std::source_location& location = std::source_location::current()) const;
    void GetResourceControllersOfPlayer(const USimPlayer sim_player, UC::TArray<ASimShip>& result, const std::source_location& location = std::source_location::current()) const;
    void GetProductionUnitsOfSimPlayer(USimPlayer sim_player, UC::TArray<ASimEntity>& result, const std::source_location& location = std::source_location::current()) const;
    void GetProductionCapableUnitsCopy(UC::TArray<ASimEntity>& result, const std::source_location& location = std::source_location::current()) const;
    void GetIdleResourceControllersOfPlayer(const USimPlayer sim_player, UC::TArray<ASimShip>& result, const std::source_location& location = std::source_location::current()) const;
    void GetCarrierUnitsOfSimPlayer(USimPlayer sim_player, UC::TArray<ASimEntity>& result, const std::source_location& location = std::source_location::current()) const;
    void GetCarrierUnitsCopy(UC::TArray<ASimEntity>& result, const std::source_location& location = std::source_location::current()) const;
};