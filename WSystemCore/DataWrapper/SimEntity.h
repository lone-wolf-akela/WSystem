#pragma once
#include <pch.h>

#include "UObject.h"

class SimEntity : public UObjWrapper
{
public:
	using UObjWrapper::UObjWrapper;

	WSYS_DATA_PROPERTY(std::int32_t, PlayerOwner)
	WSYS_DATA_PROPERTY(std::int32_t, SimID)
	WSYS_DATA_PROPERTY(bool, bIsNis)

	[[nodiscard]] WSYS_MEMBER_FUNCTION_NOARGS(bool, IsShip)
	[[nodiscard]] WSYS_MEMBER_FUNCTION_NOARGS(bool, IsAlive)
	[[nodiscard]] WSYS_MEMBER_FUNCTION_NOARGS(bool, IsMilitary)
	[[nodiscard]] WSYS_MEMBER_FUNCTION_NOARGS(bool, IsLocal)
	[[nodiscard]] WSYS_MEMBER_FUNCTION_NOARGS(bool, IsDamaged)
	[[nodiscard]] WSYS_MEMBER_FUNCTION_NOARGS(bool, IsAliveAndVisibleEntity)
	[[nodiscard]] WSYS_MEMBER_FUNCTION_NOARGS(bool, CanHeal)
	[[nodiscard]] WSYS_MEMBER_FUNCTION_NOARGS(bool, CanBeFocused)

	[[nodiscard]] bool IsMovableEntity() const;
	[[nodiscard]] bool IsResource() const;
	[[nodiscard]] bool IsWeaponFireActor() const;
	[[nodiscard]] bool IsMissile() const;
	[[nodiscard]] bool IsRavenSimProjectile() const;
	[[nodiscard]] bool IsProjectile() const;
	[[nodiscard]] std::wstring GetDataAssetName() const;
	[[nodiscard]] std::string  GetDataAssetNameNarrow() const;
};
