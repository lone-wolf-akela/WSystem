#pragma once
#include <pch.h>

#include "SimEntity.h"
#include "WeaponFireStaticData.h"

class AWeaponFireActor : public ASimEntity
{
public:
	using ASimEntity::ASimEntity;
	WSYS_DATA_PROPERTY(UWeaponFireStaticData, DataAsset)

	[[nodiscard]] std::wstring GetDataAssetName() const;
	[[nodiscard]] std::string  GetDataAssetNameNarrow() const;
};
