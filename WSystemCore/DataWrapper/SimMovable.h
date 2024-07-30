#pragma once
#include <pch.h>

#include "SimEntity.h"
#include "MovableStaticData.h"

class ASimMovable : public ASimEntity
{
public:
	using ASimEntity::ASimEntity;
	WSYS_DATA_PROPERTY(UMovableStaticData, DataAsset)

	[[nodiscard]] std::wstring GetDataAssetName() const;
	[[nodiscard]] std::string  GetDataAssetNameNarrow() const;
};