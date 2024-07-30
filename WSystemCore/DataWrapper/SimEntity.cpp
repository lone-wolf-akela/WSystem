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

bool ASimEntity::IsMovableEntity() const
{
	return object_is_of_type(obj, L"SimMovable");
}

bool ASimEntity::IsResource() const
{
	return object_is_of_type(obj, L"SimResource");
}

bool ASimEntity::IsWeaponFireActor() const
{
	return object_is_of_type(obj, L"WeaponFireActor");
}

bool ASimEntity::IsMissile() const
{
	return object_is_of_type(obj, L"SimMissile");
}

bool ASimEntity::IsRavenSimProjectile() const
{
	return object_is_of_type(obj, L"RavenSimProjectile");
}

bool ASimEntity::IsProjectile() const
{
	return object_is_of_type(obj, L"SimProjectile");
}

std::wstring ASimEntity::GetDataAssetName() const
{
	if (IsShip())
	{
		const ASimShip ship = obj;
		return ship.GetDataAssetName();
	}
	if (IsResource())
	{
		const ASimResource resource = obj;
		return resource.GetDataAssetName();
	}
	if (IsWeaponFireActor())
	{
		const AWeaponFireActor weapon_fire = obj;
		return weapon_fire.GetDataAssetName();
	}
	else
	if (IsMovableEntity())
	{
		const ASimMovable movable = obj;
		return movable.GetDataAssetName();
	}
	return {};
}

std::string ASimEntity::GetDataAssetNameNarrow() const
{
	return boost::nowide::narrow(GetDataAssetName());
}
