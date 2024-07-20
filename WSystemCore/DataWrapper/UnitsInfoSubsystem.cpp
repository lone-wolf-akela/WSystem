#include <pch.h>

#include "UnitsInfoSubsystem.h"

void UnitsInfoSubsystem::GetShipsFormationAndStance(const UC::TArray<SimShip>& ships, bool& single_formation,
	std::int32_t& formation_order_index, UnitOrderStaticData& formation_order, bool& single_stance,
	std::int32_t& stance_order_index, UnitOrderStaticData& stance_order, const std::source_location& location) const
{
	const auto func = FindFunction(STR("GetShipsFormationAndStance"), location);
	struct {
		UC::TArray<SimShip> ships;
		bool single_formation;
		std::int32_t formation_order_index;
		UnitOrderStaticData formation_order;
		bool single_stance;
		std::int32_t stance_order_index;
		UnitOrderStaticData stance_order;
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

void UnitsInfoSubsystem::IsUnitResourceController(const SimEntity sim_entity, const SimPlayer sim_player, bool& result,
	bool& belongs_to_player, const std::source_location& location) const
{
	const auto func = FindFunction(STR("IsUnitResourceController"), location);
	struct {
		SimEntity sim_entity;
		SimPlayer sim_player;
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

void UnitsInfoSubsystem::GetShipsToDockWith(SimPlayer sim_player, SimEntity docker,
	UC::TArray<SimShip>& out_dockees, const std::source_location& location) const
{
	const auto func = FindFunction(STR("GetShipsToDockWith"), location);
	struct {
		SimPlayer sim_player;
		SimEntity docker;
		UC::TArray<SimShip> out_dockees;
	} args{
		sim_player,
		docker,
		std::move(out_dockees)
	};
	obj->ProcessEvent(func, &args);
	out_dockees = std::move(args.out_dockees);
}

void UnitsInfoSubsystem::GetResourceControllersOfPlayer(const SimPlayer sim_player, UC::TArray<SimShip>& result, const std::source_location& location) const
{
	const auto func = FindFunction(STR("GetResourceControllersOfPlayer"), location);
	struct {
		SimPlayer sim_player;
		UC::TArray<SimShip> result;
	} args{
		sim_player,
		std::move(result)
	};
	obj->ProcessEvent(func, &args);
	result = std::move(args.result);
}

void UnitsInfoSubsystem::GetProductionUnitsOfSimPlayer(SimPlayer sim_player, UC::TArray<SimEntity>& result, const std::source_location& location) const
{
	const auto func = FindFunction(STR("GetProductionUnitsOfSimPlayer"), location);
	struct {
		SimPlayer sim_player;
		UC::TArray<SimEntity> result;
	} args{
		sim_player,
		std::move(result)
	};
	obj->ProcessEvent(func, &args);
	result = std::move(args.result);
}

void UnitsInfoSubsystem::GetProductionCapableUnitsCopy(UC::TArray<SimEntity>& result, const std::source_location& location) const
{
	const auto func = FindFunction(STR("GetProductionCapableUnitsCopy"), location);
	struct {
		UC::TArray<SimEntity> result;
	} args{
		std::move(result)
	};
	obj->ProcessEvent(func, &args);
	result = std::move(args.result);
}

void UnitsInfoSubsystem::GetIdleResourceControllersOfPlayer(const SimPlayer sim_player,
	UC::TArray<SimShip>& result, const std::source_location& location) const
{
	const auto func = FindFunction(STR("GetIdleResourceControllersOfPlayer"), location);
	struct {
		SimPlayer sim_player;
		UC::TArray<SimShip> result;
	} args{
		sim_player,
		std::move(result)
	};
	obj->ProcessEvent(func, &args);
	result = std::move(args.result);
}

void UnitsInfoSubsystem::GetCarrierUnitsOfSimPlayer(SimPlayer sim_player, UC::TArray<SimEntity>& result, const std::source_location& location) const
{
	const auto func = FindFunction(STR("GetCarrierUnitsOfSimPlayer"), location);
	struct {
		SimPlayer sim_player;
		UC::TArray<SimEntity> result;
	} args{
		sim_player,
		std::move(result)
	};
	obj->ProcessEvent(func, &args);
	result = std::move(args.result);
}

void UnitsInfoSubsystem::GetCarrierUnitsCopy(UC::TArray<SimEntity>& result, const std::source_location& location) const
{
	const auto func = FindFunction(STR("GetCarrierUnitsCopy"), location);
	struct {
		UC::TArray<SimEntity> result;
	} args{
		std::move(result)
	};
	obj->ProcessEvent(func, &args);
	result = std::move(args.result);
}
