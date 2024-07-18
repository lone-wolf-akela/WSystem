#pragma once
#include <pch.h>

#include "UObject.h"

enum class LobbyState : std::int8_t
{
    Invalid = -1,
    Setup = 0,
    PreLobby = 1,
    Lobby = 2,
    LoadSaveGame = 3,
    LoadReplay = 4,
    InitScenario = 5,
    InGame = 6,
    PostGame = 7,
};

class RavenGameMode : public UObjWrapper
{
public:
    using UObjWrapper::UObjWrapper;

    WSYS_DATA_PROPERTY(LobbyState, LobbyState)

    [[nodiscard]] bool IsLobbyRavenGameMode() const;
};