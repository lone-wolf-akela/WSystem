#pragma once
#include <pch.h>

#include "UObject.h"
#include "BuildFamily.h"

class EntityStaticData : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;

	WSYS_DATA_PROPERTY(BuildFamily, BuildFamily)
};