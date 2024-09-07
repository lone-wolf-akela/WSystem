#pragma once
#include <pch.h>

#include "ResearchStaticData.h"
#include "ShipStaticData.h"


struct FResearchData 
{
    UResearchStaticData StaticData;
    UShipStaticData ShipData;
    void* ResearchFamilyData;
    EResearchState State;
    bool Paused;
    float Progress;
    int32_t QueuePosition;
    int32_t FamilyQueuePosition;
};