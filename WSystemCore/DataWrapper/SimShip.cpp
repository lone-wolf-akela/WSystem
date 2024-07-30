#include <pch.h>
#include "SimShip.h"

std::wstring ASimShip::GetDataAssetName() const
{
	return DataAsset->GetName();
}

std::string ASimShip::GetDataAssetNameNarrow() const
{
	return boost::nowide::narrow(GetDataAssetName());
}
