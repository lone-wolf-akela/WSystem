#pragma once
#include <pch.h>

#include "SimEntity.h"
#include "WeaponFireStaticData.h"

class WeaponFireActor : public SimEntity
{
public:
	using SimEntity::SimEntity;
	WSYS_DATA_PROPERTY(WeaponFireStaticData, DataAsset)

	[[nodiscard]] std::wstring GetDataAssetName() const;
	[[nodiscard]] std::string  GetDataAssetNameNarrow() const;
};
