#pragma once
#include <pch.h>

#include "SimEntity.h"
#include "MovableStaticData.h"

class SimMovable : public SimEntity
{
public:
	using SimEntity::SimEntity;
	WSYS_DATA_PROPERTY(MovableStaticData, DataAsset)

	[[nodiscard]] std::wstring GetDataAssetName() const;
	[[nodiscard]] std::string  GetDataAssetNameNarrow() const;
};