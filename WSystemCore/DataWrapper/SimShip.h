#pragma once
#include <pch.h>

#include <LibWrapper/LibDataTypes.h>
#include "ShipStaticData.h"
#include "SimEntity.h"
#include "StrikeGroupFormationStaticData.h"

class SimShip : public SimEntity
{
public:
	using SimEntity::SimEntity;

	WSYS_DATA_PROPERTY(ShipStaticData, DataAsset)
	WSYS_DATA_PROPERTY(float, ShipScreenSize)
	WSYS_DATA_PROPERTY(float, ShipNormalizedScreenSize)
	WSYS_DATA_PROPERTY(float, ShipAudioSignificance)
	WSYS_DATA_PROPERTY(std::int32_t, SquadronID)
	WSYS_DATA_PROPERTY(bool, IsSquadronLeader)
	WSYS_DATA_PROPERTY(SimShip, SquadronLeader)
	WSYS_DATA_PROPERTY(SquadronStance, SquadronStance)
	WSYS_DATA_PROPERTY(StrikeGroupFormationStaticData, CurrentFormation)
	WSYS_DATA_PROPERTY(Unreal::FText, PilotName)
	WSYS_DATA_PROPERTY(Unreal::FString, CreationMap)
	WSYS_DATA_PROPERTY(float, AudioFocusWeight)
	WSYS_DATA_PROPERTY(float, AudioFocusWeightContextualMultiplier)
	WSYS_DATA_PROPERTY(std::int32_t, AudioFocusRank)
	WSYS_DATA_PROPERTY(float, AudioFocusRankNormalized)
	WSYS_DATA_PROPERTY(std::int32_t, ControlGroupsFlags)
	WSYS_DATA_PROPERTY(bool, IsCenterFocused)
	WSYS_DATA_PROPERTY(TurretDeploymentState, DeployState)
	WSYS_DATA_PROPERTY(Unreal::FVector, DeployLocation)
	WSYS_DATA_PROPERTY(Unreal::FVector, DeployNormal)
	WSYS_DATA_PROPERTY(bool, bDeployedInTacticalPause)
	WSYS_DATA_PROPERTY(bool, IsLatched)
	WSYS_DATA_PROPERTY(float, PrimarySensorRange)
	WSYS_DATA_PROPERTY(float, VisualRange)
	WSYS_DATA_PROPERTY(float, WeaponRange)
	WSYS_DATA_PROPERTY(float, SpecialWeaponRange)
	WSYS_DATA_PROPERTY(float, HealWeaponRange)
	WSYS_DATA_PROPERTY(float, HealSpecialWeaponRange)
	WSYS_DATA_PROPERTY(float, HyperspaceProgress)
	WSYS_DATA_PROPERTY(SimShip, OpposingShip)
	WSYS_DATA_PROPERTY(float, ZombieTime)
	WSYS_DATA_PROPERTY(EntityDeathModifiers, DeathModifiers)
	WSYS_DATA_PROPERTY(float, Significance)
	WSYS_DATA_PROPERTY(float, DistanceToCamera)
	WSYS_DATA_PROPERTY(float, BackstageEffectiveness)
	WSYS_DATA_PROPERTY(SimShip, DockWith)
	WSYS_DATA_PROPERTY(DockingStage, DockingStage)
	WSYS_DATA_PROPERTY(bool, IsDocked)
	WSYS_DATA_PROPERTY(bool, bIsDocking)
	WSYS_DATA_PROPERTY(bool, bHasPower)
	WSYS_DATA_PROPERTY(bool, IsInCombat)
	WSYS_DATA_PROPERTY(bool, bIsHandlingExternalMove)
	WSYS_DATA_PROPERTY(bool, bCanRally)
	WSYS_DATA_PROPERTY(HyperspaceStatus, HyperspaceStatus)
	WSYS_DATA_PROPERTY(SimShip, Parent)
	WSYS_DATA_PROPERTY(UC::TArray<SimShip>, Collectors)
	using AnimationStatesMapType = UC::TMap<SobAnimationState, bool>;
	WSYS_DATA_PROPERTY(AnimationStatesMapType, AnimationStates)
	WSYS_DATA_PROPERTY(UCommandType, ActiveCommandType)
	// TArray<FSimShipAbilityState> AbilityStates;
	// TArray<UStatusEffectStaticData*> CurStatusEffects;

	WSYS_MEMBER_FUNCTION_NOARGS(Unreal::FVector, GetShipVelocity)

	[[nodiscard]] std::wstring GetDataAssetName() const;
	[[nodiscard]] std::string  GetDataAssetNameNarrow() const;
};

