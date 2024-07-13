#pragma once

#include <ThirdParty/UnrealContainers/UnrealContainers.h>

#include "UObject.h"
#include "SimResearchManager.h"
#include "SimEntity.h"

class SimPlayer : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;

	WSYS_DATA_PROPERTY(RC::Unreal::FString, PlayerName)
	WSYS_DATA_PROPERTY(SimResearchManager, ResearchManager)
	WSYS_DATA_PROPERTY(UC::TArray<SimEntity>, OwnedSimObjects)
};