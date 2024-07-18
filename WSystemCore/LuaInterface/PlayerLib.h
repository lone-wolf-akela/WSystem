#pragma once
#include <pch.h>

#include <LibWrapper/TiirPlayerFunctionLibrary.h>

#include "SobGroupLib.h"

class PlayerLibInterface
{
public:
	PlayerLibInterface() = default;

	PlayerLibInterface(const PlayerLibInterface& o) = delete;
	PlayerLibInterface& operator=(const PlayerLibInterface& o) = delete;
	PlayerLibInterface(PlayerLibInterface&& o) noexcept = default;
	PlayerLibInterface& operator=(PlayerLibInterface&& o) noexcept = default;

	~PlayerLibInterface() = default;

	void BindLuaState(sol::state_view* lua, TiirPlayerFunctionLibrary* lib, SobGroupManager* sob_group_manager);

	void SetResourceUnits(std::int32_t player_index, std::int32_t resource_unit_total) const;
	void ResetCommanderSupply(std::int32_t player_index) const;
	void PlayerKill(std::int32_t player_index) const;
	bool PlayerIsAlive(std::int32_t player_index) const;
	bool PlayerHasShipWithBuildQueue(std::int32_t player_index) const;
	bool PlayerHasNonResourceShipWithBuildQueue(std::int32_t player_index) const;
	bool PlayerHasMothership(std::int32_t player_index) const;
	void PlayerEntityGroup(std::string_view output_group, std::int32_t player_index) const;
	std::int32_t PlayerCount() const;
	bool IsValid(const TiirCommander& player) const;
	bool IsHuman(const TiirCommander& player) const;
	bool IsEnvironment(const TiirCommander& player) const;
	std::int32_t GetResourceUnits(std::int32_t player_index) const;
	std::int32_t GetPlayerIndex(const TiirCommander& player) const;
	std::tuple<bool, TiirCommander> GetPlayerFromIndex(std::int32_t player_index) const;
	TiirCommander GetEnvironmentPlayer() const;
	void AddResourceUnits(std::int32_t player_index, std::int32_t resource_unit_count) const;
private:
	sol::state_view* lua = nullptr;
	SobGroupManager* sob_group_manager = nullptr;
	TiirPlayerFunctionLibrary* lib = nullptr;
};