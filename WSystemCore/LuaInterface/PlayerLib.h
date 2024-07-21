#pragma once
#include <pch.h>

#include <LibWrapper/TiirPlayerFunctionLibrary.h>
#include <DataWrapper/RavenSimulationProxy.h>

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

	void Initialize(sol::state_view* lua, TiirPlayerFunctionLibrary* lib, SobGroupManager* sob_group_manager);
	void Begin_InGame(RavenSimulationProxy sim_proxy);

	void SetResourceUnits(std::int32_t player_index, std::int32_t resource_unit_total) const;
	void ResetCommanderSupply(std::int32_t player_index) const;
	void PlayerKill(std::int32_t player_index) const;
	[[nodiscard]] bool PlayerIsAlive(std::int32_t player_index) const;
	[[nodiscard]] bool PlayerHasShipWithBuildQueue(std::int32_t player_index) const;
	[[nodiscard]] bool PlayerHasNonResourceShipWithBuildQueue(std::int32_t player_index) const;
	[[nodiscard]] bool PlayerHasMothership(std::int32_t player_index) const;
	void PlayerEntityGroup(std::string_view output_group, std::int32_t player_index) const;
	[[nodiscard]] std::int32_t PlayerCount() const;
	[[nodiscard]] bool IsValid(const TiirCommander& player) const;
	[[nodiscard]] bool IsHuman(std::int32_t player_index) const;
	[[nodiscard]] bool IsEnvironment(const TiirCommander& player) const;
	[[nodiscard]] std::int32_t GetResourceUnits(std::int32_t player_index) const;
	[[nodiscard]] std::int32_t GetPlayerIndex(const TiirCommander& player) const;
	[[nodiscard]] std::tuple<bool, TiirCommander> GetPlayerFromIndex(std::int32_t player_index) const;
	[[nodiscard]] TiirCommander GetEnvironmentPlayer() const;
	void AddResourceUnits(std::int32_t player_index, std::int32_t resource_unit_count) const;
	void SetPlayerName(std::int32_t player_index, std::string_view name) const;
	[[nodiscard]] std::string GetPlayerName(std::int32_t player_index) const;
	[[nodiscard]] std::int32_t GetPlayerTeamID(std::int32_t player_index) const;
private:
	sol::state_view* lua = nullptr;
	SobGroupManager* sob_group_manager = nullptr;
	RavenSimulationProxy sim_proxy = nullptr;
	TiirPlayerFunctionLibrary* lib = nullptr;
};