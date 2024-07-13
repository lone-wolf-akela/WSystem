#pragma once

#include "UObject.h"
#include "SimPlayer.h"

enum class ResearchEvent : std::uint8_t 
{
	ResearchStart,
	ResearchCancel,
	ResearchComplete,
	ResearchNoRU,
	ResearchAvailable,
	InstaResearchComplete,
	ResearchInProgress,
	ResearchRestricted,
	ResearchUnrestricted,
	ResearchPaused,
	ResearchUnpaused,
	_ResearchEventNum,
};

class RavenHUD : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;
	WSYS_MEMBER_FUNCTION_VOID(ResearchChangedEvent, SimPlayer, player, ResearchData, data, ResearchEvent, event, bool, Restored)
};