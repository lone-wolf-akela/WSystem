#pragma once
#include <pch.h>

#include "UObject.h"
#include "SimPlayer.h"

class ASimulationProxy : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;

	using EntityMapType = UC::TMap<std::uint32_t, ASimEntity>;

	WSYS_DATA_PROPERTY(UC::TArray<USimPlayer>, SimPlayers)
	WSYS_DATA_PROPERTY(USimPlayer, LocalPlayer)
	WSYS_DATA_PROPERTY(USimPlayer, viewAsPlayer)
	WSYS_DATA_PROPERTY(EntityMapType, EntityMap)
	WSYS_DATA_PROPERTY(USimPlayer, GalaxyPlayer)
	WSYS_DATA_PROPERTY(float, ElapsedTime)
	WSYS_DATA_PROPERTY(std::uint32_t, SimulatingFrame)
	WSYS_DATA_PROPERTY(float, SimulatingDeltaTime)
};