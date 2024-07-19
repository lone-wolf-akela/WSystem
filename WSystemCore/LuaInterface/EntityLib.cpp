#include <pch.h>

#include "EntityLib.h"

void EntityLibInterface::BindLuaState(sol::state_view* lua, TiirEntityFunctionLibrary* lib, SobGroupManager* sob_group_manager, Database* database)
{
	this->lua = lua;
	this->lib = lib;
	this->sob_group_manager = sob_group_manager;
	this->database = database;

	lua->new_usertype<EntityLibInterface>("EntityLibInterface",
		"UndeployTurret", &EntityLibInterface::UndeployTurret,
		"Teleport", &EntityLibInterface::Teleport,
		"SetVelocity", &EntityLibInterface::SetVelocity,
		"SetTransform", &EntityLibInterface::SetTransform,
		"SetTactics", &EntityLibInterface::SetTactics,
		"SetStance", &EntityLibInterface::SetStance,
		"SetRotation", &EntityLibInterface::SetRotation,
		"SetNoRetaliate", &EntityLibInterface::SetNoRetaliate,
		"SetMetaDataValue", &EntityLibInterface::SetMetaDataValue,
		"SetLocation", &EntityLibInterface::SetLocation,
		"SetInvincible", &EntityLibInterface::SetInvincible,
		"SetIgnoreForPersistentFleet", &EntityLibInterface::SetIgnoreForPersistentFleet,
		"SetIgnoreDamage", &EntityLibInterface::SetIgnoreDamage,
		"SetGhost", &EntityLibInterface::SetGhost,
		"SetCloaking", &EntityLibInterface::SetCloaking,
		"SetAutoLaunch", &EntityLibInterface::SetAutoLaunch,
		"SetAngularVelocity", &EntityLibInterface::SetAngularVelocity,
		"Scuttle", &EntityLibInterface::Scuttle,
		"SalvageCapture", &EntityLibInterface::SalvageCapture,
		"RevealInFow", &EntityLibInterface::RevealInFow,
		"RetireTo", &EntityLibInterface::RetireTo,
		"Retire", &EntityLibInterface::Retire,
		"Repair", &EntityLibInterface::Repair,
		"RemoveObtainableArtifactFromShip", &EntityLibInterface::RemoveObtainableArtifactFromShip,
		"OverrideRetaliationSetting", &EntityLibInterface::OverrideRetaliationSetting,
		"MovePingPong", &EntityLibInterface::MovePingPong,
		"MoveAlong", &EntityLibInterface::MoveAlong,
		"MakeDead", &EntityLibInterface::MakeDead,
		"LaunchSelf", &EntityLibInterface::LaunchSelf,
		"LaunchAll", &EntityLibInterface::LaunchAll,
		"LatchInstantly", &EntityLibInterface::LatchInstantly,
		"Kamikaze", &EntityLibInterface::Kamikaze,
		"IsValid_OnPres", &EntityLibInterface::IsValid_OnPres,
		"IsValid", &EntityLibInterface::IsValid,
		"IsInHyperspace", &EntityLibInterface::IsInHyperspace,
		"IsInCombat", &EntityLibInterface::IsInCombat,
		"IsCloaking", &EntityLibInterface::IsCloaking,
		"IsBeingCaptured", &EntityLibInterface::IsBeingCaptured,
		"IsBeingAttacked", &EntityLibInterface::IsBeingAttacked,
		"IsAttacking", &EntityLibInterface::IsAttacking,
		"IsAlive", &EntityLibInterface::IsAlive,
		"Guard", &EntityLibInterface::Guard,
		"GetVisualRange", &EntityLibInterface::GetVisualRange,
		"GetSecondarySensorRange", &EntityLibInterface::GetSecondarySensorRange,
		"GetPrimarySensorRange", &EntityLibInterface::GetPrimarySensorRange,
		"GetPosition", &EntityLibInterface::GetPosition,
		"GetOwningPlayer", &EntityLibInterface::GetOwningPlayer,
		"GetOrientation", &EntityLibInterface::GetOrientation,
		"GetNumberOfQueuedOrders", &EntityLibInterface::GetNumberOfQueuedOrders,
		"GetMetaDataValue", &EntityLibInterface::GetMetaDataValue,
		"GetHealthAbsolute", &EntityLibInterface::GetHealthAbsolute,
		"GetHealth", &EntityLibInterface::GetHealth,
		"GetBuildTime", &EntityLibInterface::GetBuildTime,
		"GatherResource", &EntityLibInterface::GatherResource,
		"FindShipType", &EntityLibInterface::FindShipType,
		"DockInstantly", &EntityLibInterface::DockInstantly,
		"Dock", &EntityLibInterface::Dock,
		"DeployTurretAtPositionAndOrientation", &EntityLibInterface::DeployTurretAtPositionAndOrientation,
		"DeployTurretAtPositionAndNormal", &EntityLibInterface::DeployTurretAtPositionAndNormal,
		"DeployTurret", &EntityLibInterface::DeployTurret,
		"CustomCommand", &EntityLibInterface::CustomCommand,
		"ClearStatusEffects", &EntityLibInterface::ClearStatusEffects,
		"ClearRetaliationSetting", &EntityLibInterface::ClearRetaliationSetting,
		"ClearModifiers", &EntityLibInterface::ClearModifiers,
		"ChangeOwner", &EntityLibInterface::ChangeOwner,
		"ChangeCommander", &EntityLibInterface::ChangeCommander,
		"BindInstantly", &EntityLibInterface::BindInstantly,
		"Attack", &EntityLibInterface::Attack,
		"AddOverrideModifier", &EntityLibInterface::AddOverrideModifier,
		"RemoveModifier", &EntityLibInterface::RemoveModifier,
		"AddMultiplierModifier", &EntityLibInterface::AddMultiplierModifier,
		"AddAbilityModifier", &EntityLibInterface::AddAbilityModifier,
		"RemoveStatusEffectByHandle", &EntityLibInterface::RemoveStatusEffectByHandle,
		"RemoveStatusEffect", &EntityLibInterface::RemoveStatusEffect,
		"AddStatusEffect", &EntityLibInterface::AddStatusEffect,
		"AddObtainableArtifactToShip", &EntityLibInterface::AddObtainableArtifactToShip
	);
}

void EntityLibInterface::UndeployTurret(std::uint64_t entity_id, bool instantaneous) const
{
	this->lib->UndeployTurret({ entity_id }, instantaneous);
}

void EntityLibInterface::Teleport(
	std::uint64_t entity_id, 
	double dest_rotation_w, double dest_rotation_x,	double dest_rotation_y, double dest_rotation_z, 
	double dest_position_x, double dest_position_y,	double dest_position_z, 
	double scale_x, double scale_y, double scale_z, 
	bool teleport_ships_in_parade) const
{
	this->lib->Teleport(
		{ entity_id }, 
		{ { dest_rotation_w, dest_rotation_x, dest_rotation_y, dest_rotation_z },
		{ dest_position_x, dest_position_y, dest_position_z },
		{ scale_x, scale_y, scale_z } },
		teleport_ships_in_parade);
}

void EntityLibInterface::SetVelocity(std::uint64_t entity_id, double x, double y, double z) const
{
	this->lib->SetVelocity({ entity_id }, { x, y, z });
}

void EntityLibInterface::SetTransform(
	std::uint64_t entity_id, 
	double rotation_w, double rotation_x, double rotation_y, double rotation_z, 
	double position_x, double position_y, double position_z, 
	double scale_x, double scale_y,	double scale_z) const
{
	this->lib->SetTransform(
		{ entity_id },
		{ { rotation_w, rotation_x, rotation_y, rotation_z },
		{ position_x, position_y, position_z },
		{ scale_x, scale_y, scale_z } });
}

void EntityLibInterface::SetTactics(std::uint64_t entity_id, SquadronTactics tactics) const
{
	this->lib->SetTactics({ entity_id }, tactics);
}

void EntityLibInterface::SetStance(std::uint64_t entity_id, SquadronStance stance) const
{
	this->lib->SetStance({ entity_id }, stance);
}

void EntityLibInterface::SetRotation(std::uint64_t entity_id, double pitch, double yaw, double roll) const
{
	this->lib->SetRotation({ entity_id }, { pitch, yaw, roll });
}

void EntityLibInterface::SetNoRetaliate(std::uint64_t entity_id, bool enabled) const
{
	this->lib->SetNoRetaliate({ entity_id }, enabled);
}

void EntityLibInterface::SetMetaDataValue(std::uint64_t entity_id, std::string_view key, std::int32_t value) const
{
	const RC::Unreal::FString key_fstring(boost::nowide::widen(key).c_str());
	this->lib->SetMetaDataValue({ entity_id }, key_fstring, value);
}

void EntityLibInterface::SetLocation(std::uint64_t entity_id, double x, double y, double z) const
{
	this->lib->SetLocation({ entity_id }, { x, y, z });
}

void EntityLibInterface::SetInvincible(std::uint64_t entity_id, bool enabled) const
{
	this->lib->SetInvincible({ entity_id }, enabled);
}

void EntityLibInterface::SetIgnoreForPersistentFleet(std::uint64_t entity_id, bool enabled) const
{
	this->lib->SetIgnoreForPersistentFleet({ entity_id }, enabled);
}

void EntityLibInterface::SetIgnoreDamage(std::uint64_t entity_id, bool enabled) const
{
	this->lib->SetIgnoreDamage({ entity_id }, enabled);
}

void EntityLibInterface::SetGhost(std::uint64_t entity_id, bool enabled) const
{
	this->lib->SetGhost({ entity_id }, enabled);
}

void EntityLibInterface::SetCloaking(std::uint64_t entity_id, bool enabled) const
{
	this->lib->SetCloaking({ entity_id }, enabled);
}

void EntityLibInterface::SetAutoLaunch(std::uint64_t entity_id, AutoLaunchSetting auto_launch_setting) const
{
	this->lib->SetAutoLaunch({ entity_id }, auto_launch_setting);
}

void EntityLibInterface::SetAngularVelocity(std::uint64_t entity_id, double x, double y, double z) const
{
	this->lib->SetAngularVelocity({ entity_id }, { x, y, z });
}

void EntityLibInterface::Scuttle(std::uint64_t entity_id) const
{
	this->lib->Scuttle({ entity_id });
}

void EntityLibInterface::SalvageCapture(std::uint64_t entity_id, std::string_view target_group) const
{
	const auto targets = sob_group_manager->FindGroup(target_group);
	this->lib->SalvageCapture({ entity_id }, targets);
}

void EntityLibInterface::RevealInFow(std::uint64_t entity_id, bool revealed) const
{
	this->lib->RevealInFow({ entity_id }, revealed);
}

void EntityLibInterface::RetireTo(std::uint64_t entity_id, std::uint64_t target_id) const
{
	this->lib->RetireTo({ entity_id }, { target_id });
}

void EntityLibInterface::Retire(std::uint64_t entity_id) const
{
	this->lib->Retire({ entity_id });
}

void EntityLibInterface::Repair(std::uint64_t entity_id, std::string_view target_group) const
{
	const auto targets = sob_group_manager->FindGroup(target_group);
	this->lib->Repair({ entity_id }, targets);
}

void EntityLibInterface::RemoveObtainableArtifactFromShip(std::uint64_t entity_id) const
{
	this->lib->RemoveObtainableArtifactFromShip({ entity_id });
}

void EntityLibInterface::OverrideRetaliationSetting(std::uint64_t entity_id,
	RetaliationSetting retaliation_setting) const
{
	this->lib->OverrideRetaliationSetting({ entity_id }, retaliation_setting);
}

void EntityLibInterface::MovePingPong(std::uint64_t entity_id, sol::table locations, bool attack_move) const
{
	UC::TArray<RC::Unreal::FVector> locations_vector;
	for (std::size_t i = 1; i <= locations.size(); i += 3)
	{
		locations_vector.Add({ locations[i], locations[i+1], locations[i+2] });
	}
	this->lib->MovePingPong({ entity_id }, locations_vector, attack_move);
}

void EntityLibInterface::MoveAlong(std::uint64_t entity_id, sol::table path, bool loop, bool attack_move) const
{
	UC::TArray<RC::Unreal::FVector> path_vector;
	for (std::size_t i = 1; i <= path.size(); i += 3)
	{
		path_vector.Add({ path[i], path[i+1], path[i+2] });
	}
	this->lib->MoveAlong({ entity_id }, path_vector, loop, attack_move);

}

void EntityLibInterface::MakeDead(std::uint64_t entity_id, bool instant, bool no_aoe_damage, bool no_debris,
	bool no_zombie) const
{
	EntityDeathModifiers death_modifiers;
	death_modifiers.Instant = instant;
	death_modifiers.NoAoeDamage = no_aoe_damage;
	death_modifiers.NoDebris = no_debris;
	death_modifiers.NoZombie = no_zombie;
	this->lib->MakeDead({ entity_id }, death_modifiers);
}

void EntityLibInterface::LaunchSelf(std::uint64_t entity_id) const
{
	this->lib->LaunchSelf({ entity_id });
}

void EntityLibInterface::LaunchAll(std::uint64_t entity_id) const
{
	this->lib->LaunchAll({ entity_id });
}

void EntityLibInterface::LatchInstantly(std::uint64_t entity_id, std::uint64_t latch_target_entity) const
{
	this->lib->LatchInstantly({ entity_id }, { latch_target_entity });
}

void EntityLibInterface::Kamikaze(std::uint64_t entity_id, std::string_view target_group) const
{
	const auto targets = sob_group_manager->FindGroup(target_group);
	this->lib->Kamikaze({ entity_id }, targets);
}

bool EntityLibInterface::IsValid_OnPres(std::uint64_t entity_id) const
{
	return this->lib->IsValid_OnPres({ entity_id });
}

bool EntityLibInterface::IsValid(std::uint64_t entity_id) const
{
	return this->lib->IsValid({ entity_id });
}

bool EntityLibInterface::IsInHyperspace(std::uint64_t entity_id) const
{
	return this->lib->IsInHyperspace({ entity_id });
}

bool EntityLibInterface::IsInCombat(std::uint64_t entity_id) const
{
	return this->lib->IsInCombat({ entity_id });
}

bool EntityLibInterface::IsCloaking(std::uint64_t entity_id) const
{
	return this->lib->IsCloaking({ entity_id });
}

bool EntityLibInterface::IsBeingCaptured(std::uint64_t entity_id) const
{
	return this->lib->IsBeingCaptured({ entity_id });
}

bool EntityLibInterface::IsBeingAttacked(std::uint64_t entity_id) const
{
	return this->lib->IsBeingAttacked({ entity_id });
}

bool EntityLibInterface::IsAttacking(std::uint64_t entity_id) const
{
	return this->lib->IsAttacking({ entity_id });
}

bool EntityLibInterface::IsAlive(std::uint64_t entity_id) const
{
	return this->lib->IsAlive({ entity_id });
}

void EntityLibInterface::Guard(std::uint64_t entity_id, std::string_view target_group) const
{
	const auto targets = sob_group_manager->FindGroup(target_group);
	this->lib->Guard({ entity_id }, targets);
}

float EntityLibInterface::GetVisualRange(std::uint64_t entity_id) const
{
	return this->lib->GetVisualRange({ entity_id });
}

float EntityLibInterface::GetSecondarySensorRange(std::uint64_t entity_id) const
{
	return this->lib->GetSecondarySensorRange({ entity_id });
}

float EntityLibInterface::GetPrimarySensorRange(std::uint64_t entity_id) const
{
	return this->lib->GetPrimarySensorRange({ entity_id });
}

std::tuple<double, double, double> EntityLibInterface::GetPosition(std::uint64_t entity_id) const
{
	const auto position = this->lib->GetPosition({ entity_id });
	return { position.X(), position.Y(), position.Z()};
}

TiirCommander EntityLibInterface::GetOwningPlayer(std::uint64_t entity_id) const
{
	return this->lib->GetOwningPlayer({ entity_id });
}

std::tuple<double, double, double> EntityLibInterface::GetOrientation(std::uint64_t entity_id) const
{
	const auto orientation = this->lib->GetOrientation({ entity_id });
	return { orientation.GetPitch(), orientation.GetYaw(), orientation.GetRoll()};
}

std::int32_t EntityLibInterface::GetNumberOfQueuedOrders(std::uint64_t entity_id) const
{
	return this->lib->GetNumberOfQueuedOrders({ entity_id });
}

std::tuple<bool, std::int32_t> EntityLibInterface::GetMetaDataValue(std::uint64_t entity_id, std::string_view key) const
{
	std::int32_t data;
	const RC::Unreal::FString key_fstring(boost::nowide::widen(key).c_str());
	const auto result = this->lib->GetMetaDataValue({ entity_id }, key_fstring, &data);
	return { result, data };
}

float EntityLibInterface::GetHealthAbsolute(std::uint64_t entity_id) const
{
	return this->lib->GetHealthAbsolute({ entity_id });
}

float EntityLibInterface::GetHealth(std::uint64_t entity_id) const
{
	return this->lib->GetHealth({ entity_id });
}

std::int32_t EntityLibInterface::GetBuildTime(std::uint64_t entity_id) const
{
	return this->lib->GetBuildTime({ entity_id });
}

void EntityLibInterface::GatherResource(std::uint64_t entity_id, std::string_view target_group) const
{
	const auto targets = sob_group_manager->FindGroup(target_group);
	this->lib->GatherResource({ entity_id }, targets);
}

std::string EntityLibInterface::FindShipType(std::uint64_t entity_id) const
{
	auto data = this->lib->FindShipStaticData({ entity_id });
	return boost::nowide::narrow(data->GetName());
}

void EntityLibInterface::DockInstantly(std::uint64_t entity_id, std::uint64_t dock_target_entity) const
{
	this->lib->DockInstantly({ entity_id }, { dock_target_entity });
}

void EntityLibInterface::Dock(std::uint64_t entity_id, std::uint64_t dock_target_entity, bool stay_docked,
	bool dock_only) const
{
	this->lib->Dock({ entity_id }, { dock_target_entity }, stay_docked, dock_only);
}

void EntityLibInterface::DeployTurretAtPositionAndOrientation(std::uint64_t entity_id, double x, double y, double z,
	double pitch, double yaw, double roll, bool instantaneous) const
{
	this->lib->DeployTurretAtPositionAndOrientation(
		{ entity_id },
		{ x, y, z },
		{ pitch, yaw, roll },
		instantaneous);
}

void EntityLibInterface::DeployTurretAtPositionAndNormal(std::uint64_t entity_id, double position_x, double position_y,
	double position_z, double normal_x, double normal_y, double normal_z, bool instantaneous) const
{
	this->lib->DeployTurretAtPositionAndNormal(
		{ entity_id },
		{ position_x, position_y, position_z },
		{ normal_x, normal_y, normal_z },
		instantaneous);
}

void EntityLibInterface::DeployTurret(std::uint64_t entity_id, bool instantaneous) const
{
	this->lib->DeployTurret({ entity_id }, instantaneous);
}

void EntityLibInterface::CustomCommand(std::uint64_t entity_id, std::string_view target_group) const
{
	const auto targets = sob_group_manager->FindGroup(target_group);
	this->lib->CustomCommand({ entity_id }, targets);
}

bool EntityLibInterface::ClearStatusEffects(std::uint64_t entity_id) const
{
	return this->lib->ClearStatusEffects({ entity_id });
}

void EntityLibInterface::ClearRetaliationSetting(std::uint64_t entity_id) const
{
	this->lib->ClearRetaliationSetting({ entity_id });
}

bool EntityLibInterface::ClearModifiers(std::uint64_t entity_id) const
{
	return this->lib->ClearModifiers({ entity_id });
}

void EntityLibInterface::ChangeOwner(std::uint64_t entity_id, std::int32_t target_player) const
{
	this->lib->ChangeOwner({ entity_id }, target_player);
}

void EntityLibInterface::ChangeCommander(std::uint64_t entity_id, const TiirCommander& new_commander) const
{
	this->lib->ChangeCommander({ entity_id }, new_commander);
}

void EntityLibInterface::BindInstantly(std::uint64_t entity_id, std::uint64_t bind_target_entity) const
{
	this->lib->BindInstantly({ entity_id }, { bind_target_entity });
}

void EntityLibInterface::Attack(std::uint64_t entity_id, std::string_view target_group, bool maintain_guard) const
{
	const auto targets = sob_group_manager->FindGroup(target_group);
	this->lib->Attack({ entity_id }, targets, maintain_guard);
}

TiirModifierHandle EntityLibInterface::AddOverrideModifier(std::uint64_t entity_id, SobPropertyType property,
	float value, InfluenceType influence_type, float influence_radius) const
{
	return this->lib->AddOverrideModifier({ entity_id }, property, value, influence_type, influence_radius);
}

bool EntityLibInterface::RemoveModifier(const TiirModifierHandle& modifier) const
{
	return this->lib->RemoveModifier(modifier);
}

TiirModifierHandle EntityLibInterface::AddMultiplierModifier(std::uint64_t entity_id, MultiplierType multiplier,
	float multiplier_value, InfluenceType influence_type, float influence_radius,
	ActivityRelation multiplier_value_relation, float multiplier_interp_min_value) const
{
	return this->lib->AddMultiplierModifier(
		{ entity_id },
		multiplier,
		multiplier_value,
		influence_type,
		influence_radius,
		multiplier_value_relation,
		multiplier_interp_min_value);
}

TiirModifierHandle EntityLibInterface::AddAbilityModifier(std::uint64_t entity_id, AbilityType ability,
	bool ability_state, InfluenceType influence_type, float influence_radius) const
{
	return this->lib->AddAbilityModifier(
		{ entity_id },
		ability,
		ability_state,
		influence_type,
		influence_radius);
}

bool EntityLibInterface::RemoveStatusEffectByHandle(const TiirStatusEffectHandle& handle) const
{
	return this->lib->RemoveStatusEffectByHandle(handle);
}

bool EntityLibInterface::RemoveStatusEffect(std::uint64_t entity_id, std::string_view status) const
{
	const auto status_data = database->GetStatusEffectData(status);
	return this->lib->RemoveStatusEffect({ entity_id }, status_data);
}

TiirStatusEffectHandle EntityLibInterface::AddStatusEffect(std::uint64_t entity_id,
	std::string_view status_effect) const
{
	const auto status_data = database->GetStatusEffectData(status_effect);
	return this->lib->AddStatusEffect({ entity_id }, status_data);
}

void EntityLibInterface::AddObtainableArtifactToShip(std::uint64_t entity_id,
	std::string_view artifact_static_data) const
{
	const auto artifact_data = database->GetArtifactData(artifact_static_data);
	this->lib->AddObtainableArtifactToShip({ entity_id }, artifact_data);
}
