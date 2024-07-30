#pragma once
#include <pch.h>

#include "UObject.h"
#include "BuildJobType.h"
#include "EntityStaticData.h"

class UProductionComponent : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;
	
	using UnitTypeQueuesType = UC::TMap<UEntityStaticData, FBuildJobType>;
	WSYS_DATA_PROPERTY(UnitTypeQueuesType, UnitTypeQueues)

	FBuildJobType GetJobTypeState(const UEntityStaticData UnitType, bool& bValid, const std::source_location& location = std::source_location::current()) const;
};