#pragma once
#include <pch.h>

#include "StartingUnitEntry.h"

struct StartingShipEntry : StartingUnitEntry 
{
	UC::TArray<StartingUnitEntry> HoldEntries;
};
