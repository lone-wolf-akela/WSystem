#pragma once
#include <cstdint>

#include <Unreal/Transform.hpp>
#include <Unreal/Rotator.hpp>

#include <DataWrapper/SimEntity.h>
#include <DataWrapper/ShipStaticData.h>

#include "LibBase.h"
#include "LibDataTypes.h"

class StatusEffectStaticData;
class EntityStatus;
class GameplayTagQuery;
class ArtifactStaticData;
class TiirScriptInstance;
class StrikeGroupFormationStaticData;
class TiirGroupQuery;
class WeaponStaticData;
class TiirShipSpawner;
class AttackFamily;

class TiirEntityGroupFunctionLibrary : public LibBase<TiirEntityGroupFunctionLibrary>
{
public:
	static constexpr auto LibPath = STR("/Script/RavenSimulation.TiirEntityGroupFunctionLibrary");

	WSYS_MEMBER_FUNCTION_VOID(UndeployTurret, TiirEntityGroup*, Group, bool, Instantaneous)
	WSYS_MEMBER_FUNCTION_VOID(ToggleAlternativeShipOrientation, TiirEntityGroup*, Group)
	WSYS_MEMBER_FUNCTION_VOID(Teleport, TiirEntityGroup*, Group, RC::Unreal::FTransform, Transform, bool, TeleportShipsInParade)
	WSYS_MEMBER_FUNCTION_VOID(TakeDamageAbsolute, TiirEntityGroup*, Group, float, DamageAbsolute)
	WSYS_MEMBER_FUNCTION_VOID(TakeDamage, TiirEntityGroup*, Group, float, DamagePercentage)
	WSYS_MEMBER_FUNCTION_VOID(Stop, TiirEntityGroup*, Group)
	WSYS_MEMBER_FUNCTION_VOID(Spawn, TiirEntityGroup*, Group, RC::Unreal::FTransform, Transform, bool, SkipPlacementLogic)
	WSYS_MEMBER_FUNCTION_VOID(SetVelocity, TiirEntityGroup*, Group, RC::Unreal::FVector, Velocity)
	WSYS_MEMBER_FUNCTION_VOID(SetTransform, TiirEntityGroup*, Group, RC::Unreal::FTransform, Transform)
	WSYS_MEMBER_FUNCTION_VOID(SetTactics, TiirEntityGroup*, Group, SquadronTactics, Tactics)
	WSYS_MEMBER_FUNCTION_VOID(SetStance, TiirEntityGroup*, Group, SquadronStance, Stance)
	WSYS_MEMBER_FUNCTION_VOID(SetRotation, TiirEntityGroup*, Group, RC::Unreal::FRotator, Rotation)
	WSYS_MEMBER_FUNCTION_VOID(SetNoRetaliate, TiirEntityGroup*, Group, bool, Enabled)
	WSYS_MEMBER_FUNCTION_VOID(SetLocation, TiirEntityGroup*, Group, RC::Unreal::FVector, Location)
	WSYS_MEMBER_FUNCTION_VOID(SetInvincible, TiirEntityGroup*, Group, bool, Enabled)
	WSYS_MEMBER_FUNCTION_VOID(SetIgnoreForPersistentFleet, TiirEntityGroup*, Group, bool, Enabled)
	WSYS_MEMBER_FUNCTION_VOID(SetIgnoreDamage, TiirEntityGroup*, Group, bool, Enabled)
	WSYS_MEMBER_FUNCTION_VOID(SetHealth, TiirEntityGroup*, Group, float, HealthPercentage)
	WSYS_MEMBER_FUNCTION_VOID(SetGhost, TiirEntityGroup*, Group, bool, Enabled)
	WSYS_MEMBER_FUNCTION_VOID(SetCloaking, TiirEntityGroup*, Group, bool, Enabled)
	WSYS_MEMBER_FUNCTION_VOID(SetAutoLaunch, TiirEntityGroup*, Group, AutoLaunchSetting, AutoLaunchSetting)
	WSYS_MEMBER_FUNCTION_VOID(Scuttle, TiirEntityGroup*, Group)
	WSYS_MEMBER_FUNCTION_VOID(SalvageCapture, TiirEntityGroup*, Group, TiirEntityGroup*, Targets)
	WSYS_MEMBER_FUNCTION_VOID(RevealInFow, TiirEntityGroup*, Group, bool, Revealed)
	WSYS_MEMBER_FUNCTION_VOID(RetireTo, TiirEntityGroup*, Group, TiirEntity*, Target)
	WSYS_MEMBER_FUNCTION_VOID(Retire, TiirEntityGroup*, Group)
	WSYS_MEMBER_FUNCTION_VOID(Repair, TiirEntityGroup*, Group, TiirEntityGroup*, Targets)
	WSYS_MEMBER_FUNCTION_VOID(RemoveObtainableArtifactFromShips, TiirEntityGroup*, Group)
	WSYS_MEMBER_FUNCTION_VOID(ParadeAround, TiirEntityGroup*, Group, TiirEntity*, ParadeAroundEntity, ParadeMode, ParadeMode)
	WSYS_MEMBER_FUNCTION_VOID(OverrideRetaliationSetting, TiirEntityGroup*, Group, RetaliationSetting, TheRetaliationSetting)
	WSYS_MEMBER_FUNCTION_VOID(MoveTo, TiirEntityGroup*, Group, RC::Unreal::FVector, Destination, bool, AttackMove)
	WSYS_MEMBER_FUNCTION_VOID(MovePingPong, TiirEntityGroup*, Group, UC::TArray<RC::Unreal::FVector>*, Locations, bool, AttackMove)
	WSYS_MEMBER_FUNCTION_VOID(MoveAlong, TiirEntityGroup*, Group, UC::TArray<RC::Unreal::FVector>*, Path, bool, Loop, bool, AttackMove)
	WSYS_MEMBER_FUNCTION(TiirEntityGroup, MakeGroupFromActor, SimEntity, Entity)
	WSYS_MEMBER_FUNCTION_VOID(MakeDead, TiirEntityGroup*, Group, EntityDeathModifiers*, DeathModifiers)
	WSYS_MEMBER_FUNCTION_VOID(LaunchSelf, TiirEntityGroup*, Group)
	WSYS_MEMBER_FUNCTION_VOID(LaunchAll, TiirEntityGroup*, Group)
	WSYS_MEMBER_FUNCTION_VOID(LatchInstantly, TiirEntityGroup*, Group, TiirEntityGroup*, LatchTargetEntity)
	WSYS_MEMBER_FUNCTION_VOID(KillUnit, TiirEntityGroup*, Group, bool, byDamage)
	WSYS_MEMBER_FUNCTION_VOID(Kamikaze, TiirEntityGroup*, Group, TiirEntityGroup*, TargetGroup)
	WSYS_MEMBER_FUNCTION(bool, IsWithinPlayerSensorRange, TiirEntityGroup*, Group, std::int32_t, TargetPlayer)
	WSYS_MEMBER_FUNCTION(bool, IsInHyperspace, TiirEntityGroup*, Group)
	WSYS_MEMBER_FUNCTION(bool, IsGroupInCombat, TiirEntityGroup*, Group, bool, RequireEveryone)
	WSYS_MEMBER_FUNCTION(bool, IsDeSpawned, TiirEntityGroup*, Group)
	WSYS_MEMBER_FUNCTION(bool, IsCloaking, TiirEntityGroup*, Group, bool, RequireAll)
	WSYS_MEMBER_FUNCTION_VOID(HyperspaceToDestination, TiirEntityGroup*, Group, RC::Unreal::FTransform, Destination, bool, SkipPlacementLogic)
	WSYS_MEMBER_FUNCTION_VOID(HyperspaceExit, TiirEntityGroup*, Group, RC::Unreal::FTransform, Transform, bool, SkipPlacementLogic)
	WSYS_MEMBER_FUNCTION_VOID(HyperspaceEnter, TiirEntityGroup*, Group)
	WSYS_MEMBER_FUNCTION_VOID(Guard, TiirEntityGroup*, Group, TiirEntityGroup*, Targets)
	WSYS_MEMBER_FUNCTION(std::int32_t, GroupRemoveEntity, TiirEntityGroup*, Group, TiirEntity*, Entity)
	WSYS_MEMBER_FUNCTION(std::int32_t, GroupRemove, TiirEntityGroup*, Group, TiirEntityGroup*, SourceGroup)
	WSYS_MEMBER_FUNCTION(std::int32_t, GroupPurgeDead, TiirEntityGroup*, Group)
	WSYS_MEMBER_FUNCTION(std::int32_t, GroupPurgeAlive, TiirEntityGroup*, Group)
	WSYS_MEMBER_FUNCTION_VOID(GroupMembers, TiirEntityGroup*, Group, UC::TArray<TiirEntity>*, Members)
	WSYS_MEMBER_FUNCTION(std::int32_t, GroupCountFiltered, TiirEntityGroup*, Group, TiirGroupCountFilter*, Filter)
	WSYS_MEMBER_FUNCTION(std::int32_t, GroupCount, TiirEntityGroup*, Group)
	WSYS_MEMBER_FUNCTION_VOID(GroupClear, TiirEntityGroup*, Group)
	WSYS_MEMBER_FUNCTION(std::int32_t, GroupAddEntity, TiirEntityGroup*, Group, TiirEntity*, Entity)
	WSYS_MEMBER_FUNCTION(std::int32_t, GroupAdd, TiirEntityGroup*, Group, TiirEntityGroup*, SourceGroup)
	WSYS_MEMBER_FUNCTION(RC::Unreal::FVector, GetPosition, TiirEntityGroup*, Group)
	WSYS_MEMBER_FUNCTION(RC::Unreal::FRotator, GetOrientation, TiirEntityGroup*, Group)
	WSYS_MEMBER_FUNCTION(RC::Unreal::FString, GenerateDebugString, TiirEntityGroup*, Group)
	WSYS_MEMBER_FUNCTION_VOID(GatherResource, TiirEntityGroup*, Group, TiirEntityGroup*, Targets)
	WSYS_MEMBER_FUNCTION(std::int32_t, FillGroupIncludingPlayer, TiirEntityGroup*, Group, TiirEntityGroup*, SourceGroup, TiirCommander*, OwningPlayer)
	WSYS_MEMBER_FUNCTION(std::int32_t, FillGroupFromPlayerMothershipList, TiirEntityGroup*, Group, std::int32_t, OwningPlayer, bool, IncludeDead)
	WSYS_MEMBER_FUNCTION(std::int32_t, FillGroupFromPlayer, TiirEntityGroup*, Group, std::int32_t, OwningPlayer, bool, IncludeDocked, bool, IncludeInHyperspace, bool, IncludeDead)
	WSYS_MEMBER_FUNCTION(std::int32_t, FillGroupExcludingPlayer, TiirEntityGroup*, Group, TiirEntityGroup*, SourceGroup, std::int32_t, ExcludingPlayer)
	WSYS_MEMBER_FUNCTION(std::int32_t, FillGroupByProximityToLocation, TiirEntityGroup*, Group, TiirEntityGroup*, SourceGroup, RC::Unreal::FVector, Location, RC::Unreal::FVector, Distance)
	WSYS_MEMBER_FUNCTION(std::int32_t, FillGroupByProximityToGroup, TiirEntityGroup*, Group, TiirEntityGroup*, SourceGroup, TiirEntityGroup*, NearGroup, RC::Unreal::FVector, Distance)
	WSYS_MEMBER_FUNCTION_VOID(DockInstantly, TiirEntityGroup*, Group, TiirEntityGroup*, DockTargetEntityGroup)
	WSYS_MEMBER_FUNCTION_VOID(Dock, TiirEntityGroup*, Group, TiirEntityGroup*, DockTargetEntityGroup, bool, StayDocked, bool, DockOnly)
	WSYS_MEMBER_FUNCTION_VOID(DisbandStrikeGroup, TiirEntityGroup*, Group)
	WSYS_MEMBER_FUNCTION_VOID(Despawn, TiirEntityGroup*, Group, bool, IgnoreActiveCommands)
	WSYS_MEMBER_FUNCTION_VOID(DeployTurretAtPositionAndOrientation, TiirEntityGroup*, Group, RC::Unreal::FVector, Position, RC::Unreal::FRotator, Orientation, bool, Instantaneous)
	WSYS_MEMBER_FUNCTION_VOID(DeployTurretAtPositionAndNormal, TiirEntityGroup*, Group, RC::Unreal::FVector, Position, RC::Unreal::FVector, Normal, bool, Instantaneous)
	WSYS_MEMBER_FUNCTION_VOID(DeployTurret, TiirEntityGroup*, Group, bool, Instantaneous)
	WSYS_MEMBER_FUNCTION_VOID(CustomCommand, TiirEntityGroup*, Group, TiirEntityGroup*, Targets)
	WSYS_MEMBER_FUNCTION(std::int32_t, CountShipTypePresentInGroup, TiirEntityGroup*, Group, UC::TArray<ShipStaticData>, FilterTypes)
	WSYS_MEMBER_FUNCTION_VOID(ClearStatusEffects, TiirEntityGroup*, Group)
	WSYS_MEMBER_FUNCTION_VOID(ClearRetaliationSetting, TiirEntityGroup*, Group)
	WSYS_MEMBER_FUNCTION_VOID(ChangeOwner, TiirEntityGroup*, Group, std::int32_t, TargetPlayer)
	WSYS_MEMBER_FUNCTION_VOID(ChangeCommander, TiirEntityGroup*, Group, TiirCommander*, NewCommander)
	WSYS_MEMBER_FUNCTION_VOID(BindInstantly, TiirEntityGroup*, Group, TiirEntityGroup*, BindTargetEntity)
	WSYS_MEMBER_FUNCTION_VOID(AttackPlayer, TiirEntityGroup*, Group, std::int32_t, TargetPlayer, bool, CanAttackCloakedUnits)
	WSYS_MEMBER_FUNCTION_VOID(Attack, TiirEntityGroup*, Group, TiirEntityGroup*, TargetGroup, bool, MaintainGuard, bool, CanAttackCloakedUnits)
	WSYS_MEMBER_FUNCTION(std::int32_t, FillGroupFromFilteredType, TiirEntityGroup*, Group, TiirEntityGroup*, SourceGroup, UC::TArray<EntityStaticData>, DesiredTypes)

	// to be implemented
	WSYS_MEMBER_FUNCTION(std::int32_t, CountAttackFamilyPresentInGroup, TiirEntityGroup*, Group, UC::TArray<AttackFamily*>, FilterTypes)
	WSYS_MEMBER_FUNCTION(std::int32_t, FillGroupFromFilteredFamily, TiirEntityGroup*, Group, TiirEntityGroup*, SourceGroup, UC::TArray<AttackFamily*>, DesiredTypes)

	WSYS_MEMBER_FUNCTION_VOID(CreateShip, TiirEntityGroup*, Group, TiirShipSpawner*, ShipSpawner, std::int32_t, OwningPlayer, bool, StartInHyperspace, bool, SkipPlacementLogic)

	WSYS_MEMBER_FUNCTION(std::int32_t, FillGroupWithTagQueryMatches, TiirEntityGroup*, Group, TiirEntityGroup*, SourceGroup, GameplayTagQuery*, query)

	WSYS_MEMBER_FUNCTION(bool, FireAtNoTarget, TiirEntityGroup*, Group, WeaponStaticData*, WeaponType, bool, AllSourcesFire, RC::Unreal::FName, FireFromSocket, RC::Unreal::FVector, MuzzleOffset)
	WSYS_MEMBER_FUNCTION(bool, FireAt, TiirEntityGroup*, Group, TiirEntityGroup*, TargetGroup, WeaponStaticData*, WeaponType, bool, AllSourcesFire, bool, FireAtAllTargets, RC::Unreal::FName, FireFromSocket, RC::Unreal::FVector, MuzzleOffset)

	WSYS_MEMBER_FUNCTION(TiirEntityGroup, QueryGroupByProximity, TiirGroupQuery*, query, RC::Unreal::FVector, Location, float, Radius)

	WSYS_MEMBER_FUNCTION_VOID(RemoveStatusEffectsByHandles, UC::TArray<TiirStatusEffectHandle>*, Handles)
	WSYS_MEMBER_FUNCTION_VOID(RemoveStatusEffect, TiirEntityGroup*, Group, StatusEffectStaticData*, Status)
	WSYS_MEMBER_FUNCTION(bool, HasStatusEffect, TiirEntityGroup*, Group, StatusEffectStaticData*, StatusEffect, bool, CheckForAll)
	WSYS_MEMBER_FUNCTION_VOID(RemoveEntityStatus, TiirEntityGroup*, Group, EntityStatus*, Status)
	WSYS_MEMBER_FUNCTION_VOID(ApplyEntityStatus, TiirEntityGroup*, Group, EntityStatus*, Status)
	WSYS_MEMBER_FUNCTION_VOID(AddStatusEffect, TiirEntityGroup*, Group, StatusEffectStaticData*, Status, UC::TArray<TiirStatusEffectHandle>*, OutHandles)

	WSYS_MEMBER_FUNCTION_VOID(SetStrikeGroupFormation, TiirEntityGroup*, Group, StrikeGroupFormationStaticData*, Formation)
		
	// WSYS_MEMBER_FUNCTION_VOID(AddObtainableSoftArtifactToShips, TiirEntityGroup*, Group, TSoftObjectPtr<UArtifactStaticData>, ArtifactStaticData)
	WSYS_MEMBER_FUNCTION_VOID(AddObtainableArtifactToShips, TiirEntityGroup*, Group, ArtifactStaticData*, ArtifactStaticData)
};