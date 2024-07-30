#pragma once
#include <pch.h>

#include "UObject.h"
#include "SimPlayer.h"

class RavenHUD : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;
	WSYS_MEMBER_FUNCTION_VOID(ResearchChangedEvent, USimPlayer, player, FResearchData, data, EResearchEvent, event, bool, Restored)
};