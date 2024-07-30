#pragma once
#include <pch.h>

#include "EnumDef.h"
#include "UObject.h"

class UResearchStaticData : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;

	WSYS_DATA_PROPERTY(RC::Unreal::FText, ShortDisplayName)
	WSYS_DATA_PROPERTY(RC::Unreal::FText, DisplayName)
	WSYS_DATA_PROPERTY(RC::Unreal::FText, Description)
	WSYS_DATA_PROPERTY(EUpgradeType, UpgradeType)
};
