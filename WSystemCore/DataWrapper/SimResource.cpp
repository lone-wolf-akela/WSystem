#include <pch.h>

#include "SimResource.h"

std::wstring ASimResource::GetDataAssetName() const
{
	return DataAsset->GetName();
}

std::string ASimResource::GetDataAssetNameNarrow() const
{
	return boost::nowide::narrow(GetDataAssetName());
}
