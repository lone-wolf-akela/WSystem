#include <pch.h>
#include "SimShip.h"

std::wstring SimShip::GetDataAssetName() const
{
	const auto& data = *GetDataAsset();
	return data->GetName();
}

std::string SimShip::GetDataAssetNameNarrow() const
{
	return boost::nowide::narrow(GetDataAssetName());
}
