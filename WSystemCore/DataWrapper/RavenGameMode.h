#pragma once
#include <pch.h>

#include "EnumDef.h"
#include "UObject.h"

class RavenGameMode : public UObjWrapper
{
public:
    using UObjWrapper::UObjWrapper;

    WSYS_DATA_PROPERTY(ELobbyState, LobbyState)

    [[nodiscard]] bool IsLobbyRavenGameMode() const;
};