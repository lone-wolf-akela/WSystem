#include "SobGroupLib.h"

void SobGroupManager::BindLuaState(sol::state_view* lua, TiirEntityGroupFunctionLibrary* lib, Database* database)
{
	this->lua = lua;
	this->lib = lib;
	this->database = database;

	auto sobgroup_manager_t = lua->new_usertype<SobGroupManager>(
		"SobGroup",
		// functions
		"CreateOrClear", &SobGroupManager::CreateOrClear,
		"CreateIfNotExists", &SobGroupManager::CreateIfNotExists,
		"IsExists", &SobGroupManager::IsExists,
		"Delete", &SobGroupManager::Delete,
		"FillGroupFromPlayer", &SobGroupManager::FillGroupFromPlayer,
		"HyperspaceToDestination", &SobGroupManager::HyperspaceToDestination,
		"Teleport", &SobGroupManager::Teleport,
		"FillGroupFromFilteredType", &SobGroupManager::FillGroupFromFilteredType,
		"GroupCount", &SobGroupManager::GroupCount,
		"TakeDamageAbsolute", &SobGroupManager::TakeDamageAbsolute,
		"TakeDamage", &SobGroupManager::TakeDamage,
		"Stop", &SobGroupManager::Stop,
		"SetVelocity", &SobGroupManager::SetVelocity
	);
}

bool SobGroupManager::CreateOrClear(std::string_view name)
{
	if (const auto found = groups.find(name); found != groups.end())
	{
		found->second.Entities = {};
		return false;
	}
	else
	{
		groups.emplace(name, TiirEntityGroup{});
		return true;
	}
}

bool SobGroupManager::CreateIfNotExists(std::string_view name)
{
	if (!groups.contains(name))
	{
		groups.emplace(name, TiirEntityGroup{});
		return true;
	}
	return false;
}

bool SobGroupManager::IsExists(std::string_view name) const
{
	return groups.contains(name);
}

bool SobGroupManager::Delete(std::string_view name)
{
	const auto found = groups.find(name);

	if (found == groups.end())
	{
		return false;
	}

	groups.erase(found);
	return true;
}

std::int32_t SobGroupManager::FillGroupFromPlayer(
	std::string_view group, 
	std::int32_t owning_player,
	bool include_docked, 
	bool include_in_hyperspace, 
	bool include_dead)
{
	return lib->FillGroupFromPlayer(FindGroup(group), owning_player, include_docked, include_in_hyperspace, include_dead);
}

void SobGroupManager::HyperspaceToDestination(
	std::string_view group, 
	double dest_rotation_w, double dest_rotation_x, double dest_rotation_y, double dest_rotation_z, 
	double dest_position_x, double dest_position_y, double dest_position_z,
	double scale_x, double scale_y, double scale_z, 
	bool skip_placement_logic)
{

	RC::Unreal::FQuat dest_rotation{ dest_rotation_x, dest_rotation_y, dest_rotation_z, dest_rotation_w };
	RC::Unreal::FVector dest_position{ dest_position_x, dest_position_y, dest_position_z };
	RC::Unreal::FVector scale{ scale_x, scale_y, scale_z };
	lib->HyperspaceToDestination(
		FindGroup(group),
		RC::Unreal::FTransform{ dest_rotation, dest_position, scale },
		skip_placement_logic);
}

void SobGroupManager::Teleport(std::string_view group, double dest_rotation_w, double dest_rotation_x,
	double dest_rotation_y, double dest_rotation_z, double dest_position_x, double dest_position_y, double dest_position_z,
	double scale_x, double scale_y, double scale_z, bool skip_placement_logic)
{
	RC::Unreal::FQuat dest_rotation{ dest_rotation_x, dest_rotation_y, dest_rotation_z, dest_rotation_w };
	RC::Unreal::FVector dest_position{ dest_position_x, dest_position_y, dest_position_z };
	RC::Unreal::FVector scale{ scale_x, scale_y, scale_z };
	lib->Teleport(
		FindGroup(group),
		RC::Unreal::FTransform{ dest_rotation, dest_position, scale },
		skip_placement_logic);
}

std::int32_t SobGroupManager::FillGroupFromFilteredType(
	std::string_view group, 
	std::string_view source_group,
	sol::table desired_types)
{
	UC::TArray<EntityStaticData> tarray_desired_types;
	tarray_desired_types.Reserve(desired_types.size());
	for (const auto& kv : desired_types)
	{
		const auto type = kv.second.as<std::string>();
		auto entity_data = database->GetEntityData(type);
		tarray_desired_types.Add(entity_data);
	}
	return lib->FillGroupFromFilteredType(FindGroup(group), FindGroup(source_group), tarray_desired_types);
}

std::int32_t SobGroupManager::GroupCount(std::string_view group)
{
	return lib->GroupCount(FindGroup(group));
}

void SobGroupManager::TakeDamageAbsolute(std::string_view group, float damage_absolute)
{
	lib->TakeDamageAbsolute(FindGroup(group), damage_absolute);
}

void SobGroupManager::TakeDamage(std::string_view group, float damage_percentage)
{
	lib->TakeDamage(FindGroup(group), damage_percentage);
}

void SobGroupManager::Stop(std::string_view group)
{
	lib->Stop(FindGroup(group));
}

void SobGroupManager::SetVelocity(std::string_view group, double x, double y, double z)
{
	lib->SetVelocity(FindGroup(group), RC::Unreal::FVector{ x, y, z });
}

TiirEntityGroup& SobGroupManager::FindGroup(std::string_view name)
{
	if (const auto found = groups.find(name); found != groups.end())
	{
		return found->second;
	}
	throw std::runtime_error("SobGroup not found");
}
