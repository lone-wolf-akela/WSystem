#pragma once
#include <pch.h>

#include "SimEntity.h"
#include "ResourceStaticData.h"

class SimResource : public SimEntity
{
public:
	using SimEntity::SimEntity;
	WSYS_DATA_PROPERTY(ResourceStaticData, DataAsset)

	[[nodiscard]] std::wstring GetDataAssetName() const;
	[[nodiscard]] std::string  GetDataAssetNameNarrow() const;
};