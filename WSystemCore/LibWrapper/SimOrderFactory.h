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
	WSYS_MEMBER_FUNCTION(SimOrder, MakeCancelBuildOrder, const SimPlayer, Player, const SimEntity, Builder, const BuildCancelType, cancelBuildType, const std::int32_t, buildJobID, const BuildFamily, cancelFamily)
	WSYS_MEMBER_FUNCTION(SimOrder, MakeTogglePauseBuildOrder, const SimPlayer, Player, const SimEntity, Builder, const bool, Pause, const BuildPauseType, buildPauseType, const std::int32_t, buildJobID, const BuildFamily, buildFamily);
};