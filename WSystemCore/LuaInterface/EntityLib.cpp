#include <pch.h>

#include <DataWrapper/UnitsInfoSubsystem.h>

#include "LuaInterface.h"
#include "SobGroupLib.h"
#include "EntityIdManager.h"
#include "EntityLib.h"

void EntityLibInterface::Initialize(sol::state_view* lua, TiirEntityFunctionLibrary* lib, SobGroupManager* sob_group_manager, Database* database, EntityIdManager* entity_id_manager)
{
	this->lua = lua;
	this->lib = lib;
	this->sob_group_manager = sob_group_manager;
	this->database = database;
	this->entity_id_manager = entity_id_manager;

	auto EntityLibType = lua->new_usertype<EntityLibInterface>("EntityLibInterface");
	EntityLibType["UndeployTurret"] = &EntityLibInterface::UndeployTurret;
	EntityLibType["Teleport"] = &EntityLibInterface::Teleport;
	EntityLibType["SetVelocity"] = &EntityLibInterface::SetVelocity;
	EntityLibType["SetTransform"] = &EntityLibInterface::SetTransform;
	EntityLibType["SetTactics"] = &EntityLibInterface::SetTactics;
	EntityLibType["SetStance"] = &EntityLibInterface::SetStance;
	EntityLibType["SetRotation"] = &EntityLibInterface::SetRotation;
	EntityLibType["SetNoRetaliate"] = &EntityLibInterface::SetNoRetaliate;
	EntityLibType["SetMetaDataValue"] = &EntityLibInterface::SetMetaDataValue;
	EntityLibType["SetLocation"] = &EntityLibInterface::SetLocation;
	EntityLibType["SetInvincible"] = &EntityLibInterface::SetInvincible;
	EntityLibType["SetIgnoreForPersistentFleet"] = &EntityLibInterface::SetIgnoreForPersistentFleet;
	EntityLibType["SetIgnoreDamage"] = &EntityLibInterface::SetIgnoreDamage;
	EntityLibType["SetGhost"] = &EntityLibInterface::SetGhost;
	EntityLibType["SetCloaking"] = &EntityLibInterface::SetCloaking;
	EntityLibType["SetAutoLaunch"] = &EntityLibInterface::SetAutoLaunch;
	EntityLibType["SetAngularVelocity"] = &EntityLibInterface::SetAngularVelocity;
	EntityLibType["Scuttle"] = &EntityLibInterface::Scuttle;
	EntityLibType["SalvageCapture"] = &EntityLibInterface::SalvageCapture;
	EntityLibType["RevealInFow"] = &EntityLibInterface::RevealInFow;
	EntityLibType["RetireTo"] = &EntityLibInterface::RetireTo;
	EntityLibType["Retire"] = &EntityLibInterface::Retire;
	EntityLibType["Repair"] = &EntityLibInterface::Repair;
	EntityLibType["RemoveObtainableArtifactFromShip"] = &EntityLibInterface::RemoveObtainableArtifactFromShip;
	EntityLibType["OverrideRetaliationSetting"] = &EntityLibInterface::OverrideRetaliationSetting;
	EntityLibType["MovePingPong"] = &EntityLibInterface::MovePingPong;
	EntityLibType["MoveAlong"] = &EntityLibInterface::MoveAlong;
	EntityLibType["MakeDead"] = &EntityLibInterface::MakeDead;
	EntityLibType["LaunchSelf"] = &EntityLibInterface::LaunchSelf;
	EntityLibType["LaunchAll"] = &EntityLibInterface::LaunchAll;
	EntityLibType["LatchInstantly"] = &EntityLibInterface::LatchInstantly;
	EntityLibType["Kamikaze"] = &EntityLibInterface::Kamikaze;
	EntityLibType["IsValid_OnPres"] = &EntityLibInterface::IsValid_OnPres;
	EntityLibType["IsValid"] = &EntityLibInterface::IsValid;
	EntityLibType["IsInHyperspace"] = &EntityLibInterface::IsInHyperspace;
	EntityLibType["IsInCombat"] = &EntityLibInterface::IsInCombat;
	EntityLibType["IsCloaking"] = &EntityLibInterface::IsCloaking;
	EntityLibType["IsBeingCaptured"] = &EntityLibInterface::IsBeingCaptured;
	EntityLibType["IsBeingAttacked"] = &EntityLibInterface::IsBeingAttacked;
	EntityLibType["IsAttacking"] = &EntityLibInterface::IsAttacking;
	EntityLibType["IsAlive"] = &EntityLibInterface::IsAlive;
	EntityLibType["Guard"] = &EntityLibInterface::Guard;
	EntityLibType["GetVisualRange"] = &EntityLibInterface::GetVisualRange;
	EntityLibType["GetSecondarySensorRange"] = &EntityLibInterface::GetSecondarySensorRange;
	EntityLibType["GetPrimarySensorRange"] = &EntityLibInterface::GetPrimarySensorRange;
	EntityLibType["GetPosition"] = &EntityLibInterface::GetPosition;
	EntityLibType["GetOwningPlayer"] = &EntityLibInterface::GetOwningPlayer;
	EntityLibType["GetOrientation"] = &EntityLibInterface::GetOrientation;
	EntityLibType["GetNumberOfQueuedOrders"] = &EntityLibInterface::GetNumberOfQueuedOrders;
	EntityLibType["GetMetaDataValue"] = &EntityLibInterface::GetMetaDataValue;
	EntityLibType["GetHealthAbsolute"] = &EntityLibInterface::GetHealthAbsolute;
	EntityLibType["GetHealth"] = &EntityLibInterface::GetHealth;
	EntityLibType["GetBuildTime"] = &EntityLibInterface::GetBuildTime;
	EntityLibType["GatherResource"] = &EntityLibInterface::GatherResource;
	EntityLibType["FindShipType"] = &EntityLibInterface::FindShipType;
	EntityLibType["DockInstantly"] = &EntityLibInterface::DockInstantly;
	EntityLibType["Dock"] = &EntityLibInterface::Dock;
	EntityLibType["DeployTurretAtPositionAndOrientation"] = &EntityLibInterface::DeployTurretAtPositionAndOrientation;
	EntityLibType["DeployTurretAtPositionAndNormal"] = &EntityLibInterface::DeployTurretAtPositionAndNormal;
	EntityLibType["DeployTurret"] = &EntityLibInterface::DeployTurret;
	EntityLibType["CustomCommand"] = &EntityLibInterface::CustomCommand;
	EntityLibType["ClearStatusEffects"] = &EntityLibInterface::ClearStatusEffects;
	EntityLibType["ClearRetaliationSetting"] = &EntityLibInterface::ClearRetaliationSetting;
	EntityLibType["ClearModifiers"] = &EntityLibInterface::ClearModifiers;
	EntityLibType["ChangeOwner"] = &EntityLibInterface::ChangeOwner;
	EntityLibType["ChangeCommander"] = &EntityLibInterface::ChangeCommander;
	EntityLibType["BindInstantly"] = &EntityLibInterface::BindInstantly;
	EntityLibType["Attack"] = &EntityLibInterface::Attack;
	EntityLibType["AddOverrideModifier"] = &EntityLibInterface::AddOverrideModifier;
	EntityLibType["RemoveModifier"] = &EntityLibInterface::RemoveModifier;
	EntityLibType["AddMultiplierModifier"] = &EntityLibInterface::AddMultiplierModifier;
	EntityLibType["AddAbilityModifier"] = &EntityLibInterface::AddAbilityModifier;
	EntityLibType["RemoveStatusEffectByHandle"] = &EntityLibInterface::RemoveStatusEffectByHandle;
	EntityLibType["RemoveStatusEffect"] = &EntityLibInterface::RemoveStatusEffect;
	EntityLibType["AddStatusEffect"] = &EntityLibInterface::AddStatusEffect;
	EntityLibType["AddObtainableArtifactToShip"] = &EntityLibInterface::AddObtainableArtifactToShip;
	EntityLibType["IsShip"] = &EntityLibInterface::IsShip;
	EntityLibType["IsMilitary"] = &EntityLibInterface::IsMilitary;
	EntityLibType["IsDamaged"] = &EntityLibInterface::IsDamaged;
	EntityLibType["IsAliveAndVisibleEntity"] = &EntityLibInterface::IsAliveAndVisibleEntity;
	EntityLibType["CanHeal"] = &EntityLibInterface::CanHeal;
	EntityLibType["CanBeFocused"] = &EntityLibInterface::CanBeFocused;
	EntityLibType["IsResource"] = &EntityLibInterface::IsResource;
	EntityLibType["IsMissile"] = &EntityLibInterface::IsMissile;
	EntityLibType["GetEntityInternalName"] = &EntityLibInterface::GetEntityInternalName;
	EntityLibType["GetStance"] = &EntityLibInterface::GetStance;
	EntityLibType["GetFormation"] = &EntityLibInterface::GetFormation;
	EntityLibType["IsNis"] = &EntityLibInterface::IsNis;
	EntityLibType["GetShipScreenSize"] = &EntityLibInterface::GetShipScreenSize;
	EntityLibType["GetShipNormalizedScreenSize"] = &EntityLibInterface::GetShipNormalizedScreenSize;
	EntityLibType["GetShipAudioSignificance"] = &EntityLibInterface::GetShipAudioSignificance;
	EntityLibType["GetSquadronID"] = &EntityLibInterface::GetSquadronID;
	EntityLibType["IsSquadronLeader"] = &EntityLibInterface::IsSquadronLeader;
	EntityLibType["GetSquadronLeader"] = &EntityLibInterface::GetSquadronLeader;
	EntityLibType["GetPilotName"] = &EntityLibInterface::GetPilotName;
	EntityLibType["GetLocalizedUnitName"] = &EntityLibInterface::GetLocalizedUnitName;
	EntityLibType["GetLocalizedUnitDescription"] = &EntityLibInterface::GetLocalizedUnitDescription;
	EntityLibType["GetLocalizedUnitFlavourText"] = &EntityLibInterface::GetLocalizedUnitFlavourText;
	EntityLibType["GetCreationMap"] = &EntityLibInterface::GetCreationMap;
	EntityLibType["GetAudioFocusWeight"] = &EntityLibInterface::GetAudioFocusWeight;
	EntityLibType["GetAudioFocusWeightContextualMultiplier"] = &EntityLibInterface::GetAudioFocusWeightContextualMultiplier;
	EntityLibType["GetAudioFocusRank"] = &EntityLibInterface::GetAudioFocusRank;
	EntityLibType["GetAudioFocusRankNormalized"] = &EntityLibInterface::GetAudioFocusRankNormalized;
	EntityLibType["GetControlGroupsFlags"] = &EntityLibInterface::GetControlGroupsFlags;
	EntityLibType["IsCenterFocused"] = &EntityLibInterface::IsCenterFocused;
	EntityLibType["GetDeployState"] = &EntityLibInterface::GetDeployState;
	EntityLibType["GetDeployLocation"] = &EntityLibInterface::GetDeployLocation;
	EntityLibType["GetDeployNormal"] = &EntityLibInterface::GetDeployNormal;
	EntityLibType["IsDeployedInTacticalPause"] = &EntityLibInterface::IsDeployedInTacticalPause;
	EntityLibType["IsLatched"] = &EntityLibInterface::IsLatched;
	EntityLibType["GetWeaponRange"] = &EntityLibInterface::GetWeaponRange;
	EntityLibType["GetSpecialWeaponRange"] = &EntityLibInterface::GetSpecialWeaponRange;
	EntityLibType["GetHealWeaponRange"] = &EntityLibInterface::GetHealWeaponRange;
	EntityLibType["GetHealSpecialWeaponRange"] = &EntityLibInterface::GetHealSpecialWeaponRange;
	EntityLibType["GetHyperspaceProgress"] = &EntityLibInterface::GetHyperspaceProgress;
	EntityLibType["GetOpposingShip"] = &EntityLibInterface::GetOpposingShip;
	EntityLibType["GetZombieTime"] = &EntityLibInterface::GetZombieTime;
	EntityLibType["GetDeathModifiers"] = &EntityLibInterface::GetDeathModifiers;
	EntityLibType["GetSignificance"] = &EntityLibInterface::GetSignificance;
	EntityLibType["GetDistanceToCamera"] = &EntityLibInterface::GetDistanceToCamera;
	EntityLibType["GetBackstageEffectiveness"] = &EntityLibInterface::GetBackstageEffectiveness;
	EntityLibType["GetDockWith"] = &EntityLibInterface::GetDockWith;
	EntityLibType["GetDockingStage"] = &EntityLibInterface::GetDockingStage;
	EntityLibType["IsDocked"] = &EntityLibInterface::IsDocked;
	EntityLibType["IsDocking"] = &EntityLibInterface::IsDocking;
	EntityLibType["HasPower"] = &EntityLibInterface::HasPower;
	EntityLibType["IsHandlingExternalMove"] = &EntityLibInterface::IsHandlingExternalMove;
	EntityLibType["CanRally"] = &EntityLibInterface::CanRally;
	EntityLibType["GetHyperspaceStatus"] = &EntityLibInterface::GetHyperspaceStatus;
	EntityLibType["GetParent"] = &EntityLibInterface::GetParent;
	EntityLibType["GetCollectors"] = &EntityLibInterface::GetCollectors;
	EntityLibType["GetAnimationStates"] = &EntityLibInterface::GetAnimationStates;
	EntityLibType["GetActiveCommandType"] = &EntityLibInterface::GetActiveCommandType;
	EntityLibType["GetShipVelocity"] = &EntityLibInterface::GetShipVelocity;
	EntityLibType["IsMovableEntity"] = &EntityLibInterface::IsMovableEntity;
	EntityLibType["IsWeaponFireActor"] = &EntityLibInterface::IsWeaponFireActor;
	EntityLibType["IsRavenSimProjectile"] = &EntityLibInterface::IsRavenSimProjectile;
	EntityLibType["IsProjectile"] = &EntityLibInterface::IsProjectile;
	EntityLibType["SetAnimationState"] = &EntityLibInterface::SetAnimationState;
}

void EntityLibInterface::Begin_InitScenario(UnitsInfoSubsystem units_info_subsystem)
{
	this->units_info_subsystem = units_info_subsystem;
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

void EntityLibInterface::SetTactics(std::uint64_t entity_id, ESquadronTactics tactics) const
{
	this->lib->SetTactics({ entity_id }, tactics);
}

void EntityLibInterface::SetStance(std::uint64_t entity_id, ESquadronStance stance) const
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

void EntityLibInterface::SetAutoLaunch(std::uint64_t entity_id, EAutoLaunchSetting auto_launch_setting) const
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
	const auto& targets = sob_group_manager->FindGroup(target_group);
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
	const auto& targets = sob_group_manager->FindGroup(target_group);
	this->lib->Repair({ entity_id }, targets);
}

void EntityLibInterface::RemoveObtainableArtifactFromShip(std::uint64_t entity_id) const
{
	this->lib->RemoveObtainableArtifactFromShip({ entity_id });
}

void EntityLibInterface::OverrideRetaliationSetting(std::uint64_t entity_id,
	ERetaliationSetting retaliation_setting) const
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
	const EntityDeathModifiers death_modifiers{
		.Instant = instant,
		.NoAoeDamage = no_aoe_damage,
		.NoDebris = no_debris,
		.NoZombie = no_zombie
	};
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
	const auto& targets = sob_group_manager->FindGroup(target_group);
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
	const auto& targets = sob_group_manager->FindGroup(target_group);
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
	const Unreal::FString key_fstring(boost::nowide::widen(key).c_str());
	const auto result = this->lib->GetMetaDataValue({ entity_id }, key_fstring, data);
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
	const auto& targets = sob_group_manager->FindGroup(target_group);
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
	const auto& targets = sob_group_manager->FindGroup(target_group);
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
	const auto& targets = sob_group_manager->FindGroup(target_group);
	this->lib->Attack({ entity_id }, targets, maintain_guard);
}

TiirModifierHandle EntityLibInterface::AddOverrideModifier(std::uint64_t entity_id, ESobPropertyType property,
	float value, EInfluenceType influence_type, float influence_radius) const
{
	return this->lib->AddOverrideModifier({ entity_id }, property, value, influence_type, influence_radius);
}

bool EntityLibInterface::RemoveModifier(const TiirModifierHandle& modifier) const
{
	return this->lib->RemoveModifier(modifier);
}

TiirModifierHandle EntityLibInterface::AddMultiplierModifier(std::uint64_t entity_id, EMultiplierType multiplier,
	float multiplier_value, EInfluenceType influence_type, float influence_radius,
	EActivityRelation multiplier_value_relation, float multiplier_interp_min_value) const
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

TiirModifierHandle EntityLibInterface::AddAbilityModifier(std::uint64_t entity_id, EAbilityType ability,
	bool ability_state, EInfluenceType influence_type, float influence_radius) const
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

namespace 
{
	ASimEntity find_check_entity(const EntityIdManager* id_manager, std::uint64_t entity_id)
	{
		const auto entity = id_manager->FindEntity(entity_id);
		if (!entity.IsValid())
		{
			const auto err_msg = std::format("Entity with id {} not found\n", entity_id);
			throw std::runtime_error(err_msg);
		}
		return entity;
	}
}

bool EntityLibInterface::IsShip(std::uint64_t entity_id) const
{
	const auto entity = find_check_entity(entity_id_manager, entity_id);
	return entity.IsShip();
}

bool EntityLibInterface::IsMilitary(std::uint64_t entity_id) const
{
	const auto entity = find_check_entity(entity_id_manager, entity_id);
	return entity.IsMilitary();
}

bool EntityLibInterface::IsDamaged(std::uint64_t entity_id) const
{
	const auto entity = find_check_entity(entity_id_manager, entity_id);
	return entity.IsDamaged();
}

bool EntityLibInterface::IsAliveAndVisibleEntity(std::uint64_t entity_id) const
{
	const auto entity = find_check_entity(entity_id_manager, entity_id);
	return entity.IsAliveAndVisibleEntity();
}

bool EntityLibInterface::CanHeal(std::uint64_t entity_id) const
{
	const auto entity = find_check_entity(entity_id_manager, entity_id);
	return entity.CanHeal();
}

bool EntityLibInterface::CanBeFocused(std::uint64_t entity_id) const
{
	const auto entity = find_check_entity(entity_id_manager, entity_id);
	return entity.CanBeFocused();
}

bool EntityLibInterface::IsResource(std::uint64_t entity_id) const
{
	const auto entity = find_check_entity(entity_id_manager, entity_id);
	return entity.IsResource();
}

bool EntityLibInterface::IsMissile(std::uint64_t entity_id) const
{
	const auto entity = find_check_entity(entity_id_manager, entity_id);
	return entity.IsMissile();
}

std::string EntityLibInterface::GetEntityInternalName(std::uint64_t entity_id) const
{
	const auto entity = find_check_entity(entity_id_manager, entity_id);
	return boost::nowide::narrow(entity->GetName());
}

namespace
{
	ASimShip find_check_ship(const EntityIdManager* id_manager, std::uint64_t entity_id)
	{
		const auto entity = find_check_entity(id_manager, entity_id);
		if (!entity.IsShip())
		{
			const auto err_msg = std::format("Entity with id {} is not a ship\n", entity_id);
			throw std::runtime_error(err_msg);
		}
		return entity.obj;
	}
}

ESquadronStance EntityLibInterface::GetStance(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);

	UC::TArray<ASimShip> ships;
	ships.Add(ship);
	bool single_formation;
	UUnitOrderStaticData formation_order;
	std::int32_t formation_order_index;
	bool single_stance;
	std::int32_t stance_order_index;
	UUnitOrderStaticData stance_order;
	units_info_subsystem.GetShipsFormationAndStance(
		ships,
		single_formation, formation_order_index, formation_order,
		single_stance, stance_order_index, stance_order);
	return stance_order.SquadronStance;
}

std::string EntityLibInterface::GetFormation(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);

	UC::TArray<ASimShip> ships;
	ships.Add(ship);
	bool single_formation;
	UUnitOrderStaticData formation_order;
	std::int32_t formation_order_index;
	bool single_stance;
	std::int32_t stance_order_index;
	UUnitOrderStaticData stance_order;
	units_info_subsystem.GetShipsFormationAndStance(
		ships, 
		single_formation, formation_order_index, formation_order,
		single_stance, stance_order_index, stance_order);
	return boost::nowide::narrow(formation_order.StrikeGroupFormationData->GetName());
}

bool EntityLibInterface::IsNis(std::uint64_t entity_id) const
{
	const auto entity = find_check_entity(entity_id_manager, entity_id);
	return entity.bIsNis;
}

float EntityLibInterface::GetShipScreenSize(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.ShipScreenSize;
}

float EntityLibInterface::GetShipNormalizedScreenSize(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.ShipNormalizedScreenSize;
}

float EntityLibInterface::GetShipAudioSignificance(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.ShipAudioSignificance;
}

std::int32_t EntityLibInterface::GetSquadronID(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.SquadronID;
}

bool EntityLibInterface::IsSquadronLeader(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.IsSquadronLeader;
}

std::uint64_t EntityLibInterface::GetSquadronLeader(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	if (const auto& leader = ship.SquadronLeader; leader.IsValid())
	{
		return leader.SimID;
	}
	return 0;
}

std::string EntityLibInterface::GetPilotName(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return boost::nowide::narrow(ship.PilotName.ToString());
}

std::string EntityLibInterface::GetLocalizedUnitName(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	const auto& ship_static_data = ship.DataAsset;
	return boost::nowide::narrow(ship_static_data.UnitName.ToString());
}

std::string EntityLibInterface::GetLocalizedUnitDescription(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	const auto& ship_static_data = ship.DataAsset;
	return boost::nowide::narrow(ship_static_data.UnitDescription.ToString());
}

std::string EntityLibInterface::GetLocalizedUnitFlavourText(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	const auto& ship_static_data = ship.DataAsset;
	return boost::nowide::narrow(ship_static_data.UnitFlavourText.ToString());
}

std::string EntityLibInterface::GetCreationMap(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return boost::nowide::narrow(ship.CreationMap.GetCharArray());
}

float EntityLibInterface::GetAudioFocusWeight(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.AudioFocusWeight;
}

float EntityLibInterface::GetAudioFocusWeightContextualMultiplier(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.AudioFocusWeightContextualMultiplier;
}

std::int32_t EntityLibInterface::GetAudioFocusRank(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.AudioFocusRank;
}

float EntityLibInterface::GetAudioFocusRankNormalized(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.AudioFocusRankNormalized;
}

std::int32_t EntityLibInterface::GetControlGroupsFlags(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.ControlGroupsFlags;
}

bool EntityLibInterface::IsCenterFocused(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.IsCenterFocused;
}

ETurretDeploymentState EntityLibInterface::GetDeployState(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.DeployState;
}

std::tuple<double, double, double> EntityLibInterface::GetDeployLocation(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	const auto& location = ship.DeployLocation;
	return { location.X(), location.Y(), location.Z() };
}

std::tuple<double, double, double> EntityLibInterface::GetDeployNormal(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	const auto& normal = ship.DeployNormal;
	return { normal.X(), normal.Y(), normal.Z() };
}

bool EntityLibInterface::IsDeployedInTacticalPause(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.bDeployedInTacticalPause;
}

bool EntityLibInterface::IsLatched(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.IsLatched;
}

float EntityLibInterface::GetWeaponRange(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.WeaponRange;
}

float EntityLibInterface::GetSpecialWeaponRange(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.SpecialWeaponRange;
}

float EntityLibInterface::GetHealWeaponRange(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.HealWeaponRange;
}

float EntityLibInterface::GetHealSpecialWeaponRange(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.HealSpecialWeaponRange;
}

float EntityLibInterface::GetHyperspaceProgress(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.HyperspaceProgress;
}

std::uint64_t EntityLibInterface::GetOpposingShip(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	if (const auto& opposing_ship = ship.OpposingShip; opposing_ship.IsValid())
	{
		return opposing_ship.SimID;
	}
	return 0;
}

float EntityLibInterface::GetZombieTime(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.ZombieTime;
}

std::tuple<bool, bool, bool, bool> EntityLibInterface::GetDeathModifiers(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	auto& flags = ship.DeathModifiers;
	return {
		static_cast<bool>(flags.Instant), 
		static_cast<bool>(flags.NoAoeDamage),
		static_cast<bool>(flags.NoDebris),
		static_cast<bool>(flags.NoZombie)
	};
}

float EntityLibInterface::GetSignificance(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.Significance;
}

float EntityLibInterface::GetDistanceToCamera(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.DistanceToCamera;
}

float EntityLibInterface::GetBackstageEffectiveness(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.BackstageEffectiveness;
}

std::uint64_t EntityLibInterface::GetDockWith(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	if (const auto& dock_with = ship.DockWith; dock_with.IsValid())
	{
		return dock_with.SimID;
	}
	return 0;
}

EDockingStage EntityLibInterface::GetDockingStage(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.DockingStage;
}

bool EntityLibInterface::IsDocked(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.IsDocked;
}

bool EntityLibInterface::IsDocking(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.bIsDocking;
}

bool EntityLibInterface::HasPower(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.bHasPower;
}

bool EntityLibInterface::IsHandlingExternalMove(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.bIsHandlingExternalMove;
}

bool EntityLibInterface::CanRally(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.bCanRally;
}

EHyperspaceStatus EntityLibInterface::GetHyperspaceStatus(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.HyperspaceStatus;
}

std::uint64_t EntityLibInterface::GetParent(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	if (const auto& parent = ship.Parent; parent.IsValid())
	{
		return parent.SimID;
	}
	return 0;
}

sol::table EntityLibInterface::GetCollectors(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	const auto& collectors = ship.Collectors;
	sol::table result = lua->create_table();
	for (auto& collector : collectors)
	{
		result.add(static_cast<std::uint64_t>(collector.SimID));
	}
	return result;
}

sol::table EntityLibInterface::GetAnimationStates(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	const auto& animation_states = ship.AnimationStates;
	sol::table result = lua->create_table();
	for (auto& kv : animation_states)
	{
		auto& state = kv.Key();
		auto& val = kv.Value();
		result[static_cast<std::uint8_t>(state)] = val;
	}
	return result;
}

UCommandType EntityLibInterface::GetActiveCommandType(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	return ship.ActiveCommandType;
}

std::tuple<double, double, double> EntityLibInterface::GetShipVelocity(std::uint64_t entity_id) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	const auto& velocity = ship.GetShipVelocity();
	return { velocity.X(), velocity.Y(), velocity.Z() };
}

bool EntityLibInterface::IsMovableEntity(std::uint64_t entity_id) const
{
	const auto entity = find_check_entity(entity_id_manager, entity_id);
	return entity.IsMovableEntity();
}

bool EntityLibInterface::IsWeaponFireActor(std::uint64_t entity_id) const
{
	const auto entity = find_check_entity(entity_id_manager, entity_id);
	return entity.IsWeaponFireActor();
}

bool EntityLibInterface::IsRavenSimProjectile(std::uint64_t entity_id) const
{
	const auto entity = find_check_entity(entity_id_manager, entity_id);
	return entity.IsRavenSimProjectile();
}

bool EntityLibInterface::IsProjectile(std::uint64_t entity_id) const
{
	const auto entity = find_check_entity(entity_id_manager, entity_id);
	return entity.IsProjectile();
}

void EntityLibInterface::SetAnimationState(std::uint64_t entity_id, ESobAnimationState state, bool value) const
{
	const auto ship = find_check_ship(entity_id_manager, entity_id);
	auto& states = ship.AnimationStates;
	auto kv = states.Find(state, [](auto a, auto b) {return a == b; });
	kv->Value() = value;
	ship.ReceiveAnimationStateChanged(state, {});
}
