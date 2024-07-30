#pragma once
#include <pch.h>

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
	WSYS_MEMBER_FUNCTION_VOID(SetTactics, const TiirEntity&, entity, const ESquadronTactics, tactics)

	WSYS_MEMBER_FUNCTION_VOID(SetStance, const TiirEntity&, entity, const ESquadronStance, stance)

	WSYS_MEMBER_FUNCTION_VOID(SetRotation, const TiirEntity&, entity, const RC::Unreal::FRotator&, rotation)

	WSYS_MEMBER_FUNCTION_VOID(SetNoRetaliate, const TiirEntity&, entity, const bool, enabled)

	WSYS_MEMBER_FUNCTION_VOID(SetMetaDataValue, const TiirEntity&, entity, const RC::Unreal::FString&, key, const std::int32_t, value)

	WSYS_MEMBER_FUNCTION_VOID(SetLocation, const TiirEntity&, entity, const RC::Unreal::FVector&, loc)

	WSYS_MEMBER_FUNCTION_VOID(SetInvincible, const TiirEntity&, entity, const bool, enabled)

	WSYS_MEMBER_FUNCTION_VOID(SetIgnoreForPersistentFleet, const TiirEntity&, entity, const bool, enabled)

	WSYS_MEMBER_FUNCTION_VOID(SetIgnoreDamage, const TiirEntity&, entity, const bool, enabled)

	WSYS_MEMBER_FUNCTION_VOID(SetGhost, const TiirEntity&, entity, const bool, enabled)

	WSYS_MEMBER_FUNCTION_VOID(SetCloaking, const TiirEntity&, entity, const bool, enabled)

	WSYS_MEMBER_FUNCTION_VOID(SetAutoLaunch, const TiirEntity&, entity, const EAutoLaunchSetting, auto_launch_setting)

	WSYS_MEMBER_FUNCTION_VOID(SetAngularVelocity, const TiirEntity&, entity, const RC::Unreal::FVector&, angular_velocity)

	WSYS_MEMBER_FUNCTION_VOID(Scuttle, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION_VOID(SalvageCapture, const TiirEntity&, entity, const TiirEntityGroup&, targets)

	WSYS_MEMBER_FUNCTION_VOID(RevealInFow, const TiirEntity&, entity, const bool, revealed)

	WSYS_MEMBER_FUNCTION_VOID(RetireTo, const TiirEntity&, entity, const TiirEntity&, target)

	WSYS_MEMBER_FUNCTION_VOID(Retire, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION_VOID(Repair, const TiirEntity&, entity, const TiirEntityGroup&, targets)
	
	WSYS_MEMBER_FUNCTION(bool, RemoveStatusEffectByHandle, const TiirStatusEffectHandle&, handle)

	WSYS_MEMBER_FUNCTION(bool, RemoveStatusEffect, const TiirEntity&, entity, const UStatusEffectStaticData, status)

	WSYS_MEMBER_FUNCTION_VOID(RemoveObtainableArtifactFromShip, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(bool, RemoveModifier, const TiirModifierHandle&, modifier)

	// todo bound to lua
	WSYS_MEMBER_FUNCTION_VOID(RemoveEntityStatus, const TiirEntity&, entity, const EntityStatus*, status)

	WSYS_MEMBER_FUNCTION_VOID(OverrideRetaliationSetting, const TiirEntity&, entity, const ERetaliationSetting, retaliation_setting)

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
	WSYS_MEMBER_FUNCTION(bool, HasStatusEffect, const TiirEntity&, entity, const UStatusEffectStaticData, status_effect)

	WSYS_MEMBER_FUNCTION_VOID(Guard, const TiirEntity&, entity, const TiirEntityGroup&, targets)

	WSYS_MEMBER_FUNCTION(float, GetVisualRange, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(float, GetSecondarySensorRange, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(float, GetPrimarySensorRange, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(RC::Unreal::FVector, GetPosition, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(TiirCommander, GetOwningPlayer, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(RC::Unreal::FRotator, GetOrientation, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(std::int32_t, GetNumberOfQueuedOrders, const TiirEntity&, entity)

	bool GetMetaDataValue(const TiirEntity& entity, const Unreal::FString& key, std::int32_t& value, const std::source_location& location = std::source_location::current()) const;

	WSYS_MEMBER_FUNCTION(float, GetHealthAbsolute, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION(float, GetHealth, const TiirEntity&, entity)

	// not bound
	WSYS_MEMBER_FUNCTION(TiirEntity, GetEntity_OnPres, const ASimEntity, entity)

	// not bound
	WSYS_MEMBER_FUNCTION(TiirEntity, GetEntity, const ASimEntity, entity)

	WSYS_MEMBER_FUNCTION(std::int32_t, GetBuildTime, const TiirEntity&, entity)

	WSYS_MEMBER_FUNCTION_VOID(GatherResource, const TiirEntity&, entity, const TiirEntityGroup&, targets)

	// bound to lua: FindShipType
	WSYS_MEMBER_FUNCTION(UShipStaticData, FindShipStaticData, const TiirEntity&, entity)

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

	WSYS_MEMBER_FUNCTION(TiirStatusEffectHandle, AddStatusEffect, const TiirEntity&, entity, UStatusEffectStaticData, status_effect)

	WSYS_MEMBER_FUNCTION(TiirModifierHandle, AddOverrideModifier, const TiirEntity&, entity, const ESobPropertyType, property, const float, value, const EInfluenceType, influence_type, const float, influence_radius)

	// todo bound to lua
	//WSYS_MEMBER_FUNCTION_VOID(AddObtainableSoftArtifactToShip, const TiirEntity&, entity, const TSoftObjectPtr<UArtifactStaticData>, artifact_static_data)

	WSYS_MEMBER_FUNCTION_VOID(AddObtainableArtifactToShip, const TiirEntity&, entity, const UArtifactStaticData, artifact_static_data)

	WSYS_MEMBER_FUNCTION(TiirModifierHandle, AddMultiplierModifier, const TiirEntity&, entity, const EMultiplierType, multiplier, const float, multiplier_value, const EInfluenceType, influence_type, const float, influence_radius, const EActivityRelation, multiplier_value_relation, const float, multiplier_interp_min_value)

	WSYS_MEMBER_FUNCTION(TiirModifierHandle, AddAbilityModifier, const TiirEntity&, entity, const EAbilityType, ability, const bool, ability_state, const EInfluenceType, influence_type, const float, influence_radius)

};
