#include <pch.h>

#include "UnitsInfoSubsystem.h"

void UnitsInfoSubsystem::GetShipsFormationAndStance(const UC::TArray<ASimShip>& ships, bool& single_formation,
	std::int32_t& formation_order_index, UUnitOrderStaticData& formation_order, bool& single_stance,
	std::int32_t& stance_order_index, UUnitOrderStaticData& stance_order, const std::source_location& location) const
{
	const auto func = FindFunction(STR("GetShipsFormationAndStance"), location);
	struct {
		UC::TArray<ASimShip> ships;
		bool single_formation;
		std::int32_t formation_order_index;
		UUnitOrderStaticData formation_order;
		bool single_stance;
		std::int32_t stance_order_index;
		UUnitOrderStaticData stance_order;
	} args{
		ships,
		single_formation,
		formation_order_index,
		formation_order,
		single_stance,
		stance_order_index,
		stance_order
	};
	obj->ProcessEvent(func, &args);
	single_formation = args.single_formation;
	formation_order_index = args.formation_order_index;
	formation_order = args.formation_order;
	single_stance = args.single_stance;
	stance_order_index = args.stance_order_index;
	stance_order = args.stance_order;
}

void UnitsInfoSubsystem::IsUnitResourceController(const ASimEntity sim_entity, const USimPlayer sim_player, bool& result,
	bool& belongs_to_player, const std::source_location& location) const
{
	const auto func = FindFunction(STR("IsUnitResourceController"), location);
	struct {
		ASimEntity sim_entity;
		USimPlayer sim_player;
		bool result;
		bool belongs_to_player;
	} args{
		sim_entity,
		sim_player,
		result,
		belongs_to_player
	};
	obj->ProcessEvent(func, &args);
	result = args.result;
	belongs_to_player = args.belongs_to_player;
}

void UnitsInfoSubsystem::GetShipsToDockWith(USimPlayer sim_player, ASimEntity docker,
	UC::TArray<ASimShip>& out_dockees, const std::source_location& location) const
{
	const auto func = FindFunction(STR("GetShipsToDockWith"), location);
	struct {
		USimPlayer sim_player;
		ASimEntity docker;
		UC::TArray<ASimShip> out_dockees;
	} args{
		sim_player,
		docker,
		std::move(out_dockees)
	};
	obj->ProcessEvent(func, &args);
	out_dockees = std::move(args.out_dockees);
}

void UnitsInfoSubsystem::GetResourceControllersOfPlayer(const USimPlayer sim_player, UC::TArray<ASimShip>& result, const std::source_location& location) const
{
	const auto func = FindFunction(STR("GetResourceControllersOfPlayer"), location);
	struct {
		USimPlayer sim_player;
		UC::TArray<ASimShip> result;
	} args{
		sim_player,
		std::move(result)
	};
	obj->ProcessEvent(func, &args);
	result = std::move(args.result);
}

void UnitsInfoSubsystem::GetProductionUnitsOfSimPlayer(USimPlayer sim_player, UC::TArray<ASimEntity>& result, const std::source_location& location) const
{
	const auto func = FindFunction(STR("GetProductionUnitsOfSimPlayer"), location);
	struct {
		USimPlayer sim_player;
		UC::TArray<ASimEntity> result;
	} args{
		sim_player,
		std::move(result)
	};
	obj->ProcessEvent(func, &args);
	result = std::move(args.result);
}

void UnitsInfoSubsystem::GetProductionCapableUnitsCopy(UC::TArray<ASimEntity>& result, const std::source_location& location) const
{
	const auto func = FindFunction(STR("GetProductionCapableUnitsCopy"), location);
	struct {
		UC::TArray<ASimEntity> result;
	} args{
		std::move(result)
	};
	obj->ProcessEvent(func, &args);
	result = std::move(args.result);
}

void UnitsInfoSubsystem::GetIdleResourceControllersOfPlayer(const USimPlayer sim_player,
	UC::TArray<ASimShip>& result, const std::source_location& location) const
{
	const auto func = FindFunction(STR("GetIdleResourceControllersOfPlayer"), location);
	struct {
		USimPlayer sim_player;
		UC::TArray<ASimShip> result;
	} args{
		sim_player,
		std::move(result)
	};
	obj->ProcessEvent(func, &args);
	result = std::move(args.result);
}

void UnitsInfoSubsystem::GetCarrierUnitsOfSimPlayer(USimPlayer sim_player, UC::TArray<ASimEntity>& result, const std::source_location& location) const
{
	const auto func = FindFunction(STR("GetCarrierUnitsOfSimPlayer"), location);
	struct {
		USimPlayer sim_player;
		UC::TArray<ASimEntity> result;
	} args{
		sim_player,
		std::move(result)
	};
	obj->ProcessEvent(func, &args);
	result = std::move(args.result);
}

void UnitsInfoSubsystem::GetCarrierUnitsCopy(UC::TArray<ASimEntity>& result, const std::source_location& location) const
{
	const auto func = FindFunction(STR("GetCarrierUnitsCopy"), location);
	struct {
		UC::TArray<ASimEntity> result;
	} args{
		std::move(result)
	};
	obj->ProcessEvent(func, &args);
	result = std::move(args.result);
}
