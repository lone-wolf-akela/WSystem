#pragma once
#include <pch.h>

#include "UObject.h"

#include <LibWrapper/LibDataTypes.h>

#include "ShipStaticData.h"
#include "StartingUnitEntry.h"
#include "StartingShipEntry.h"
#include "StatusEffectStaticData.h"

class EntityStatus;

class ATiirShipSpawner : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;

	WSYS_DATA_PROPERTY(bool, AutoSpawn)
    WSYS_DATA_PROPERTY(UShipStaticData, ShipType)
    WSYS_DATA_PROPERTY(std::int32_t, ShipCount)
    WSYS_DATA_PROPERTY(std::int32_t, OwningPlayer)
    WSYS_DATA_PROPERTY(RC::Unreal::FString, GroupName)
    WSYS_DATA_PROPERTY(RC::Unreal::FString, SquadronName)
    WSYS_DATA_PROPERTY(ESquadronStance, Stance)
    WSYS_DATA_PROPERTY(bool, UseRetaliationOverride)
    WSYS_DATA_PROPERTY(ERetaliationSetting, RetaliationOverride)
    WSYS_DATA_PROPERTY(bool, DoNotRetaliateAgainstMe)
    WSYS_DATA_PROPERTY(UC::TArray<FStartingUnitEntry>, HoldEntries)
    WSYS_DATA_PROPERTY(UC::TArray<FStartingShipEntry>, SupportingShips)
    WSYS_DATA_PROPERTY(UC::TArray<EntityStatus*>, ActiveStatuses)
    WSYS_DATA_PROPERTY(UC::TArray<UStatusEffectStaticData>, ActiveStatusEffects)
};
