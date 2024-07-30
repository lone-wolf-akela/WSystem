#pragma once
#include <pch.h>

#include <LibWrapper/LibDataTypes.h>

#include "UObject.h"
#include "StrikeGroupFormationStaticData.h"

class UUnitOrderStaticData : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;
	WSYS_DATA_PROPERTY(ESquadronStance, SquadronStance)
	WSYS_DATA_PROPERTY(ESquadronTactics, SquadronTactics)
	WSYS_DATA_PROPERTY(UStrikeGroupFormationStaticData, StrikeGroupFormationData)
};
