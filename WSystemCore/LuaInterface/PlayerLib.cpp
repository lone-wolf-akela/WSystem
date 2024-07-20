#include <pch.h>
#include "PlayerLib.h"

void PlayerLibInterface::BindLuaState(sol::state_view* lua, TiirPlayerFunctionLibrary* lib, SobGroupManager* sob_group_manager)
{
	this->lua = lua;
	this->lib = lib;
	this->sob_group_manager = sob_group_manager;

	lua->new_usertype<PlayerLibInterface>("PlayerLibInterface",
		"SetResourceUnits", &PlayerLibInterface::SetResourceUnits,
		"ResetCommanderSupply", &PlayerLibInterface::ResetCommanderSupply,
		"PlayerKill", &PlayerLibInterface::PlayerKill,
		"PlayerIsAlive", &PlayerLibInterface::PlayerIsAlive,
		"PlayerHasShipWithBuildQueue", &PlayerLibInterface::PlayerHasShipWithBuildQueue,
		"PlayerHasNonResourceShipWithBuildQueue", &PlayerLibInterface::PlayerHasNonResourceShipWithBuildQueue,
		"PlayerHasMothership", &PlayerLibInterface::PlayerHasMothership,
		"PlayerEntityGroup", &PlayerLibInterface::PlayerEntityGroup,
		"PlayerCount", &PlayerLibInterface::PlayerCount,
		"IsValid", &PlayerLibInterface::IsValid,
		"IsHuman", &PlayerLibInterface::IsHuman,
		"IsEnvironment", &PlayerLibInterface::IsEnvironment,
		"GetResourceUnits", &PlayerLibInterface::GetResourceUnits,
		"GetPlayerIndex", &PlayerLibInterface::GetPlayerIndex,
		"GetPlayerFromIndex", &PlayerLibInterface::GetPlayerFromIndex,
		"GetEnvironmentPlayer", &PlayerLibInterface::GetEnvironmentPlayer,
		"AddResourceUnits", &PlayerLibInterface::AddResourceUnits
	);
}

void PlayerLibInterface::SetResourceUnits(std::int32_t player_index, std::int32_t resource_unit_total) const
{
	lib->SetResourceUnits(player_index, resource_unit_total);
}

void PlayerLibInterface::ResetCommanderSupply(std::int32_t player_index) const
{
	lib->ResetCommanderSupply(player_index);
}

void PlayerLibInterface::PlayerKill(std::int32_t player_index) const
{
	lib->PlayerKill(player_index);
}

bool PlayerLibInterface::PlayerIsAlive(std::int32_t player_index) const
{
	return lib->PlayerIsAlive(player_index);
}

bool PlayerLibInterface::PlayerHasShipWithBuildQueue(std::int32_t player_index) const
{
	return lib->PlayerHasShipWithBuildQueue(player_index);
}

bool PlayerLibInterface::PlayerHasNonResourceShipWithBuildQueue(std::int32_t player_index) const
{
	return lib->PlayerHasNonResourceShipWithBuildQueue(player_index);
}

bool PlayerLibInterface::PlayerHasMothership(std::int32_t player_index) const
{
	return lib->PlayerHasMothership(player_index);
}

void PlayerLibInterface::PlayerEntityGroup(std::string_view output_group, std::int32_t player_index) const
{
	sob_group_manager->SetGroup(output_group, lib->PlayerEntityGroup(player_index));
}

std::int32_t PlayerLibInterface::PlayerCount() const
{
	return lib->PlayerCount();
}

bool PlayerLibInterface::IsValid(const TiirCommander& player) const
{
	return lib->IsValid(player);
}

bool PlayerLibInterface::IsHuman(const TiirCommander& player) const
{
	return lib->IsHuman(player);
}

bool PlayerLibInterface::IsEnvironment(const TiirCommander& player) const
{
	return lib->IsEnvironment(player);
}

std::int32_t PlayerLibInterface::GetResourceUnits(std::int32_t player_index) const
{
	return lib->GetResourceUnits(player_index);
}

std::int32_t PlayerLibInterface::GetPlayerIndex(const TiirCommander& player) const
{
	return lib->GetPlayerIndex(player);
}

std::tuple<bool, TiirCommander> PlayerLibInterface::GetPlayerFromIndex(std::int32_t player_index) const
{
	TiirCommander player;
	const bool result = lib->GetPlayerFromIndex(player_index, player);
	return { result, player };
}

TiirCommander PlayerLibInterface::GetEnvironmentPlayer() const
{
	TiirCommander player;
	lib->GetEnvironmentPlayer(player);
	return player;
}

void PlayerLibInterface::AddResourceUnits(std::int32_t player_index, std::int32_t resource_unit_count) const
{
	lib->AddResourceUnits(player_index, resource_unit_count);
}
