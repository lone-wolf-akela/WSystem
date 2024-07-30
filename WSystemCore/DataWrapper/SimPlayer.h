#pragma once
#include <pch.h>

#include "UObject.h"
#include "SimResearchManager.h"
#include "SimEntity.h"

class USimPlayer : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;

	WSYS_DATA_PROPERTY(RC::Unreal::FString, PlayerName)
	WSYS_DATA_PROPERTY(USimResearchManager, ResearchManager)
	WSYS_DATA_PROPERTY(UC::TArray<ASimEntity>, OwnedSimObjects)
	WSYS_DATA_PROPERTY(std::int32_t, TeamID)
	WSYS_DATA_PROPERTY(bool, IsHuman)
};