#include <pch.h>

#include "WeaponFireActor.h"

std::wstring WeaponFireActor::GetDataAssetName() const
{
	const auto& data = *GetDataAsset();
	return data->GetName();
}

std::string WeaponFireActor::GetDataAssetNameNarrow() const
{
	return boost::nowide::narrow(GetDataAssetName());
}
