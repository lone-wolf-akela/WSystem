#include <pch.h>

#include "SimMovable.h"

std::wstring SimMovable::GetDataAssetName() const
{
	const auto& data = *GetDataAsset();
	return data->GetName();
}

std::string SimMovable::GetDataAssetNameNarrow() const
{
	return boost::nowide::narrow(GetDataAssetName());
}
