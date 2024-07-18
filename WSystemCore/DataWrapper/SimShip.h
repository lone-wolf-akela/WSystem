#pragma once
#include <pch.h>

#include "ShipStaticData.h"
#include "SimEntity.h"

class SimShip : public SimEntity
{
public:
	using SimEntity::SimEntity;

	WSYS_DATA_PROPERTY(ShipStaticData, DataAsset)
};
