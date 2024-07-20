#include <pch.h>
#include "UniverseLib.h"

void UniverseLib::Initialize(sol::state_view* lua)
{
	this->lua = lua;
	lua->new_usertype<UniverseLib>(
		"UniverseLibType",
		"GameTime", &UniverseLib::GameTime,
		"GameFrame", &UniverseLib::GameFrame,
		"FrameDeltaTime", &UniverseLib::FrameDeltaTime
	);
}

void UniverseLib::Begin_InGame(RavenSimulationProxy sim_proxy)
{
	this->sim_proxy = sim_proxy;
}

float UniverseLib::GameTime() const
{
	return *this->sim_proxy.GetElapsedTime();
}

std::uint32_t UniverseLib::GameFrame() const
{
	return *this->sim_proxy.GetSimulatingFrame();
}

float UniverseLib::FrameDeltaTime() const
{
	return *this->sim_proxy.GetSimulatingDeltaTime();
}
