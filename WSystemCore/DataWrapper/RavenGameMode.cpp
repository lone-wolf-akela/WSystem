#include <pch.h>

#include "RavenGameMode.h"

bool RavenGameMode::IsLobbyRavenGameMode() const
{
	if (!IsValid())
	{
		return false;
	}
	const auto fullname = obj->GetFullName();
	return fullname.find(STR("BP_LobbyRavenGameMode_C ")) != decltype(fullname)::npos;
}
