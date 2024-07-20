#pragma once
#include <pch.h>

#include <LibWrapper/LibDataTypes.h>

#include "UObject.h"
#include "StrikeGroupFormationStaticData.h"

class UnitOrderStaticData : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;
	WSYS_DATA_PROPERTY(SquadronStance, SquadronStance)
	WSYS_DATA_PROPERTY(SquadronTactics, SquadronTactics)
	WSYS_DATA_PROPERTY(StrikeGroupFormationStaticData, StrikeGroupFormationData)
};
