#pragma once

#include "UObject.h"

class ShipStaticData : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;

	WSYS_DATA_PROPERTY(RC::Unreal::FText, UnitName)
	WSYS_DATA_PROPERTY(RC::Unreal::FText, UnitDescription)
	WSYS_DATA_PROPERTY(RC::Unreal::FText, UnitFlavourText)
};