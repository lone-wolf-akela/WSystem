#pragma once
#include <pch.h>

#include "UObject.h"
#include "BuildJobType.h"
#include "EntityStaticData.h"

class ProductionComponent : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;
	
	using UnitTypeQueuesType = UC::TMap<EntityStaticData, BuildJobType>;
	WSYS_DATA_PROPERTY(UnitTypeQueuesType, UnitTypeQueues)

	BuildJobType GetJobTypeState(const EntityStaticData UnitType, bool& bValid, const std::source_location& location = std::source_location::current()) const;
};