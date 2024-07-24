#include <pch.h>

#include "SimResource.h"

std::wstring SimResource::GetDataAssetName() const
{
	const auto& data = *GetDataAsset();
	return data->GetName();
}

std::string SimResource::GetDataAssetNameNarrow() const
{
	return boost::nowide::narrow(GetDataAssetName());
}
