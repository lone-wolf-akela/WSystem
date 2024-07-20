#pragma once
#include <pch.h>

#include <DataWrapper/RavenSimulationProxy.h>

class UniverseLib
{
public:
	UniverseLib() = default;

	UniverseLib(const UniverseLib&) = delete;
	UniverseLib& operator=(const UniverseLib&) = delete;
	UniverseLib(UniverseLib&&) = default;
	UniverseLib& operator=(UniverseLib&&) = default;

	~UniverseLib() = default;
	void Initialize(sol::state_view* lua);
	void Begin_InGame(RavenSimulationProxy sim_proxy);

	float GameTime() const;
	std::uint32_t GameFrame() const;
	float FrameDeltaTime() const;
private:
	sol::state_view* lua = nullptr;
	RavenSimulationProxy sim_proxy;
};