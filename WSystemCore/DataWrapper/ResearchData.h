#pragma once
#include <pch.h>

#include "ResearchStaticData.h"
#include "ShipStaticData.h"

enum class ResearchState : std::int8_t
{
    Restricted,
    Locked,
    Pending,
    InProgress,
    Done,
};

struct ResearchData 
{
    ResearchStaticData StaticData;
    ShipStaticData ShipData;
    void* ResearchFamilyData;
    ResearchState State;
    bool Paused;
    float Progress;
};