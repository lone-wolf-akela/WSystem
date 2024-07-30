#pragma once
#include <pch.h>

#include "ShipStaticData.h"
#include "BuildJob.h"

struct FBuildJobType 
{
public:
    UShipStaticData Type;
    UC::TArray<FBuildJob> Jobs;
    std::int32_t NumShipsInBatch;
    std::int32_t NumShipsRemaining;
    std::int32_t CurrentJobIndex;
    float CurrentJobProgress;
    float TotalRequiredTime;
    float Progress;
    bool bPaused;
};