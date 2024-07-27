#pragma once
#include <pch.h>

#include "BuildFamily.h"
#include "EntityStaticData.h"

class ShipStaticData : public EntityStaticData
{
public:
	using EntityStaticData::EntityStaticData;

	WSYS_DATA_PROPERTY(RC::Unreal::FText, UnitName)
	WSYS_DATA_PROPERTY(RC::Unreal::FText, UnitDescription)
	WSYS_DATA_PROPERTY(RC::Unreal::FText, UnitFlavourText)
	WSYS_DATA_PROPERTY(UC::TArray<BuildFamily>, ProductionFamilies)
};