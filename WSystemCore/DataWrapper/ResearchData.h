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
};