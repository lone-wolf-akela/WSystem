#pragma once
#include <pch.h>

#include <DataWrapper/SimEntity.h>
#include <DataWrapper/ShipStaticData.h>
#include <DataWrapper/AttackFamily.h>
#include <DataWrapper/ArtifactStaticData.h>
#include <DataWrapper/TiirShipSpawner.h>
#include <DataWrapper/StrikeGroupFormationStaticData.h>
#include <DataWrapper/WeaponStaticData.h>
#include <DataWrapper/StatusEffectStaticData.h>

#include "LibBase.h"
#include "LibDataTypes.h"

class EntityStatus;
class GameplayTagQuery;
class TiirScriptInstance;
class TiirGroupQuery;

class TiirEntityGroupFunctionLibrary : public LibBase<TiirEntityGroupFunctionLibrary>
{
public:
	static constexpr auto LibPath = STR("/Script/RavenSimulation.TiirEntityGroupFunctionLibrary");
	WSYS_MEMBER_FUNCTION_VOID(UndeployTurret, const TiirEntityGroup&, group, const bool, instantaneous)

	WSYS_MEMBER_FUNCTION_VOID(ToggleAlternativeShipOrientation, const TiirEntityGroup&, group)

	WSYS_MEMBER_FUNCTION_VOID(Teleport, const TiirEntityGroup&, group, const RC::Unreal::FTransform&, transform, const bool, teleport_ships_in_parade)

	WSYS_MEMBER_FUNCTION_VOID(TakeDamageAbsolute, const TiirEntityGroup&, group, const float, damage_absolute)

	WSYS_MEMBER_FUNCTION_VOID(TakeDamage, const TiirEntityGroup&, group, const float, damage_percentage)

	WSYS_MEMBER_FUNCTION_VOID(Stop, const TiirEntityGroup&, group)

	WSYS_MEMBER_FUNCTION_VOID(Spawn, const TiirEntityGroup&, group, const RC::Unreal::FTransform&, transform, const bool, skip_placement_logic)

	WSYS_MEMBER_FUNCTION_VOID(SetVelocity, const TiirEntityGroup&, group, const RC::Unreal::FVector&, velocity)

	WSYS_MEMBER_FUNCTION_VOID(SetTransform, const TiirEntityGroup&, group, const RC::Unreal::FTransform&, transform)

	WSYS_MEMBER_FUNCTION_VOID(SetTactics, const TiirEntityGroup&, group, const SquadronTactics, tactics)

	WSYS_MEMBER_FUNCTION_VOID(SetStrikeGroupFormation, const TiirEntityGroup&, group, const StrikeGroupFormationStaticData, formation)

	WSYS_MEMBER_FUNCTION_VOID(SetStance, const TiirEntityGroup&, group, const SquadronStance, stance)

	WSYS_MEMBER_FUNCTION_VOID(SetRotation, const TiirEntityGroup&, group, const RC::Unreal::FRotator&, rotation)

	WSYS_MEMBER_FUNCTION_VOID(SetNoRetaliate, const TiirEntityGroup&, group, const bool, enabled)

	WSYS_MEMBER_FUNCTION_VOID(SetLocation, const TiirEntityGroup&, group, const RC::Unreal::FVector&, loc)

	WSYS_MEMBER_FUNCTION_VOID(SetInvincible, const TiirEntityGroup&, group, const bool, enabled)

	WSYS_MEMBER_FUNCTION_VOID(SetIgnoreForPersistentFleet, const TiirEntityGroup&, group, const bool, enabled)

	WSYS_MEMBER_FUNCTION_VOID(SetIgnoreDamage, const TiirEntityGroup&, group, const bool, enabled)

	WSYS_MEMBER_FUNCTION_VOID(SetHealth, const TiirEntityGroup&, group, const float, health_percentage)

	WSYS_MEMBER_FUNCTION_VOID(SetGhost, const TiirEntityGroup&, group, const bool, enabled)

	WSYS_MEMBER_FUNCTION_VOID(SetCloaking, const TiirEntityGroup&, group, const bool, enabled)

	WSYS_MEMBER_FUNCTION_VOID(SetAutoLaunch, const TiirEntityGroup&, group, const AutoLaunchSetting, auto_launch_setting)

	WSYS_MEMBER_FUNCTION_VOID(Scuttle, const TiirEntityGroup&, group)

	WSYS_MEMBER_FUNCTION_VOID(SalvageCapture, const TiirEntityGroup&, group, const TiirEntityGroup&, targets)

	WSYS_MEMBER_FUNCTION_VOID(RevealInFow, const TiirEntityGroup&, group, const bool, revealed)

	WSYS_MEMBER_FUNCTION_VOID(RetireTo, const TiirEntityGroup&, group, const TiirEntity&, target)

	WSYS_MEMBER_FUNCTION_VOID(Retire, const TiirEntityGroup&, group)

	WSYS_MEMBER_FUNCTION_VOID(Repair, const TiirEntityGroup&, group, const TiirEntityGroup&, target_group)

	WSYS_MEMBER_FUNCTION_VOID(RemoveStatusEffectsByHandles, const UC::TArray<TiirStatusEffectHandle>&, handles)

	WSYS_MEMBER_FUNCTION_VOID(RemoveStatusEffect, const TiirEntityGroup&, group, const StatusEffectStaticData, status)

	WSYS_MEMBER_FUNCTION_VOID(RemoveObtainableArtifactFromShips, const TiirEntityGroup&, group)

	// todo: bound to lua
	WSYS_MEMBER_FUNCTION_VOID(RemoveEntityStatus, const TiirEntityGroup&, group, const EntityStatus*, status)

	// todo: bound to lua
	// WSYS_MEMBER_FUNCTION_REF(TiirEntityGroup, QueryGroupByProximity, TiirGroupQuery&, query, const RC::Unreal::FVector&, loc, float, radius)

	WSYS_MEMBER_FUNCTION_VOID(ParadeAround, const TiirEntityGroup&, group, const TiirEntity&, parade_around_entity, const ParadeMode, parade_mode)

	WSYS_MEMBER_FUNCTION_VOID(OverrideRetaliationSetting, const TiirEntityGroup&, group, const RetaliationSetting, the_retaliation_setting)

	WSYS_MEMBER_FUNCTION_VOID(MoveTo, const TiirEntityGroup&, group, const RC::Unreal::FVector&, destination, bool, attack_move)

	WSYS_MEMBER_FUNCTION_VOID(MovePingPong, const TiirEntityGroup&, group, const UC::TArray<RC::Unreal::FVector>&, locations, bool, attack_move)

	WSYS_MEMBER_FUNCTION_VOID(MoveAlong, const TiirEntityGroup&, group, const UC::TArray<RC::Unreal::FVector>&, path, bool, loop, bool, attack_move)

	// not bound.
	WSYS_MEMBER_FUNCTION(TiirEntityGroup, MakeGroupFromActor, const SimEntity, entity)

	WSYS_MEMBER_FUNCTION_VOID(MakeDead, const TiirEntityGroup&, group, const EntityDeathModifiers&, death_modifiers)

	WSYS_MEMBER_FUNCTION_VOID(LaunchSelf, const TiirEntityGroup&, group)

	WSYS_MEMBER_FUNCTION_VOID(LaunchAll, const TiirEntityGroup&, group)

	WSYS_MEMBER_FUNCTION_VOID(LatchInstantly, const TiirEntityGroup&, group, const TiirEntityGroup&, latch_target_entity)

	WSYS_MEMBER_FUNCTION_VOID(KillUnit, const TiirEntityGroup&, group, bool, by_damage)

	WSYS_MEMBER_FUNCTION_VOID(Kamikaze, const TiirEntityGroup&, group, const TiirEntityGroup&, target_group, const bool, can_attack_cloaked_units)

	WSYS_MEMBER_FUNCTION(bool, IsWithinPlayerSensorRange, const TiirEntityGroup&, group, const std::int32_t, target_player)

	WSYS_MEMBER_FUNCTION(bool, IsInHyperspace, const TiirEntityGroup&, group)

	WSYS_MEMBER_FUNCTION(bool, IsGroupInCombat, const TiirEntityGroup&, group, bool, require_everyone)

	WSYS_MEMBER_FUNCTION(bool, IsDeSpawned, const TiirEntityGroup&, group)

	WSYS_MEMBER_FUNCTION(bool, IsCloaking, const TiirEntityGroup&, group, const bool, require_all)

	// bound to lua
	// seems not work
	WSYS_MEMBER_FUNCTION_VOID(HyperspaceToDestination, const TiirEntityGroup&, group, const RC::Unreal::FTransform&, destination, const bool, skip_placement_logic)

	WSYS_MEMBER_FUNCTION_VOID(HyperspaceExit, const TiirEntityGroup&, group, const RC::Unreal::FTransform&, transform, const bool, skip_placement_logic)

	WSYS_MEMBER_FUNCTION_VOID(HyperspaceEnter, const TiirEntityGroup&, group)

	WSYS_MEMBER_FUNCTION(bool, HasStatusEffect, const TiirEntityGroup&, group, const StatusEffectStaticData, status_effect, const bool, check_for_all)

	WSYS_MEMBER_FUNCTION_VOID(Guard, const TiirEntityGroup&, group, const TiirEntityGroup&, targets)

	WSYS_MEMBER_FUNCTION_REF(std::int32_t, GroupRemoveEntity, TiirEntityGroup&, group, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION_REF(std::int32_t, GroupRemove, TiirEntityGroup&, group, const TiirEntityGroup&, source_group)

	WSYS_MEMBER_FUNCTION_REF(std::int32_t, GroupPurgeDead, TiirEntityGroup&, group)

	WSYS_MEMBER_FUNCTION_REF(std::int32_t, GroupPurgeAlive, TiirEntityGroup&, group)

	WSYS_MEMBER_FUNCTION_VOID(GroupMembers, const TiirEntityGroup&, group, UC::TArray<TiirEntity>*, members)

	WSYS_MEMBER_FUNCTION_REF(std::int32_t, GroupCountFiltered, TiirEntityGroup&, group, const TiirGroupCountFilter&, filter)

	WSYS_MEMBER_FUNCTION_REF(std::int32_t, GroupCount, TiirEntityGroup&, group)

	WSYS_MEMBER_FUNCTION_VOID_REF(GroupClear, TiirEntityGroup&, group)

	WSYS_MEMBER_FUNCTION_REF(std::int32_t, GroupAddEntity, TiirEntityGroup&, group, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION_REF(std::int32_t, GroupAdd, TiirEntityGroup&, group, const TiirEntityGroup&, source_group)

	WSYS_MEMBER_FUNCTION(RC::Unreal::FVector, GetPosition, const TiirEntityGroup&, group)

	WSYS_MEMBER_FUNCTION(RC::Unreal::FRotator, GetOrientation, const TiirEntityGroup&, group)

	WSYS_MEMBER_FUNCTION(RC::Unreal::FString, GenerateDebugString, const TiirEntityGroup&, group)

	WSYS_MEMBER_FUNCTION_VOID(GatherResource, const TiirEntityGroup&, group, const TiirEntityGroup&, targets)

	WSYS_MEMBER_FUNCTION(bool, FireAtNoTarget, const TiirEntityGroup&, group, const WeaponStaticData, weapon_type, const bool, all_sources_fire, const RC::Unreal::FName&, fire_from_socket, const RC::Unreal::FVector&, muzzle_offset)

	WSYS_MEMBER_FUNCTION(bool, FireAt, const TiirEntityGroup&, group, const TiirEntityGroup&, target_group, const WeaponStaticData, weapon_type, const bool, all_sources_fire, const bool, fire_at_all_targets, const RC::Unreal::FName&, fire_from_socket, const RC::Unreal::FVector&, muzzle_offset)

	// todo: bound to lua
	//WSYS_MEMBER_FUNCTION_REF(std::int32_t, FillGroupWithTagQueryMatches, TiirEntityGroup&, group, const TiirEntityGroup&, source_group, const GameplayTagQuery&, query)

	WSYS_MEMBER_FUNCTION_REF(std::int32_t, FillGroupIncludingPlayer, TiirEntityGroup&, group, const TiirEntityGroup&, source_group, const TiirCommander&, owning_player)

	WSYS_MEMBER_FUNCTION_REF(std::int32_t, FillGroupFromPlayerMothershipList, TiirEntityGroup&, group, const std::int32_t, owning_player, const bool, include_dead)

	WSYS_MEMBER_FUNCTION_REF(std::int32_t, FillGroupFromPlayer, TiirEntityGroup&, group, const std::int32_t, owning_player, const bool, include_docked, const bool, include_in_hyperspace, const bool, include_dead)

	WSYS_MEMBER_FUNCTION_REF(std::int32_t, FillGroupFromFilteredType, TiirEntityGroup&, group, const TiirEntityGroup&, source_group, const UC::TArray<EntityStaticData>&, desired_types)

	WSYS_MEMBER_FUNCTION_REF(std::int32_t, FillGroupFromFilteredFamily, TiirEntityGroup&, group, const TiirEntityGroup&, source_group, const UC::TArray<AttackFamily>&, desired_types)

	WSYS_MEMBER_FUNCTION_REF(std::int32_t, FillGroupExcludingPlayer, TiirEntityGroup&, group, const TiirEntityGroup&, source_group, const std::int32_t, excluding_player)

	WSYS_MEMBER_FUNCTION_REF(std::int32_t, FillGroupByProximityToLocation, TiirEntityGroup&, group, const TiirEntityGroup&, source_group, const RC::Unreal::FVector&, loc, const RC::Unreal::FVector&, distance)

	WSYS_MEMBER_FUNCTION_REF(std::int32_t, FillGroupByProximityToGroup, TiirEntityGroup&, group, const TiirEntityGroup&, source_group, const TiirEntityGroup&, near_group, const RC::Unreal::FVector&, distance)

	WSYS_MEMBER_FUNCTION_VOID(DockInstantly, const TiirEntityGroup&, group, const TiirEntityGroup&, dock_target_entity_group)

	WSYS_MEMBER_FUNCTION_VOID(Dock, const TiirEntityGroup&, group, const TiirEntityGroup&, dock_target_entity_group, const bool, stay_docked, const bool, dock_only)

	WSYS_MEMBER_FUNCTION_VOID(DisbandStrikeGroup, const TiirEntityGroup&, group)

	WSYS_MEMBER_FUNCTION_VOID(Despawn, const TiirEntityGroup&, group, const bool, ignore_active_commands)

	WSYS_MEMBER_FUNCTION_VOID(DeployTurretAtPositionAndOrientation, const TiirEntityGroup&, group, const RC::Unreal::FVector&, position, const RC::Unreal::FRotator&, orientation, bool, instantaneous)

	WSYS_MEMBER_FUNCTION_VOID(DeployTurretAtPositionAndNormal, const TiirEntityGroup&, group, const RC::Unreal::FVector&, position, const RC::Unreal::FVector&, normal, bool, instantaneous)

	WSYS_MEMBER_FUNCTION_VOID(DeployTurret, const TiirEntityGroup&, group, const bool, instantaneous)

	WSYS_MEMBER_FUNCTION_VOID(CustomCommand, const TiirEntityGroup&, group, const TiirEntityGroup&, targets)

	// not bound.
	// todo build alternative func
	WSYS_MEMBER_FUNCTION_VOID_REF(CreateShip, TiirEntityGroup&, group, const TiirShipSpawner, ship_spawner, const std::int32_t, owning_player, const bool, start_in_hyperspace, const bool, skip_placement_logic)

	WSYS_MEMBER_FUNCTION(std::int32_t, CountShipTypePresentInGroup, const TiirEntityGroup&, group, const UC::TArray<ShipStaticData>&, filter_types)

	WSYS_MEMBER_FUNCTION(std::int32_t, CountAttackFamilyPresentInGroup, const TiirEntityGroup&, group, const UC::TArray<AttackFamily>&, filter_types)

	WSYS_MEMBER_FUNCTION_VOID(ClearStatusEffects, const TiirEntityGroup&, group)

	WSYS_MEMBER_FUNCTION_VOID(ClearRetaliationSetting, const TiirEntityGroup&, group)

	WSYS_MEMBER_FUNCTION_VOID(ChangeOwner, const TiirEntityGroup&, group, const std::int32_t, target_player)

	WSYS_MEMBER_FUNCTION_VOID(ChangeCommander, const TiirEntityGroup&, group, const TiirCommander&, new_commander)

	WSYS_MEMBER_FUNCTION_VOID(BindInstantly, const TiirEntityGroup&, group, const TiirEntityGroup&, bind_target_entity)

	WSYS_MEMBER_FUNCTION_VOID(AttackPlayer, const TiirEntityGroup&, group, const std::int32_t, target_player, const bool, can_attack_cloaked_units)

	WSYS_MEMBER_FUNCTION_VOID(Attack, const TiirEntityGroup&, group, const TiirEntityGroup&, target_group, const bool, maintain_guard, const bool, can_attack_cloaked_units)

	// todo: bound to lua
	WSYS_MEMBER_FUNCTION_VOID(ApplyEntityStatus, const TiirEntityGroup&, group, const EntityStatus*, status)

	WSYS_MEMBER_FUNCTION_VOID(AddStatusEffect, const TiirEntityGroup&, group, const StatusEffectStaticData, status, UC::TArray<TiirStatusEffectHandle>*, out_handles)

	// todo: bound to lua
	//WSYS_MEMBER_FUNCTION_VOID(AddObtainableSoftArtifactToShips, const TiirEntityGroup&, group, const TSoftObjectPtr<UArtifactStaticData>, artifact_static_data)

	WSYS_MEMBER_FUNCTION_VOID(AddObtainableArtifactToShips, const TiirEntityGroup&, group, const ArtifactStaticData, artifact_static_data)

};