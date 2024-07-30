#include <pch.h>

#include "EntityIdManager.h"

void EntityIdManager::Begin_InGame(RavenSimulationProxy sim_proxy)
{
	this->sim_proxy = sim_proxy;
	id_to_entity.clear();
	alive_entity.clear();
	newly_dead_entity.clear();
	newly_born_entity.clear();
}

void EntityIdManager::Tick()
{
	static std::vector<std::uint64_t> new_alive_entity;
	id_to_entity.clear();
	newly_dead_entity.clear();
	newly_born_entity.clear();
	new_alive_entity.clear();

	for (const auto& entity_map = sim_proxy.EntityMap; auto& kv : entity_map)
	{
		if (auto entity = kv.Value(); entity.IsValid())
		{
			const auto entity_id = static_cast<std::uint64_t>(kv.Key());
			id_to_entity.emplace(entity_id, entity);
		}
	}

	for(const auto& id : id_to_entity | std::views::keys)
	{
		new_alive_entity.push_back(id);
	}

	std::ranges::set_difference(alive_entity, new_alive_entity, std::back_inserter(newly_dead_entity));
	std::ranges::set_difference(new_alive_entity, alive_entity, std::back_inserter(newly_born_entity));

	alive_entity = std::move(new_alive_entity);
}

ASimEntity EntityIdManager::FindEntity(std::uint64_t entity_id) const
{
	if (const auto it = id_to_entity.find(entity_id); it != id_to_entity.end())
	{
		return it->second;
	}
	return nullptr;
}

std::span<const std::uint64_t> EntityIdManager::GetNewlyDeadEntity() const
{
	return newly_dead_entity;
}

std::span<const std::uint64_t> EntityIdManager::GetNewlyBornEntity() const
{
	return newly_born_entity;
}

