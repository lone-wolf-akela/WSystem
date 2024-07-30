#pragma once
#include <pch.h>

#include <DataWrapper/SimOrder.h>
#include <DataWrapper/SimPlayer.h>
#include <DataWrapper/SimEntity.h>
#include <DataWrapper/BuildFamily.h>

#include "LibBase.h"
#include "LibDataTypes.h"

class SimOrderFactory : public LibBase<SimOrderFactory>
{
public:
	static constexpr auto LibPath = STR("/Script/RavenSimulation.SimOrderFactory");
	WSYS_MEMBER_FUNCTION(FSimOrder, MakeCancelBuildOrder, const USimPlayer, Player, const ASimEntity, Builder, const EBuildCancelType, cancelBuildType, const std::int32_t, buildJobID, const UBuildFamily, cancelFamily)
	WSYS_MEMBER_FUNCTION(FSimOrder, MakeTogglePauseBuildOrder, const USimPlayer, Player, const ASimEntity, Builder, const bool, Pause, const EBuildPauseType, buildPauseType, const std::int32_t, buildJobID, const UBuildFamily, buildFamily);
};