#pragma once

#include <ThirdParty/UnrealContainers/UnrealContainers.h>

#include "UObject.h"
#include "SimPlayer.h"

class RavenSimulationProxy : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;

	WSYS_DATA_PROPERTY(UC::TArray<SimPlayer>, SimPlayers)
};
