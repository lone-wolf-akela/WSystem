#pragma once
#include <pch.h>

#include <LibWrapper/LibDataTypes.h>
#include "ShipStaticData.h"
#include "SimEntity.h"
#include "StrikeGroupFormationStaticData.h"
#include "ProductionComponent.h"

class ASimShip : public ASimEntity
{
public:
	using ASimEntity::ASimEntity;

	WSYS_DATA_PROPERTY(UShipStaticData, DataAsset)
	WSYS_DATA_PROPERTY(float, ShipScreenSize)
	WSYS_DATA_PROPERTY(float, ShipNormalizedScreenSize)
	WSYS_DATA_PROPERTY(float, ShipAudioSignificance)
	WSYS_DATA_PROPERTY(std::int32_t, SquadronID)
	WSYS_DATA_PROPERTY(bool, IsSquadronLeader)
	WSYS_DATA_PROPERTY(ASimShip, SquadronLeader)
	WSYS_DATA_PROPERTY(ESquadronStance, SquadronStance)
	WSYS_DATA_PROPERTY(UStrikeGroupFormationStaticData, CurrentFormation)
	WSYS_DATA_PROPERTY(Unreal::FText, PilotName)
	WSYS_DATA_PROPERTY(Unreal::FString, CreationMap)
	WSYS_DATA_PROPERTY(float, AudioFocusWeight)
	WSYS_DATA_PROPERTY(float, AudioFocusWeightContextualMultiplier)
	WSYS_DATA_PROPERTY(std::int32_t, AudioFocusRank)
	WSYS_DATA_PROPERTY(float, AudioFocusRankNormalized)
	WSYS_DATA_PROPERTY(std::int32_t, ControlGroupsFlags)
	WSYS_DATA_PROPERTY(bool, IsCenterFocused)
	WSYS_DATA_PROPERTY(ETurretDeploymentState, DeployState)
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
	WSYS_DATA_PROPERTY(ASimShip, OpposingShip)
	WSYS_DATA_PROPERTY(float, ZombieTime)
	WSYS_DATA_PROPERTY(EntityDeathModifiers, DeathModifiers)
	WSYS_DATA_PROPERTY(float, Significance)
	WSYS_DATA_PROPERTY(float, DistanceToCamera)
	WSYS_DATA_PROPERTY(float, BackstageEffectiveness)
	WSYS_DATA_PROPERTY(ASimShip, DockWith)
	WSYS_DATA_PROPERTY(EDockingStage, DockingStage)
	WSYS_DATA_PROPERTY(bool, IsDocked)
	WSYS_DATA_PROPERTY(bool, bIsDocking)
	WSYS_DATA_PROPERTY(bool, bHasPower)
	WSYS_DATA_PROPERTY(bool, IsInCombat)
	WSYS_DATA_PROPERTY(bool, bIsHandlingExternalMove)
	WSYS_DATA_PROPERTY(bool, bCanRally)
	WSYS_DATA_PROPERTY(EHyperspaceStatus, HyperspaceStatus)
	WSYS_DATA_PROPERTY(ASimShip, Parent)
	WSYS_DATA_PROPERTY(UC::TArray<ASimShip>, Collectors)
	using AnimationStatesMapType = UC::TMap<ESobAnimationState, bool>;
	WSYS_DATA_PROPERTY(AnimationStatesMapType, AnimationStates)
	WSYS_DATA_PROPERTY(UCommandType, ActiveCommandType)
	// TArray<FSimShipAbilityState> AbilityStates;
	// TArray<UStatusEffectStaticData*> CurStatusEffects;
	WSYS_DATA_PROPERTY(UProductionComponent, ProductionComponent)

	WSYS_MEMBER_FUNCTION_NOARGS(Unreal::FVector, GetShipVelocity)
	WSYS_MEMBER_FUNCTION_VOID(ReceiveAnimationStateChanged, const ESobAnimationState, AnimationState, const UC::TArray<ESobAnimationState>&, ImplicitAnimationStateChanges)

	[[nodiscard]] std::wstring GetDataAssetName() const;
	[[nodiscard]] std::string  GetDataAssetNameNarrow() const;
};

