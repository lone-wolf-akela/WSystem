#pragma once
#include <pch.h>

#include "UObject.h"

class WBP_BuildPanel : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;
	WSYS_MEMBER_FUNCTION_VOID_NOARGS(PopulateProductionCategories);
};