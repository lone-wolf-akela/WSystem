#pragma once
#include <pch.h>

#include "UObject.h"

class SimEntity : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;

	WSYS_DATA_PROPERTY(std::int32_t, PlayerOwner)
	WSYS_DATA_PROPERTY(std::int32_t, SimID)

	[[nodiscard]] WSYS_MEMBER_FUNCTION_NOARGS(bool, IsShip)
	[[nodiscard]] WSYS_MEMBER_FUNCTION_NOARGS(bool, IsAlive)
};
