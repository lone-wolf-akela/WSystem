#include <pch.h>

#include "WeaponFireActor.h"

std::wstring AWeaponFireActor::GetDataAssetName() const
{
	return DataAsset->GetName();
}

std::string AWeaponFireActor::GetDataAssetNameNarrow() const
{
	return boost::nowide::narrow(GetDataAssetName());
}
