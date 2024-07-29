#pragma once
#include <pch.h>

#include "ShipStaticData.h"
#include "BuildJob.h"

struct BuildJobType 
{
public:
    ShipStaticData Type;
    UC::TArray<BuildJob> Jobs;
    std::int32_t NumShipsInBatch;
    std::int32_t NumShipsRemaining;
    std::int32_t CurrentJobIndex;
    float CurrentJobProgress;
    float TotalRequiredTime;
    float Progress;
    bool bPaused;
};