#include <pch.h>

#include "SimMovable.h"
#include "SimResource.h"
#include "SimShip.h"
#include "WeaponFireActor.h"

#include "SimEntity.h"

namespace
{
	bool object_is_of_type(Unreal::UObject* object, std::wstring_view type)
	{
		const auto class_name = Unreal::FName(type);
		const auto class_obj = object->GetClassPrivate();

		if (class_obj->GetNamePrivate().Equals(class_name))
		{
			return true;
		}
		for (const auto super_struct : class_obj->ForEachSuperStruct())
		{
			if (super_struct->GetNamePrivate().Equals(class_name))
			{
				return true;
			}
		}
		return false;
	}
}

bool SimEntity::IsMovableEntity() const
{
	return object_is_of_type(obj, L"SimMovable");
}

bool SimEntity::IsResource() const
{
	return object_is_of_type(obj, L"SimResource");
}

bool SimEntity::IsWeaponFireActor() const
{
	return object_is_of_type(obj, L"WeaponFireActor");
}

bool SimEntity::IsMissile() const
{
	return object_is_of_type(obj, L"SimMissile");
}

bool SimEntity::IsRavenSimProjectile() const
{
	return object_is_of_type(obj, L"RavenSimProjectile");
}

bool SimEntity::IsProjectile() const
{
	return object_is_of_type(obj, L"SimProjectile");
}

std::wstring SimEntity::GetDataAssetName() const
{
	if (IsShip())
	{
		const SimShip ship = obj;
		return ship.GetDataAssetName();
	}
	if (IsResource())
	{
		const SimResource resource = obj;
		return resource.GetDataAssetName();
	}
	if (IsWeaponFireActor())
	{
		const WeaponFireActor weapon_fire = obj;
		return weapon_fire.GetDataAssetName();
	}
	else
	if (IsMovableEntity())
	{
		const SimMovable movable = obj;
		return movable.GetDataAssetName();
	}
	return {};
}

std::string SimEntity::GetDataAssetNameNarrow() const
{
	return boost::nowide::narrow(GetDataAssetName());
}
