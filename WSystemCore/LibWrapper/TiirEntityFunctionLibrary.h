#pragma once
#include <cstdint>

#include <Unreal/Transform.hpp>
#include <Unreal/Rotator.hpp>

#include <DataWrapper/ShipStaticData.h>
#include <DataWrapper/SimEntity.h>
#include <DataWrapper/ArtifactStaticData.h>
#include <DataWrapper/StatusEffectStaticData.h>

#include "LibBase.h"
#include "LibDataTypes.h"

class EntityStatus;
class GameplayTagQuery;
class TiirScriptInstance;

class TiirEntityFunctionLibrary : public LibBase<TiirEntityFunctionLibrary>
{
public:
	static constexpr auto LibPath = STR("/Script/RavenSimulation.TiirEntityFunctionLibrary");

	WSYS_MEMBER_FUNCTION_VOID(UndeployTurret, const TiirEntity&, entity, const bool, instantaneous)

	WSYS_MEMBER_FUNCTION_VOID(Teleport, const TiirEntity&, entity, const RC::Unreal::FTransform&, transform, const bool, teleport_ships_in_parade)

	WSYS_MEMBER_FUNCTION_VOID(SetVelocity, const TiirEntity&, entity, const RC::Unreal::FVector&, velocity)

	WSYS_MEMBER_FUNCTION_VOID(SetTransform, const TiirEntity&, entity, const RC::Unreal::FTransform&, transform)

	// maybe not works
	WSYS_MEMBER_FUNCTION_VOID(SetTactics, const TiirEntity&, entity, const SquadronTactics, tactics)

	WSYS_MEMBER_FUNCTION_VOID(SetStance, const TiirEntity&, entity, const SquadronStance, stance)

	WSYS_MEMBER_FUNCTION_VOID(SetRotation, const TiirEntity&, entity, const RC::Unreal::FRotator&, rotation)

	WSYS_MEMBER_FUNCTION_VOID(SetNoRetaliate, const TiirEntity&, entity, const bool, enabled)

	WSYS_MEMBER_FUNCTION_VOID(SetMetaDataValue, const TiirEntity&, entity, const RC::Unreal::FString&, key, const std::int32_t, value)

	WSYS_MEMBER_FUNCTION_VOID(SetLocation, const TiirEntity&, entity, const RC::Unreal::FVector&, loc)

	WSYS_MEMBER_FUNCTION_VOID(SetInvincible, const TiirEntity&, entity, const bool, enabled)

	WSYS_MEMBER_FUNCTION_VOID(SetIgnoreForPersistentFleet, const TiirEntity&, entity, const bool, enabled)

	WSYS_MEMBER_FUNCTION_VOID(SetIgnoreDamage, const TiirEntity&, entity, const bool, enabled)

	WSYS_MEMBER_FUNCTION_VOID(SetGhost, const TiirEntity&, entity, const bool, enabled)

	WSYS_MEMBER_FUNCTION_VOID(SetCloaking, const TiirEntity&, entity, const bool, enabled)

	WSYS_MEMBER_FUNCTION_VOID(SetAutoLaunch, const TiirEntity&, entity, const AutoLaunchSetting, auto_launch_setting)

	WSYS_MEMBER_FUNCTION_VOID(SetAngularVelocity, const TiirEntity&, entity, const RC::Unreal::FVector&, angular_velocity)

	WSYS_MEMBER_FUNCTION_VOID(Scuttle, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION_VOID(SalvageCapture, const TiirEntity&, entity, const TiirEntityGroup&, targets)

	WSYS_MEMBER_FUNCTION_VOID(RevealInFow, const TiirEntity&, entity, const bool, revealed)

	WSYS_MEMBER_FUNCTION_VOID(RetireTo, const TiirEntity&, entity, const TiirEntity&, target)

	WSYS_MEMBER_FUNCTION_VOID(Retire, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION_VOID(Repair, const TiirEntity&, entity, const TiirEntityGroup&, targets)
	
	// todo bound to lua
	WSYS_MEMBER_FUNCTION(bool, RemoveStatusEffectByHandle, const TiirStatusEffectHandle&, handle)

	// todo bound to lua
	WSYS_MEMBER_FUNCTION(bool, RemoveStatusEffect, const TiirEntity&, entity, const StatusEffectStaticData, status)

	WSYS_MEMBER_FUNCTION_VOID(RemoveObtainableArtifactFromShip, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(bool, RemoveModifier, const TiirModifierHandle&, modifier)

	// todo bound to lua
	WSYS_MEMBER_FUNCTION_VOID(RemoveEntityStatus, const TiirEntity&, entity, const EntityStatus*, status)

	WSYS_MEMBER_FUNCTION_VOID(OverrideRetaliationSetting, const TiirEntity&, entity, const RetaliationSetting, retaliation_setting)

	// not bound
	WSYS_MEMBER_FUNCTION(bool, NotEqual_TiirEntityTiirEntity, const TiirEntity&, a, const TiirEntity&, b)

	WSYS_MEMBER_FUNCTION_VOID(MovePingPong, const TiirEntity&, entity, const UC::TArray<RC::Unreal::FVector>&, locations, bool, attack_move)

	WSYS_MEMBER_FUNCTION_VOID(MoveAlong, const TiirEntity&, entity, const UC::TArray<RC::Unreal::FVector>&, path, bool, loop, bool, attack_move)

	// todo bound to lua
	//WSYS_MEMBER_FUNCTION(bool, MatchesTagQuery, const TiirEntity&, entity, const GameplayTagQuery&, query)

	WSYS_MEMBER_FUNCTION_VOID(MakeDead, const TiirEntity&, entity, const EntityDeathModifiers&, death_modifiers)

	WSYS_MEMBER_FUNCTION_VOID(LaunchSelf, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION_VOID(LaunchAll, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION_VOID(LatchInstantly, const TiirEntity&, entity, const TiirEntity&, latch_target_entity)

	WSYS_MEMBER_FUNCTION_VOID(Kamikaze, const TiirEntity&, entity, const TiirEntityGroup&, targets)

	WSYS_MEMBER_FUNCTION(bool, IsValid_OnPres, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(bool, IsValid, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(bool, IsInHyperspace, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(bool, IsInCombat, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(bool, IsCloaking, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(bool, IsBeingCaptured, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(bool, IsBeingAttacked, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(bool, IsAttacking, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(bool, IsAlive, const TiirEntity&, entity)

	// not bound
	WSYS_MEMBER_FUNCTION(bool, HasStatusEffect, const TiirEntity&, entity, const StatusEffectStaticData, status_effect)

	WSYS_MEMBER_FUNCTION_VOID(Guard, const TiirEntity&, entity, const TiirEntityGroup&, targets)

	WSYS_MEMBER_FUNCTION(float, GetVisualRange, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(float, GetSecondarySensorRange, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(float, GetPrimarySensorRange, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(RC::Unreal::FVector, GetPosition, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(TiirCommander, GetOwningPlayer, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(RC::Unreal::FRotator, GetOrientation, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(std::int32_t, GetNumberOfQueuedOrders, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(bool, GetMetaDataValue, const TiirEntity&, entity, const RC::Unreal::FString&, key, std::int32_t*, value)

	WSYS_MEMBER_FUNCTION(float, GetHealthAbsolute, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(float, GetHealth, const TiirEntity&, entity)

	// not bound
	WSYS_MEMBER_FUNCTION(TiirEntity, GetEntity_OnPres, const SimEntity, entity)

	// not bound
	WSYS_MEMBER_FUNCTION(TiirEntity, GetEntity, const SimEntity, entity)

	WSYS_MEMBER_FUNCTION(std::int32_t, GetBuildTime, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION_VOID(GatherResource, const TiirEntity&, entity, const TiirEntityGroup&, targets)

	// bound to lua: FindShipType
	WSYS_MEMBER_FUNCTION(ShipStaticData, FindShipStaticData, const TiirEntity&, entity)

	// not bound
	WSYS_MEMBER_FUNCTION(bool, EqualEqual_TiirEntityTiirEntity, const TiirEntity&, a, const TiirEntity&, b)

	WSYS_MEMBER_FUNCTION_VOID(DockInstantly, const TiirEntity&, entity, const TiirEntity&, dock_target_entity)

	WSYS_MEMBER_FUNCTION_VOID(Dock, const TiirEntity&, entity, const TiirEntity&, dock_target_entity, const bool, stay_docked, const bool, dock_only)

	// todo bound to lua
	//WSYS_MEMBER_FUNCTION(bool, DetachScript, const TiirEntity&, entity, const TiirScriptInstance&, script)

	WSYS_MEMBER_FUNCTION_VOID(DeployTurretAtPositionAndOrientation, const TiirEntity&, entity, const RC::Unreal::FVector, position, const RC::Unreal::FRotator, orientation, const bool, instantaneous)

	WSYS_MEMBER_FUNCTION_VOID(DeployTurretAtPositionAndNormal, const TiirEntity&, entity, const RC::Unreal::FVector&, position, const RC::Unreal::FVector&, normal, const bool, instantaneous)

	WSYS_MEMBER_FUNCTION_VOID(DeployTurret, const TiirEntity&, entity, const bool, instantaneous)

	WSYS_MEMBER_FUNCTION_VOID(CustomCommand, const TiirEntity&, entity, const TiirEntityGroup&, targets)

	WSYS_MEMBER_FUNCTION(bool, ClearStatusEffects, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION_VOID(ClearRetaliationSetting, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(bool, ClearModifiers, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION_VOID(ChangeOwner, const TiirEntity&, entity, const std::int32_t, target_player)

	WSYS_MEMBER_FUNCTION_VOID(ChangeCommander, const TiirEntity&, entity, const TiirCommander&, new_commander)

	WSYS_MEMBER_FUNCTION_VOID(BindInstantly, const TiirEntity&, entity, const TiirEntity&, bind_target_entity)

	WSYS_MEMBER_FUNCTION_VOID(Attack, const TiirEntity&, entity, const TiirEntityGroup&, targets, const bool, maintain_guard)

	// todo bound to lua
	//WSYS_MEMBER_FUNCTION(bool, AttachScript, const TiirEntity&, entity, const TiirScriptInstance&, script, const float, interval)

	// todo bound to lua
	WSYS_MEMBER_FUNCTION_VOID(ApplyEntityStatus, const TiirEntity&, entity, const EntityStatus*, status)

	// todo bound to lua
	WSYS_MEMBER_FUNCTION(TiirStatusEffectHandle, AddStatusEffect, const TiirEntity&, entity, StatusEffectStaticData, status_effect)

	WSYS_MEMBER_FUNCTION(TiirModifierHandle, AddOverrideModifier, const TiirEntity&, entity, const SobPropertyType, property, const float, value, const InfluenceType, influence_type, const float, influence_radius)

	// todo bound to lua
	//WSYS_MEMBER_FUNCTION_VOID(AddObtainableSoftArtifactToShip, const TiirEntity&, entity, const TSoftObjectPtr<UArtifactStaticData>, artifact_static_data)

	// todo bound to lua
	WSYS_MEMBER_FUNCTION_VOID(AddObtainableArtifactToShip, const TiirEntity&, entity, const ArtifactStaticData, artifact_static_data)

	WSYS_MEMBER_FUNCTION(TiirModifierHandle, AddMultiplierModifier, const TiirEntity&, entity, const MultiplierType, multiplier, const float, multiplier_value, const InfluenceType, influence_type, const float, influence_radius, const ActivityRelation, multiplier_value_relation, const float, multiplier_interp_min_value)

	WSYS_MEMBER_FUNCTION(TiirModifierHandle, AddAbilityModifier, const TiirEntity&, entity, const AbilityType, ability, const bool, ability_state, const InfluenceType, influence_type, const float, influence_radius)

};
