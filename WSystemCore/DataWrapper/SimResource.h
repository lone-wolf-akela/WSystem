#pragma once
#include <pch.h>

#include "SimEntity.h"
#include "ResourceStaticData.h"

class ASimResource : public ASimEntity
{
public:
	using ASimEntity::ASimEntity;
	WSYS_DATA_PROPERTY(UResourceStaticData, DataAsset)

	[[nodiscard]] std::wstring GetDataAssetName() const;
	[[nodiscard]] std::string  GetDataAssetNameNarrow() const;
};