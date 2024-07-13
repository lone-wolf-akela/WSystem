#pragma once
#include <Unreal/UFunction.hpp>

#include "UObject.h"

class RTSLevelScriptActor : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;

	WSYS_MEMBER_FUNCTION_VOID_NOARGS(TiirTick)
};