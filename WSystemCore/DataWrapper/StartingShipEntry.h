#pragma once
#include <pch.h>

#include "StartingUnitEntry.h"

struct FStartingShipEntry : FStartingUnitEntry 
{
	UC::TArray<FStartingUnitEntry> HoldEntries;
};
