#include <boost/nowide/convert.hpp>

#include <Unreal/UObjectGlobals.hpp>

#include "Database.h"

namespace
{
	template <typename DataType>
	void ScanDatabaseFor(
		std::wstring_view class_name,
		std::map<std::string, DataType, std::less<>>& map_name_to_data,
		std::map<DataType, std::string>& map_data_to_name)
	{
		map_name_to_data.clear();
		map_data_to_name.clear();

		std::vector<RC::Unreal::UObject*> objects;
		RC::Unreal::UObjectGlobals::FindAllOf(class_name, objects);
		for (const auto obj : objects)
		{
			DataType data = obj;
			auto name = boost::nowide::narrow(data->GetName());

			if (map_name_to_data.contains(name))
			{
				RC::Output::send<RC::LogLevel::Error>(
					STR("Error: Database: Duplicate {} name: {}\n"), class_name, boost::nowide::widen(name));
				continue;
			}

			map_name_to_data[name] = data;
			map_data_to_name[data] = name;
		}
	}

	template <typename DataType>
	DataType GetData(std::string_view name, bool has_inited, const std::map<std::string, DataType, std::less<>>& name_to_data)
	{
		if (!has_inited)
		{
			RC::Output::send<RC::LogLevel::Error>(STR("Error: Database has not been initialized.\n"), boost::nowide::widen(name));
			return nullptr;
		}

		if (const auto found = name_to_data.find(name); found != name_to_data.end())
		{
			return found->second;
		}

		RC::Output::send<RC::LogLevel::Error>(STR("Error: {} not found.\n"), boost::nowide::widen(name));
		return nullptr;
	}

	template <typename DataType>
	std::string GetName(const DataType& data, bool has_inited, const std::map<DataType, std::string>& data_to_name)
	{
		if (!has_inited)
		{
			RC::Output::send<RC::LogLevel::Error>(STR("Error: Database has not been initialized.\n"));
			return "";
		}
		if (const auto found = data_to_name.find(data); found != data_to_name.end())
		{
			return found->second;
		}

		RC::Output::send<RC::LogLevel::Error>(STR("Error: No data of this type\n"));
		return "";
	}
}

void Database::ScanData()
{
	if (has_inited)
	{
		return;
	}

	RC::Output::send<RC::LogLevel::Verbose>(STR("Scanning data...\n"));

	ScanDatabaseFor(STR("ShipStaticData"), name_to_shipdata, shipdata_to_name);
	ScanDatabaseFor(STR("EntityStaticData"), name_to_entitydata, entitydata_to_name);
	ScanDatabaseFor(STR("StatusEffectStaticData"), name_to_statuseffectdata, statuseffectdata_to_name);
	ScanDatabaseFor(STR("StrikeGroupFormationStaticData"), name_to_strikegroupformationdata, strikegroupformationdata_to_name);
	ScanDatabaseFor(STR("ArtifactStaticData"), name_to_artifactdata, artifactdata_to_name);
	ScanDatabaseFor(STR("WeaponStaticData"), name_to_weapondata, weapondata_to_name);
	ScanDatabaseFor(STR("AttackFamily"), name_to_attackfamily, attackfamily_to_name);

	has_inited = true;
}

ShipStaticData Database::GetShipData(std::string_view name) const
{
	return GetData(name, has_inited, name_to_shipdata);
}

std::string Database::GetShipName(const ShipStaticData& data) const
{
	return GetName(data, has_inited, shipdata_to_name);
}

EntityStaticData Database::GetEntityData(std::string_view name) const
{
	return GetData(name, has_inited, name_to_entitydata);
}

std::string Database::GetEntityName(const EntityStaticData& data) const
{
	return GetName(data, has_inited, entitydata_to_name);
}

StatusEffectStaticData Database::GetStatusEffectData(std::string_view name) const
{
	return GetData(name, has_inited, name_to_statuseffectdata);
}

std::string Database::GetStatusEffectName(const StatusEffectStaticData& data) const
{
	return GetName(data, has_inited, statuseffectdata_to_name);
}

StrikeGroupFormationStaticData Database::GetStrikeGroupFormationData(std::string_view name) const
{
	return GetData(name, has_inited, name_to_strikegroupformationdata);
}

std::string Database::GetStrikeGroupFormationName(const StrikeGroupFormationStaticData& data) const
{
	return GetName(data, has_inited, strikegroupformationdata_to_name);
}

ArtifactStaticData Database::GetArtifactData(std::string_view name) const
{
	return GetData(name, has_inited, name_to_artifactdata);
}

std::string Database::GetArtifactName(const ArtifactStaticData& data) const
{
	return GetName(data, has_inited, artifactdata_to_name);
}

WeaponStaticData Database::GetWeaponData(std::string_view name) const
{
	return GetData(name, has_inited, name_to_weapondata);
}

std::string Database::GetWeaponName(const WeaponStaticData& data) const
{
	return GetName(data, has_inited, weapondata_to_name);
}

AttackFamily Database::GetAttackFamily(std::string_view name) const
{
	return GetData(name, has_inited, name_to_attackfamily);
}

std::string Database::GetAttackFamilyName(const AttackFamily& data) const
{
	return GetName(data, has_inited, attackfamily_to_name);
}
