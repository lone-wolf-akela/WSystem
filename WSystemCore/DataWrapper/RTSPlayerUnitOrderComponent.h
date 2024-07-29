#pragma once
#include <pch.h>

#include "SimOrder.h"
#include "UObject.h"

class RTSPlayerUnitOrderComponent : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;

	WSYS_MEMBER_FUNCTION_VOID(SendOrder, const SimOrder&, Order)
};