#pragma once
#include <pch.h>

#include <LibWrapper/LibDataTypes.h>
#include "ShipStaticData.h"

struct FStartingUnitEntry 
{
    UShipStaticData UnitType;
    ESquadronStance UnitStance;
    bool UnitUseRetaliationOverride;
    ERetaliationSetting UnitRetaliationOverride;
    bool DoNotRetaliateAgainstMe;
    std::int32_t UnitCount;
};
