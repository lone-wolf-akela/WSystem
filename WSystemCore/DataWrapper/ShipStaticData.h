#pragma once

#include "EntityStaticData.h"

class ShipStaticData : public EntityStaticData
{
public:
	using EntityStaticData::EntityStaticData;

	WSYS_DATA_PROPERTY(RC::Unreal::FText, UnitName)
	WSYS_DATA_PROPERTY(RC::Unreal::FText, UnitDescription)
	WSYS_DATA_PROPERTY(RC::Unreal::FText, UnitFlavourText)
};