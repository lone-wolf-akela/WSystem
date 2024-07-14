#pragma once
#include <cstdint>

#include <Unreal/Transform.hpp>
#include <Unreal/Rotator.hpp>

#include <DataWrapper/ShipStaticData.h>
#include <DataWrapper/SimEntity.h>

#include "LibBase.h"
#include "LibDataTypes.h"

class StatusEffectStaticData;
class EntityStatus;
class GameplayTagQuery;
class ArtifactStaticData;
class TiirScriptInstance;

class TiirEntityFunctionLibrary : public LibBase<TiirEntityFunctionLibrary>
{
public:
	static constexpr auto LibPath = STR("/Script/RavenSimulation.TiirEntityFunctionLibrary");

    WSYS_MEMBER_FUNCTION_VOID(UndeployTurret, TiirEntity*, Entity, bool, Instantaneous)
    WSYS_MEMBER_FUNCTION_VOID(Teleport, TiirEntity*, Entity, RC::Unreal::FTransform, Transform, bool, TeleportShipsInParade)
    WSYS_MEMBER_FUNCTION_VOID(SetVelocity, TiirEntity*, Entity, RC::Unreal::FVector, Velocity)
    WSYS_MEMBER_FUNCTION_VOID(SetTransform, TiirEntity*, Entity, RC::Unreal::FTransform, Transform)
    WSYS_MEMBER_FUNCTION_VOID(SetTactics, TiirEntity*, Entity, SquadronTactics, Tactics)
    WSYS_MEMBER_FUNCTION_VOID(SetStance, TiirEntity*, Entity, SquadronStance, Stance)
    WSYS_MEMBER_FUNCTION_VOID(SetRotation, TiirEntity*, Entity, RC::Unreal::FRotator, Rotation)
    WSYS_MEMBER_FUNCTION_VOID(SetNoRetaliate, TiirEntity*, Entity, bool, Enabled)
    WSYS_MEMBER_FUNCTION_VOID(SetMetaDataValue, TiirEntity*, Entity, RC::Unreal::FString, Key, std::int32_t, Value)
    WSYS_MEMBER_FUNCTION_VOID(SetLocation, TiirEntity*, Entity, RC::Unreal::FVector, Location)
    WSYS_MEMBER_FUNCTION_VOID(SetInvincible, TiirEntity*, Entity, bool, Enabled)
    WSYS_MEMBER_FUNCTION_VOID(SetIgnoreForPersistentFleet, TiirEntity*, Entity, bool, Enabled)
    WSYS_MEMBER_FUNCTION_VOID(SetIgnoreDamage, TiirEntity*, Entity, bool, Enabled)
    WSYS_MEMBER_FUNCTION_VOID(SetGhost, TiirEntity*, Entity, bool, Enabled)
    WSYS_MEMBER_FUNCTION_VOID(SetCloaking, TiirEntity*, Entity, bool, Enabled)
    WSYS_MEMBER_FUNCTION_VOID(SetAutoLaunch, TiirEntity*, Entity, AutoLaunchSetting, AutoLaunchSetting)
    WSYS_MEMBER_FUNCTION_VOID(SetAngularVelocity, TiirEntity*, Entity, RC::Unreal::FVector, AngularVelocity)
    WSYS_MEMBER_FUNCTION_VOID(Scuttle, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION_VOID(SalvageCapture, TiirEntity*, Entity, TiirEntityGroup*, Targets)
    WSYS_MEMBER_FUNCTION_VOID(RevealInFow, TiirEntity*, Entity, bool, Revealed)
    WSYS_MEMBER_FUNCTION_VOID(RetireTo, TiirEntity*, Entity, TiirEntity*, Target)
    WSYS_MEMBER_FUNCTION_VOID(Retire, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION_VOID(Repair, TiirEntity*, Entity, TiirEntityGroup*, Targets)
    WSYS_MEMBER_FUNCTION_VOID(RemoveObtainableArtifactFromShip, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION(bool, RemoveModifier, TiirModifierHandle*, Modifier)
    WSYS_MEMBER_FUNCTION_VOID(OverrideRetaliationSetting, TiirEntity*, Entity, RetaliationSetting, RetaliationSetting)
    WSYS_MEMBER_FUNCTION_VOID(MovePingPong, TiirEntity*, Entity, UC::TArray<RC::Unreal::FVector>*, Locations, bool, AttackMove)
    WSYS_MEMBER_FUNCTION_VOID(MoveAlong, TiirEntity*, Entity, UC::TArray<RC::Unreal::FVector>*, Path, bool, Loop, bool, AttackMove)
    WSYS_MEMBER_FUNCTION_VOID(MakeDead, TiirEntity*, Entity, EntityDeathModifiers*, DeathModifiers)
    WSYS_MEMBER_FUNCTION_VOID(LaunchSelf, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION_VOID(LaunchAll, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION_VOID(LatchInstantly, TiirEntity*, Entity, TiirEntity*, LatchTargetEntity)
    WSYS_MEMBER_FUNCTION_VOID(Kamikaze, TiirEntity*, Entity, TiirEntityGroup*, Targets)
    WSYS_MEMBER_FUNCTION(bool, IsValid_OnPres, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION(bool, IsValid, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION(bool, IsInHyperspace, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION(bool, IsInCombat, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION(bool, IsCloaking, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION(bool, IsBeingCaptured, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION(bool, IsBeingAttacked, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION(bool, IsAttacking, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION(bool, IsAlive, TiirEntity*, Entity) 
    WSYS_MEMBER_FUNCTION_VOID(Guard, TiirEntity*, Entity, TiirEntityGroup*, Targets)
    WSYS_MEMBER_FUNCTION(float, GetVisualRange, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION(float, GetSecondarySensorRange, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION(float, GetPrimarySensorRange, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION(RC::Unreal::FVector, GetPosition, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION(TiirCommander, GetOwningPlayer, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION(RC::Unreal::FRotator, GetOrientation, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION(std::int32_t, GetNumberOfQueuedOrders, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION(bool, GetMetaDataValue, TiirEntity*, Entity, RC::Unreal::FString, Key, std::int32_t*, Value)
    WSYS_MEMBER_FUNCTION(float, GetHealthAbsolute, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION(float, GetHealth, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION(TiirEntity, GetEntity_OnPres, SimEntity, Entity)
    WSYS_MEMBER_FUNCTION(TiirEntity, GetEntity, SimEntity, Entity)
    WSYS_MEMBER_FUNCTION(std::int32_t, GetBuildTime, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION_VOID(GatherResource, TiirEntity*, Entity, TiirEntityGroup*, Targets)
    WSYS_MEMBER_FUNCTION(ShipStaticData, FindShipStaticData, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION_VOID(DockInstantly, TiirEntity*, Entity, TiirEntity*, DockTargetEntity)
    WSYS_MEMBER_FUNCTION_VOID(Dock, TiirEntity*, Entity, TiirEntity*, DockTargetEntity, bool, StayDocked, bool, DockOnly)
    WSYS_MEMBER_FUNCTION_VOID(DeployTurretAtPositionAndOrientation, TiirEntity*, Entity, RC::Unreal::FVector, Position, RC::Unreal::FRotator, Orientation, bool, Instantaneous)
    WSYS_MEMBER_FUNCTION_VOID(DeployTurretAtPositionAndNormal, TiirEntity*, Entity, RC::Unreal::FVector*, Position, RC::Unreal::FVector*, Normal, bool, Instantaneous)
    WSYS_MEMBER_FUNCTION_VOID(DeployTurret, TiirEntity*, Entity, bool, Instantaneous)
    WSYS_MEMBER_FUNCTION_VOID(CustomCommand, TiirEntity*, Entity, TiirEntityGroup*, Targets)
    WSYS_MEMBER_FUNCTION(bool, ClearStatusEffects, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION_VOID(ClearRetaliationSetting, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION(bool, ClearModifiers, TiirEntity*, Entity)
    WSYS_MEMBER_FUNCTION_VOID(ChangeOwner, TiirEntity*, Entity, std::int32_t, TargetPlayer)
    WSYS_MEMBER_FUNCTION_VOID(ChangeCommander, TiirEntity*, Entity, TiirCommander*, NewCommander)
    WSYS_MEMBER_FUNCTION_VOID(BindInstantly, TiirEntity*, Entity, TiirEntity*, BindTargetEntity)
    WSYS_MEMBER_FUNCTION_VOID(Attack, TiirEntity*, Entity, TiirEntityGroup*, Targets, bool, MaintainGuard)
    WSYS_MEMBER_FUNCTION(TiirModifierHandle, AddOverrideModifier, TiirEntity*, Entity, SobPropertyType, Property, float, Value, InfluenceType, InfluenceType, float, InfluenceRadius)
    WSYS_MEMBER_FUNCTION(TiirModifierHandle, AddMultiplierModifier, TiirEntity*, Entity, MultiplierType, Multiplier, float, MultiplierValue, InfluenceType, InflenceType, float, InfluenceRadius, ActivityRelation, MultiplierValueRelation, float, MultiplierInterpMinValue)
    WSYS_MEMBER_FUNCTION(TiirModifierHandle, AddAbilityModifier, TiirEntity*, Entity, AbilityType, Ability, bool, abilityState, InfluenceType, InflenceType, float, InfluenceRadius)

    WSYS_MEMBER_FUNCTION(bool, EqualEqual_TiirEntityTiirEntity, TiirEntity*, A, TiirEntity*, B)
    WSYS_MEMBER_FUNCTION(bool, NotEqual_TiirEntityTiirEntity, TiirEntity*, A, TiirEntity*, B)
    
    // to be implemented
    WSYS_MEMBER_FUNCTION_VOID(AddObtainableArtifactToShip, TiirEntity*, Entity, ArtifactStaticData*, ArtifactStaticData)

    WSYS_MEMBER_FUNCTION(bool, DetachScript, TiirEntity*, Entity, TiirScriptInstance*, Script)
    WSYS_MEMBER_FUNCTION(bool, AttachScript, TiirEntity*, Entity, TiirScriptInstance*, Script, float, Interval)

    WSYS_MEMBER_FUNCTION(bool, MatchesTagQuery, TiirEntity*, Entity, GameplayTagQuery*, query)

    WSYS_MEMBER_FUNCTION(bool, RemoveStatusEffectByHandle, TiirStatusEffectHandle*, Handle)
    WSYS_MEMBER_FUNCTION(TiirStatusEffectHandle, AddStatusEffect, TiirEntity*, Entity, StatusEffectStaticData*, StatusEffect)
    WSYS_MEMBER_FUNCTION(bool, HasStatusEffect, TiirEntity*, Entity, StatusEffectStaticData*, StatusEffect)
    WSYS_MEMBER_FUNCTION(bool, RemoveStatusEffect, TiirEntity*, Entity, StatusEffectStaticData*, Status)

    WSYS_MEMBER_FUNCTION_VOID(ApplyEntityStatus, TiirEntity*, Entity, EntityStatus*, Status)
    WSYS_MEMBER_FUNCTION_VOID(RemoveEntityStatus, TiirEntity*, Entity, EntityStatus*, Status)
    // WSYS_MEMBER_FUNCTION_VOID(AddObtainableSoftArtifactToShip, TiirEntity*, Entity, TSoftObjectPtr<UArtifactStaticData>, ArtifactStaticData)
};
