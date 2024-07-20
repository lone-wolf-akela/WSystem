#pragma once
#include <pch.h>

#include "UObject.h"
#include "ResearchData.h"

class SimResearchManager : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;

	WSYS_DATA_PROPERTY(UC::TArray<ResearchData>, ResearchList)
	ResearchData GetResearchState(ResearchStaticData research_data, bool& is_valid) const;
};
