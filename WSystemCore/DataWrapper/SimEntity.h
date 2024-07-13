#pragma once

#include "UObject.h"

class SimEntity : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;

	[[nodiscard]] WSYS_MEMBER_FUNCTION_NOARGS(bool, IsShip)
	[[nodiscard]] WSYS_MEMBER_FUNCTION_NOARGS(bool, IsAlive)
};
