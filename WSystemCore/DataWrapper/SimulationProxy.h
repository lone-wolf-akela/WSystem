#pragma once
#include <pch.h>

#include "UObject.h"
#include "SimPlayer.h"

class SimulationProxy : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;

	using EntityMapType = UC::TMap<std::uint32_t, SimEntity>;

	WSYS_DATA_PROPERTY(UC::TArray<SimPlayer>, SimPlayers)
	WSYS_DATA_PROPERTY(SimPlayer, LocalPlayer)
	WSYS_DATA_PROPERTY(SimPlayer, viewAsPlayer)
	WSYS_DATA_PROPERTY(EntityMapType, EntityMap)
	WSYS_DATA_PROPERTY(SimPlayer, GalaxyPlayer)
	WSYS_DATA_PROPERTY(float, ElapsedTime)
	WSYS_DATA_PROPERTY(std::uint32_t, SimulatingFrame)
	WSYS_DATA_PROPERTY(float, SimulatingDeltaTime)
};