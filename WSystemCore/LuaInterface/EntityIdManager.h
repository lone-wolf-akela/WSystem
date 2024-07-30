#pragma once
#include <pch.h>

#include <DataWrapper/SimEntity.h>
#include <DataWrapper/RavenSimulationProxy.h>

class EntityIdManager
{
public:
	EntityIdManager() = default;

	EntityIdManager(const EntityIdManager& o) = delete;
	EntityIdManager& operator=(const EntityIdManager& o) = delete;
	EntityIdManager(EntityIdManager&& o) noexcept = default;
	EntityIdManager& operator=(EntityIdManager&& o) noexcept = default;

	~EntityIdManager() = default;

	void Begin_InGame(RavenSimulationProxy sim_proxy);
	void Tick();
	[[nodiscard]] ASimEntity FindEntity(std::uint64_t entity_id) const;
	[[nodiscard]] std::span<const std::uint64_t> GetNewlyDeadEntity() const;
	[[nodiscard]] std::span<const std::uint64_t> GetNewlyBornEntity() const;

private:
	RavenSimulationProxy sim_proxy = nullptr;
	std::map<std::uint64_t, ASimEntity> id_to_entity;
	std::vector<std::uint64_t> alive_entity;
	std::vector<std::uint64_t> newly_dead_entity;
	std::vector<std::uint64_t> newly_born_entity;
};

