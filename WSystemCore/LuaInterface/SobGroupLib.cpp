#include <pch.h>

#include "SobGroupLib.h"

void SobGroupManager::BindLuaState(sol::state_view* lua, TiirEntityGroupFunctionLibrary* lib, Database* database)
{
	this->lua = lua;
	this->lib = lib;
	this->database = database;

	auto sobgroup_manager_t = lua->new_usertype<SobGroupManager>(
		"SobGroupManagerType",
		// functions
		"CreateOrClear", &SobGroupManager::CreateOrClear,
		"CreateIfNotExists", &SobGroupManager::CreateIfNotExists,
		"IsExists", &SobGroupManager::IsExists,
		"NotExistsOrEmpty", &SobGroupManager::IsEmptyOrNotExists,
		"Delete", &SobGroupManager::Delete,
		"FillGroupFromPlayer", &SobGroupManager::FillGroupFromPlayer,
		"HyperspaceToDestination", &SobGroupManager::HyperspaceToDestination,
		"Teleport", &SobGroupManager::Teleport,
		"FillGroupFromFilteredType", &SobGroupManager::FillGroupFromFilteredType,
		"GroupCount", &SobGroupManager::GroupCount,
		"TakeDamageAbsolute", &SobGroupManager::TakeDamageAbsolute,
		"TakeDamage", &SobGroupManager::TakeDamage,
		"Stop", &SobGroupManager::Stop,
		"SetVelocity", &SobGroupManager::SetVelocity,
		"UndeployTurret", &SobGroupManager::UndeployTurret,
		"ToggleAlternativeShipOrientation", &SobGroupManager::ToggleAlternativeShipOrientation,
		"Spawn", &SobGroupManager::Spawn,
		"SetTransform", &SobGroupManager::SetTransform,
		"SetTactics", &SobGroupManager::SetTactics,
		"SetStrikeGroupFormation", &SobGroupManager::SetStrikeGroupFormation,
		"SetStance", &SobGroupManager::SetStance,
		"SetRotation", &SobGroupManager::SetRotation,
		"SetNoRetaliate", &SobGroupManager::SetNoRetaliate,
		"SetLocation", &SobGroupManager::SetLocation,
		"SetInvincible", &SobGroupManager::SetInvincible,
		"SetIgnoreForPersistentFleet", &SobGroupManager::SetIgnoreForPersistentFleet,
		"SetIgnoreDamage", &SobGroupManager::SetIgnoreDamage,
		"SetHealth", &SobGroupManager::SetHealth,
		"SetGhost", &SobGroupManager::SetGhost,
		"SetCloaking", &SobGroupManager::SetCloaking,
		"SetAutoLaunch", &SobGroupManager::SetAutoLaunch,
		"Scuttle", &SobGroupManager::Scuttle,
		"SalvageCapture", &SobGroupManager::SalvageCapture,
		"RevealInFow", &SobGroupManager::RevealInFow,
		"RetireTo", &SobGroupManager::RetireTo,
		"Retire", &SobGroupManager::Retire,
		"Repair", &SobGroupManager::Repair,
		"RemoveStatusEffectsByHandles", &SobGroupManager::RemoveStatusEffectsByHandles,
		"RemoveStatusEffect", &SobGroupManager::RemoveStatusEffect,
		"RemoveObtainableArtifactFromShips", &SobGroupManager::RemoveObtainableArtifactFromShips,
		"ParadeAround", &SobGroupManager::ParadeAround,
		"OverrideRetaliationSetting", &SobGroupManager::OverrideRetaliationSetting,
		"MoveTo", &SobGroupManager::MoveTo,
		"MovePingPong", &SobGroupManager::MovePingPong,
		"MoveAlong", &SobGroupManager::MoveAlong,
		"MakeDead", &SobGroupManager::MakeDead,
		"LaunchSelf", &SobGroupManager::LaunchSelf,
		"LaunchAll", &SobGroupManager::LaunchAll,
		"LatchInstantly", &SobGroupManager::LatchInstantly,
		"KillUnit", &SobGroupManager::KillUnit,
		"IsWithinPlayerSensorRange", &SobGroupManager::IsWithinPlayerSensorRange,
		"IsInHyperspace", &SobGroupManager::IsInHyperspace,
		"IsGroupInCombat", &SobGroupManager::IsGroupInCombat,
		"IsDeSpawned", &SobGroupManager::IsDeSpawned,
		"IsCloaking", &SobGroupManager::IsCloaking,
		"HyperspaceExit", &SobGroupManager::HyperspaceExit,
		"HyperspaceEnter", &SobGroupManager::HyperspaceEnter,
		"HasStatusEffect", &SobGroupManager::HasStatusEffect,
		"Guard", &SobGroupManager::Guard,
		"GroupRemoveEntity", &SobGroupManager::GroupRemoveEntity,
		"GroupRemove", &SobGroupManager::GroupRemove,
		"GroupPurgeDead", &SobGroupManager::GroupPurgeDead,
		"GroupPurgeAlive", &SobGroupManager::GroupPurgeAlive,
		"GroupMembers", &SobGroupManager::GroupMembers,
		"GroupCountFiltered", &SobGroupManager::GroupCountFiltered,
		"GroupClear", &SobGroupManager::GroupClear,
		"GroupAddEntity", &SobGroupManager::GroupAddEntity,
		"GroupAdd", &SobGroupManager::GroupAdd,
		"GetPosition", &SobGroupManager::GetPosition,
		"GetOrientation", &SobGroupManager::GetOrientation,
		"GenerateDebugString", &SobGroupManager::GenerateDebugString,
		"GatherResource", &SobGroupManager::GatherResource,
		"FireAtNoTarget", &SobGroupManager::FireAtNoTarget,
		"FireAt", &SobGroupManager::FireAt,
		"FillGroupIncludingPlayer", &SobGroupManager::FillGroupIncludingPlayer,
		"FillGroupFromPlayerMothershipList", &SobGroupManager::FillGroupFromPlayerMothershipList,
		"FillGroupFromFilteredFamily", &SobGroupManager::FillGroupFromFilteredFamily,
		"FillGroupExcludingPlayer", &SobGroupManager::FillGroupExcludingPlayer,
		"FillGroupByProximityToLocation", &SobGroupManager::FillGroupByProximityToLocation,
		"FillGroupByProximityToGroup", &SobGroupManager::FillGroupByProximityToGroup,
		"DockInstantly", &SobGroupManager::DockInstantly,
		"Dock", &SobGroupManager::Dock,
		"DisbandStrikeGroup", &SobGroupManager::DisbandStrikeGroup,
		"Despawn", &SobGroupManager::Despawn,
		"DeployTurretAtPositionAndOrientation", &SobGroupManager::DeployTurretAtPositionAndOrientation,
		"DeployTurretAtPositionAndNormal", &SobGroupManager::DeployTurretAtPositionAndNormal,
		"DeployTurret", &SobGroupManager::DeployTurret,
		"CustomCommand", &SobGroupManager::CustomCommand,
		"CountShipTypePresentInGroup", &SobGroupManager::CountShipTypePresentInGroup,
		"CountAttackFamilyPresentInGroup", &SobGroupManager::CountAttackFamilyPresentInGroup,
		"ClearStatusEffects", &SobGroupManager::ClearStatusEffects,
		"ClearRetaliationSetting", &SobGroupManager::ClearRetaliationSetting,
		"ChangeOwner", &SobGroupManager::ChangeOwner,
		"ChangeCommander", &SobGroupManager::ChangeCommander,
		"BindInstantly", &SobGroupManager::BindInstantly,
		"AttackPlayer", &SobGroupManager::AttackPlayer,
		"Attack", &SobGroupManager::Attack,
		"AddStatusEffect", &SobGroupManager::AddStatusEffect,
		"AddObtainableArtifactToShips", &SobGroupManager::AddObtainableArtifactToShips,
		"CreateShipSimple", &SobGroupManager::CreateShipSimple
	);
}

void SobGroupManager::SetGroup(std::string_view name, const TiirEntityGroup& group)
{
	if (const auto found = groups.find(name); found != groups.end())
	{
		found->second = group;
	}
	else
	{
		groups.emplace(name, group);
	}
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

bool SobGroupManager::IsEmptyOrNotExists(std::string_view name) const
{
	if (const auto found = groups.find(name); found != groups.end())
	{
		return found->second.Entities.Num() == 0;
	}
	return true;
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
	bool skip_placement_logic) const
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
	double scale_x, double scale_y, double scale_z, bool skip_placement_logic) const
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
	tarray_desired_types.Reserve(static_cast<std::int32_t>(desired_types.size()));
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

void SobGroupManager::TakeDamageAbsolute(std::string_view group, float damage_absolute) const
{
	lib->TakeDamageAbsolute(FindGroup(group), damage_absolute);
}

void SobGroupManager::TakeDamage(std::string_view group, float damage_percentage) const
{
	lib->TakeDamage(FindGroup(group), damage_percentage);
}

void SobGroupManager::Stop(std::string_view group) const
{
	lib->Stop(FindGroup(group));
}

void SobGroupManager::SetVelocity(std::string_view group, double x, double y, double z) const
{
	lib->SetVelocity(FindGroup(group), RC::Unreal::FVector{ x, y, z });
}

void SobGroupManager::UndeployTurret(std::string_view group, bool instantaneous) const
{
	lib->UndeployTurret(FindGroup(group), instantaneous);
}

void SobGroupManager::ToggleAlternativeShipOrientation(std::string_view group) const
{
	lib->ToggleAlternativeShipOrientation(FindGroup(group));
}

void SobGroupManager::Spawn(std::string_view group, double rotation_w, double rotation_x, double rotation_y,
	double rotation_z, double translation_x, double translation_y, double translation_z, double scale_x, double scale_y,
	double scale_z, bool skip_placement_logic) const
{
	RC::Unreal::FQuat rotation{ rotation_x, rotation_y, rotation_z, rotation_w };
	RC::Unreal::FVector translation{ translation_x, translation_y, translation_z };
	RC::Unreal::FVector scale{ scale_x, scale_y, scale_z };
	lib->Spawn(FindGroup(group), RC::Unreal::FTransform{ rotation, translation, scale }, skip_placement_logic);
}

void SobGroupManager::SetTransform(std::string_view group, double rotation_w, double rotation_x, double rotation_y,
	double rotation_z, double translation_x, double translation_y, double translation_z, double scale_x, double scale_y,
	double scale_z) const
{
	RC::Unreal::FQuat rotation{ rotation_x, rotation_y, rotation_z, rotation_w };
	RC::Unreal::FVector translation{ translation_x, translation_y, translation_z };
	RC::Unreal::FVector scale{ scale_x, scale_y, scale_z };
	lib->SetTransform(FindGroup(group), RC::Unreal::FTransform{ rotation, translation, scale });
}

void SobGroupManager::SetTactics(std::string_view group, SquadronTactics tactics) const
{
	lib->SetTactics(FindGroup(group), tactics);
}

void SobGroupManager::SetStrikeGroupFormation(std::string_view group, std::string_view formation) const
{
	lib->SetStrikeGroupFormation(FindGroup(group), database->GetStrikeGroupFormationData(formation));
}

void SobGroupManager::SetStance(std::string_view group, SquadronStance stance) const
{
	lib->SetStance(FindGroup(group), stance);
}

void SobGroupManager::SetRotation(std::string_view group, double pitch, double yaw, double roll) const
{
	lib->SetRotation(FindGroup(group), RC::Unreal::FRotator{ pitch, yaw, roll });
}

void SobGroupManager::SetNoRetaliate(std::string_view group, bool enabled) const
{
	lib->SetNoRetaliate(FindGroup(group), enabled);
}

void SobGroupManager::SetLocation(std::string_view group, double x, double y, double z) const
{
	lib->SetLocation(FindGroup(group), RC::Unreal::FVector{ x, y, z });
}

void SobGroupManager::SetInvincible(std::string_view group, bool enabled) const
{
	lib->SetInvincible(FindGroup(group), enabled);
}

void SobGroupManager::SetIgnoreForPersistentFleet(std::string_view group, bool enabled) const
{
	lib->SetIgnoreForPersistentFleet(FindGroup(group), enabled);
}

void SobGroupManager::SetIgnoreDamage(std::string_view group, bool enabled) const
{
	lib->SetIgnoreDamage(FindGroup(group), enabled);
}

void SobGroupManager::SetHealth(std::string_view group, float health_percentage) const
{
	lib->SetHealth(FindGroup(group), health_percentage);
}

void SobGroupManager::SetGhost(std::string_view group, bool enabled) const
{
	lib->SetGhost(FindGroup(group), enabled);
}

void SobGroupManager::SetCloaking(std::string_view group, bool enabled) const
{
	lib->SetCloaking(FindGroup(group), enabled);
}

void SobGroupManager::SetAutoLaunch(std::string_view group, AutoLaunchSetting auto_launch_setting) const
{
	lib->SetAutoLaunch(FindGroup(group), auto_launch_setting);
}

void SobGroupManager::Scuttle(std::string_view group) const
{
	lib->Scuttle(FindGroup(group));
}

void SobGroupManager::SalvageCapture(std::string_view group, std::string_view targets) const
{
	lib->SalvageCapture(FindGroup(group), FindGroup(targets));
}

void SobGroupManager::RevealInFow(std::string_view group, bool revealed) const
{
	lib->RevealInFow(FindGroup(group), revealed);
}

void SobGroupManager::RetireTo(const std::string& group, std::uint64_t target_entity_id) const
{
	lib->RetireTo(FindGroup(group), { target_entity_id });
}

void SobGroupManager::Retire(std::string_view group) const
{
	lib->Retire(FindGroup(group));
}

void SobGroupManager::Repair(std::string_view group, std::string_view target_group) const
{
	lib->Repair(FindGroup(group), FindGroup(target_group));
}

void SobGroupManager::RemoveStatusEffectsByHandles(sol::table handles) const
{
	UC::TArray<TiirStatusEffectHandle> tarray_handles;
	tarray_handles.Reserve(static_cast<std::int32_t>(handles.size()));
	for (const auto& kv : handles)
	{
		const auto handle = kv.second.as<TiirStatusEffectHandle>();
		tarray_handles.Add(handle);
	}
	lib->RemoveStatusEffectsByHandles(tarray_handles);
}

void SobGroupManager::RemoveStatusEffect(std::string_view group, std::string_view status) const
{
	lib->RemoveStatusEffect(FindGroup(group), database->GetStatusEffectData(status));
}

void SobGroupManager::RemoveObtainableArtifactFromShips(std::string_view group) const
{
	lib->RemoveObtainableArtifactFromShips(FindGroup(group));
}

void SobGroupManager::ParadeAround(std::string_view group, std::uint64_t parade_around_entity_id,
	ParadeMode parade_mode) const
{
	lib->ParadeAround(FindGroup(group), { parade_around_entity_id }, parade_mode);
}

void SobGroupManager::OverrideRetaliationSetting(std::string_view group,
	RetaliationSetting the_retaliation_setting) const
{
	lib->OverrideRetaliationSetting(FindGroup(group), the_retaliation_setting);
}

void SobGroupManager::MoveTo(std::string_view group, double dest_x, double dest_y, double dest_z,
	bool attack_move) const
{
	lib->MoveTo(FindGroup(group), RC::Unreal::FVector{ dest_x, dest_y, dest_z }, attack_move);
}

void SobGroupManager::MovePingPong(std::string_view group, sol::table locations, bool attack_move) const
{
	UC::TArray<RC::Unreal::FVector> locations_vector;
	for (std::size_t i = 1; i <= locations.size(); i += 3)
	{
		locations_vector.Add({ locations[i], locations[i + 1], locations[i + 2] });
	}
	lib->MovePingPong(FindGroup(group), locations_vector, attack_move);
}

void SobGroupManager::MoveAlong(std::string_view group, sol::table path, bool loop, bool attack_move) const
{
	UC::TArray<RC::Unreal::FVector> path_vector;
	for (std::size_t i = 1; i <= path.size(); i += 3)
	{
		path_vector.Add({ path[i], path[i + 1], path[i + 2] });
	}
	lib->MoveAlong(FindGroup(group), path_vector, loop, attack_move);
}

void SobGroupManager::MakeDead(std::string_view group, const EntityDeathModifiers& death_modifiers) const
{
	lib->MakeDead(FindGroup(group), death_modifiers);
}

void SobGroupManager::LaunchSelf(std::string_view group) const
{
	lib->LaunchSelf(FindGroup(group));
}

void SobGroupManager::LaunchAll(std::string_view group) const
{
	lib->LaunchAll(FindGroup(group));
}

void SobGroupManager::LatchInstantly(std::string_view group, std::string_view latch_target_group) const
{
	lib->LatchInstantly(FindGroup(group), FindGroup(latch_target_group));
}

void SobGroupManager::KillUnit(std::string_view group, bool by_damage) const
{
	lib->KillUnit(FindGroup(group), by_damage);
}

bool SobGroupManager::IsWithinPlayerSensorRange(std::string_view group, std::int32_t target_player) const
{
	return lib->IsWithinPlayerSensorRange(FindGroup(group), target_player);
}

bool SobGroupManager::IsInHyperspace(std::string_view group) const
{
	return lib->IsInHyperspace(FindGroup(group));
}

bool SobGroupManager::IsGroupInCombat(std::string_view group, bool require_everyone) const
{
	return lib->IsGroupInCombat(FindGroup(group), require_everyone);
}

bool SobGroupManager::IsDeSpawned(std::string_view group) const
{
	return lib->IsDeSpawned(FindGroup(group));
}

bool SobGroupManager::IsCloaking(std::string_view group, bool require_all) const
{
	return lib->IsCloaking(FindGroup(group), require_all);
}

void SobGroupManager::HyperspaceExit(std::string_view group, double dest_rotation_w, double dest_rotation_x,
	double dest_rotation_y, double dest_rotation_z, double dest_position_x, double dest_position_y,
	double dest_position_z, double scale_x, double scale_y, double scale_z, bool skip_placement_logic) const
{
	RC::Unreal::FQuat dest_rotation{ dest_rotation_x, dest_rotation_y, dest_rotation_z, dest_rotation_w };
	RC::Unreal::FVector dest_position{ dest_position_x, dest_position_y, dest_position_z };
	RC::Unreal::FVector scale{ scale_x, scale_y, scale_z };
	lib->HyperspaceExit(FindGroup(group), RC::Unreal::FTransform{ dest_rotation, dest_position, scale }, skip_placement_logic);
}

void SobGroupManager::HyperspaceEnter(std::string_view group) const
{
	lib->HyperspaceEnter(FindGroup(group));
}

bool SobGroupManager::HasStatusEffect(std::string_view group, std::string_view status_effect, bool check_for_all) const
{
	return lib->HasStatusEffect(FindGroup(group), database->GetStatusEffectData(status_effect), check_for_all);
}

void SobGroupManager::Guard(std::string_view group, std::string_view targets) const
{
	lib->Guard(FindGroup(group), FindGroup(targets));
}

std::int32_t SobGroupManager::GroupRemoveEntity(std::string_view group, std::uint64_t entity_id)
{
	return lib->GroupRemoveEntity(FindGroup(group), { entity_id });
}

std::int32_t SobGroupManager::GroupRemove(std::string_view group, std::string_view source_group)
{
	return lib->GroupRemove(FindGroup(group), FindGroup(source_group));
}

std::int32_t SobGroupManager::GroupPurgeDead(std::string_view group)
{
	return lib->GroupPurgeDead(FindGroup(group));
}

std::int32_t SobGroupManager::GroupPurgeAlive(std::string_view group)
{
	return lib->GroupPurgeAlive(FindGroup(group));
}

sol::table SobGroupManager::GroupMembers(std::string_view group) const
{
	UC::TArray<TiirEntity> members;
	lib->GroupMembers(FindGroup(group), &members);
	auto table = lua->create_table();
	for (const auto& member : members)
	{
		table.add(member.EntityID);
	}
	return table;
}

std::int32_t SobGroupManager::GroupCountFiltered(std::string_view group, bool awake, bool docked, bool in_hyperspace,
	bool in_combat)
{
	std::uint8_t filter = 0;
	if (awake) { filter |= static_cast<std::uint8_t>(TiirGroupCountFilter::Awake); }
	if (docked) { filter |= static_cast<std::uint8_t>(TiirGroupCountFilter::Docked); }
	if (in_hyperspace) { filter |= static_cast<std::uint8_t>(TiirGroupCountFilter::InHyperspace); }
	if (in_combat) { filter |= static_cast<std::uint8_t>(TiirGroupCountFilter::InCombat); }
	return lib->GroupCountFiltered(FindGroup(group), static_cast<TiirGroupCountFilter>(filter));
}

void SobGroupManager::GroupClear(std::string_view group)
{
	lib->GroupClear(FindGroup(group));
}

std::int32_t SobGroupManager::GroupAddEntity(std::string_view group, std::uint64_t entity_id)
{
	return lib->GroupAddEntity(FindGroup(group), { entity_id });
}

std::int32_t SobGroupManager::GroupAdd(std::string_view group, std::string_view source_group)
{
	return lib->GroupAdd(FindGroup(group), FindGroup(source_group));
}

std::tuple<double, double, double> SobGroupManager::GetPosition(std::string_view group) const
{
	const auto position = lib->GetPosition(FindGroup(group));
	return { position.X(), position.Y(), position.Z()};
}

std::tuple<double, double, double> SobGroupManager::GetOrientation(std::string_view group) const
{
	const auto orientation = lib->GetOrientation(FindGroup(group));
	return { orientation.GetPitch(), orientation.GetYaw(), orientation.GetRoll() };
}

std::string SobGroupManager::GenerateDebugString(std::string_view group) const
{
	auto s = lib->GenerateDebugString(FindGroup(group));
	return boost::nowide::narrow(s.GetCharArray());
}

void SobGroupManager::GatherResource(std::string_view group, std::string_view targets) const
{
	lib->GatherResource(FindGroup(group), FindGroup(targets));
}

bool SobGroupManager::FireAtNoTarget(std::string_view group, std::string_view weapon_type, bool all_sources_fire,
	std::string_view fire_from_socket, double muzzle_offset_x, double muzzle_offset_y, double muzzle_offset_z) const
{
	RC::Unreal::FName socket_name(boost::nowide::widen(fire_from_socket));
	return lib->FireAtNoTarget(FindGroup(group), database->GetWeaponData(weapon_type), all_sources_fire, socket_name,
		{ muzzle_offset_x, muzzle_offset_y, muzzle_offset_z });
}

bool SobGroupManager::FireAt(std::string_view group, std::string_view target_group, std::string_view weapon_type,
	bool all_sources_fire, bool fire_at_all_targets, std::string_view fire_from_socket, double muzzle_offset_x,
	double muzzle_offset_y, double muzzle_offset_z) const
{
	RC::Unreal::FName socket_name(boost::nowide::widen(fire_from_socket));
	return lib->FireAt(FindGroup(group), FindGroup(target_group), database->GetWeaponData(weapon_type), all_sources_fire,
		fire_at_all_targets, socket_name, { muzzle_offset_x, muzzle_offset_y, muzzle_offset_z });
}

std::int32_t SobGroupManager::FillGroupIncludingPlayer(std::string_view group, std::string_view source_group,
	const TiirCommander& owning_player)
{
	return lib->FillGroupIncludingPlayer(FindGroup(group), FindGroup(source_group), owning_player);
}

std::int32_t SobGroupManager::FillGroupFromPlayerMothershipList(std::string_view group, std::int32_t owning_player,
	bool include_dead)
{
	return lib->FillGroupFromPlayerMothershipList(FindGroup(group), owning_player, include_dead);
}

std::int32_t SobGroupManager::FillGroupFromFilteredFamily(std::string_view group, std::string_view source_group,
	sol::table desired_types)
{
	UC::TArray<AttackFamily> tarray_desired_types;
	tarray_desired_types.Reserve(static_cast<std::int32_t>(desired_types.size()));
	for (const auto& kv : desired_types)
	{
		const auto type = kv.second.as<std::string>();
		auto data = database->GetAttackFamily(type);
		tarray_desired_types.Add(data);
	}
	return lib->FillGroupFromFilteredFamily(FindGroup(group), FindGroup(source_group), tarray_desired_types);
}

std::int32_t SobGroupManager::FillGroupExcludingPlayer(std::string_view group, std::string_view source_group,
	std::int32_t excluding_player)
{
	return lib->FillGroupExcludingPlayer(FindGroup(group), FindGroup(source_group), excluding_player);
}

std::int32_t SobGroupManager::FillGroupByProximityToLocation(std::string_view group, std::string_view source_group,
	double location_x, double location_y, double location_z, double distance_x, double distance_y, double distance_z)
{
	return lib->FillGroupByProximityToLocation(FindGroup(group), FindGroup(source_group),
		RC::Unreal::FVector{ location_x, location_y, location_z },
		RC::Unreal::FVector{ distance_x, distance_y, distance_z });
}

std::int32_t SobGroupManager::FillGroupByProximityToGroup(std::string_view group, std::string_view source_group,
	std::string_view near_group, double distance_x, double distance_y, double distance_z)
{
	return lib->FillGroupByProximityToGroup(FindGroup(group), FindGroup(source_group), FindGroup(near_group),
		RC::Unreal::FVector{ distance_x, distance_y, distance_z });
}

void SobGroupManager::DockInstantly(std::string_view group, std::string_view dock_target_entity_group) const
{
	lib->DockInstantly(FindGroup(group), FindGroup(dock_target_entity_group));
}

void SobGroupManager::Dock(std::string_view group, std::string_view dock_target_entity_group, bool stay_docked,
	bool dock_only) const
{
	lib->Dock(FindGroup(group), FindGroup(dock_target_entity_group), stay_docked, dock_only);
}

void SobGroupManager::DisbandStrikeGroup(std::string_view group) const
{
	lib->DisbandStrikeGroup(FindGroup(group));
}

void SobGroupManager::Despawn(std::string_view group, bool ignore_active_commands) const
{
	lib->Despawn(FindGroup(group), ignore_active_commands);
}

void SobGroupManager::DeployTurretAtPositionAndOrientation(std::string_view group, double position_x, double position_y,
	double position_z, double pitch, double yaw, double roll, bool instantaneous) const
{
	lib->DeployTurretAtPositionAndOrientation(FindGroup(group), RC::Unreal::FVector{ position_x, position_y, position_z },
		RC::Unreal::FRotator{ pitch, yaw, roll }, instantaneous);
}

void SobGroupManager::DeployTurretAtPositionAndNormal(std::string_view group, double position_x, double position_y,
                                                      double position_z, double normal_x, double normal_y, double normal_z, bool instantaneous) const
{
	lib->DeployTurretAtPositionAndNormal(FindGroup(group), RC::Unreal::FVector{ position_x, position_y, position_z },
		RC::Unreal::FVector{ normal_x, normal_y, normal_z }, instantaneous);
}

void SobGroupManager::DeployTurret(std::string_view group, bool instantaneous) const
{
	lib->DeployTurret(FindGroup(group), instantaneous);
}

void SobGroupManager::CustomCommand(std::string_view group, std::string_view targets) const
{
	lib->CustomCommand(FindGroup(group), FindGroup(targets));
}

std::int32_t SobGroupManager::CountShipTypePresentInGroup(std::string_view group, sol::table filter_types) const
{
	UC::TArray<ShipStaticData> tarray_filter_types;
	tarray_filter_types.Reserve(static_cast<std::int32_t>(filter_types.size()));
	for (const auto& kv : filter_types)
	{
		const auto type = kv.second.as<std::string>();
		auto data = database->GetShipData(type);
		tarray_filter_types.Add(data);
	}
	return lib->CountShipTypePresentInGroup(FindGroup(group), tarray_filter_types);
}

std::int32_t SobGroupManager::CountAttackFamilyPresentInGroup(std::string_view group, sol::table filter_families) const
{
	UC::TArray<AttackFamily> tarray_filter_families;
	tarray_filter_families.Reserve(static_cast<std::int32_t>(filter_families.size()));
	for (const auto& kv : filter_families)
	{
		const auto type = kv.second.as<std::string>();
		auto data = database->GetAttackFamily(type);
		tarray_filter_families.Add(data);
	}
	return lib->CountAttackFamilyPresentInGroup(FindGroup(group), tarray_filter_families);
}

void SobGroupManager::ClearStatusEffects(std::string_view group) const
{
	lib->ClearStatusEffects(FindGroup(group));
}

void SobGroupManager::ClearRetaliationSetting(std::string_view group) const
{
	lib->ClearRetaliationSetting(FindGroup(group));
}

void SobGroupManager::ChangeOwner(std::string_view group, std::int32_t target_player) const
{
	lib->ChangeOwner(FindGroup(group), target_player);
}

void SobGroupManager::ChangeCommander(std::string_view group, const TiirCommander& new_commander) const
{
	lib->ChangeCommander(FindGroup(group), new_commander);
}

void SobGroupManager::BindInstantly(std::string_view group, std::string_view bind_target_entity_group) const
{
	lib->BindInstantly(FindGroup(group), FindGroup(bind_target_entity_group));
}

void SobGroupManager::AttackPlayer(std::string_view group, std::int32_t target_player,
	bool can_attack_cloaked_units) const
{
	lib->AttackPlayer(FindGroup(group), target_player, can_attack_cloaked_units);
}

void SobGroupManager::Attack(std::string_view group, std::string_view target_group, bool maintain_guard,
	bool can_attack_cloaked_units) const
{
	lib->Attack(FindGroup(group), FindGroup(target_group), maintain_guard, can_attack_cloaked_units);
}

sol::table SobGroupManager::AddStatusEffect(std::string_view group, std::string_view status) const
{
	UC::TArray<TiirStatusEffectHandle> handles;
	lib->AddStatusEffect(FindGroup(group), database->GetStatusEffectData(status), &handles);
	auto table = lua->create_table();
	for (const auto& handle : handles)
	{
		table.add(handle);
	}
	return table;
}

void SobGroupManager::AddObtainableArtifactToShips(std::string_view group, std::string_view artifact_static_data) const
{
	lib->AddObtainableArtifactToShips(FindGroup(group), database->GetArtifactData(artifact_static_data));
}

void SobGroupManager::CreateShipSimple(
	std::string_view group, 
	double x, double y, double z,
	double pitch, double yaw, double roll,
	std::int32_t owning_player, bool start_in_hyperspace,
	bool skip_placement_logic, std::string_view ship_type, std::int32_t ship_count, SquadronStance stance,
	bool use_retaliation_override, RetaliationSetting retaliation_override, bool do_not_retaliate_against_me)
{	
	auto world = RC::Unreal::Cast<Unreal::UWorld>(Unreal::UObjectGlobals::FindFirstOf(STR("World")));
	auto spawner_class = RC::Unreal::UObjectGlobals::StaticFindObject<Unreal::UClass*>(
		nullptr,
		nullptr,
		STR("/Game/Assets/Blueprints/BP_TiirUnitSpawner.BP_TiirUnitSpawner_C"));

	Unreal::FVector position{ x, y, z };
	Unreal::FRotator rotation{ pitch, yaw, roll };
	auto spawner_actor = world->SpawnActor(spawner_class, &position, &rotation);
	TiirShipSpawner spawner = spawner_actor;

	*spawner.GetOwningPlayer() = owning_player;
	*spawner.GetShipType() = database->GetShipData(ship_type);
	*spawner.GetShipCount() = ship_count;
	*spawner.GetStance() = stance;
	*spawner.GetUseRetaliationOverride() = use_retaliation_override;
	*spawner.GetRetaliationOverride() = retaliation_override;
	*spawner.GetDoNotRetaliateAgainstMe() = do_not_retaliate_against_me;

	lib->CreateShip(FindGroup(group), spawner, owning_player, start_in_hyperspace, skip_placement_logic);

	spawner_actor->K2_DestroyActor();
}

TiirEntityGroup& SobGroupManager::FindGroup(std::string_view name)
{
	if (const auto found = groups.find(name); found != groups.end())
	{
		return found->second;
	}
	throw std::runtime_error("SobGroup not found");
}

const TiirEntityGroup& SobGroupManager::FindGroup(std::string_view name) const
{
	if (const auto found = groups.find(name); found != groups.end())
	{
		return found->second;
	}
	throw std::runtime_error("SobGroup not found");
}

void SobGroupManager::SetGroup(std::string_view name, TiirEntityGroup&& group)
{
	if (const auto found = groups.find(name); found != groups.end())
	{
		found->second = std::move(group);
	}
	else
	{
		groups.emplace(name, std::move(group));
	}
}
