#include <pch.h>

#include "SimMovable.h"

std::wstring ASimMovable::GetDataAssetName() const
{
	return DataAsset->GetName();
}

std::string ASimMovable::GetDataAssetNameNarrow() const
{
	return boost::nowide::narrow(GetDataAssetName());
}
