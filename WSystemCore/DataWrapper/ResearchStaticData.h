#pragma once
#include <pch.h>

#include "UObject.h"

class ResearchStaticData : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;

	WSYS_DATA_PROPERTY(RC::Unreal::FText, ShortDisplayName)
	WSYS_DATA_PROPERTY(RC::Unreal::FText, DisplayName)
	WSYS_DATA_PROPERTY(RC::Unreal::FText, Description)
};
