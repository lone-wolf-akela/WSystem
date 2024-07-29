#pragma once
#include <pch.h>

#include "UObject.h"
#include "RTSPlayerUnitOrderComponent.h"
#include "SimulationProxy.h"

class RTSPlayerController : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;
	WSYS_DATA_PROPERTY(RTSPlayerUnitOrderComponent, UnitOrderComponent)

	WSYS_MEMBER_FUNCTION_VOID(SetDebugTimeDilation, const float, TimeDilation)
	WSYS_MEMBER_FUNCTION_NOARGS(SimulationProxy, GetSimulationProxy)
};