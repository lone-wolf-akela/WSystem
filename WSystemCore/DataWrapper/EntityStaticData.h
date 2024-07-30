#pragma once
#include <pch.h>

#include "UObject.h"
#include "BuildFamily.h"

class UEntityStaticData : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;

	WSYS_DATA_PROPERTY(UBuildFamily, BuildFamily)
};