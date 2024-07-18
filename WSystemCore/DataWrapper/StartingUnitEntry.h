#pragma once
#include <pch.h>

#include <LibWrapper/LibDataTypes.h>
#include "ShipStaticData.h"

struct StartingUnitEntry 
{
    ShipStaticData UnitType;
    SquadronStance UnitStance;
    bool UnitUseRetaliationOverride;
    RetaliationSetting UnitRetaliationOverride;
    bool DoNotRetaliateAgainstMe;
    std::int32_t UnitCount;
};
