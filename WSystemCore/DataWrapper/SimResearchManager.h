#pragma once
#include <pch.h>

#include "UObject.h"
#include "ResearchData.h"

class USimResearchManager : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;

	WSYS_DATA_PROPERTY(UC::TArray<FResearchData>, ResearchList)
	FResearchData GetResearchState(UResearchStaticData research_data, bool& is_valid, const std::source_location& location = std::source_location::current()) const;
};
