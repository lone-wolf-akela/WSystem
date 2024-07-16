#include <boost/nowide/convert.hpp>

#include <Unreal/UObjectGlobals.hpp>

#include "Database.h"

void Database::ScanData()
{
	if (has_inited)
	{
		return;
	}

	RC::Output::send<RC::LogLevel::Verbose>(STR("Scanning data...\n"));

	// ship data

	name_to_shipdata.clear();
	shipdata_to_name.clear();

	std::vector<RC::Unreal::UObject*> ships;
	RC::Unreal::UObjectGlobals::FindAllOf(STR("ShipStaticData"), ships);
	for (const auto ship : ships)
	{
		ShipStaticData ship_data = ship;
		auto name = boost::nowide::narrow(ship_data->GetName());

		if (name_to_shipdata.contains(name))
		{
			RC::Output::send<RC::LogLevel::Error>(STR("Error: Database: Duplicate ship name: {}\n"), boost::nowide::widen(name));
			continue;
		}

		name_to_shipdata[name] = ship_data;
		shipdata_to_name[ship_data] = name;
	}

	// entity data
	
	name_to_entitydata.clear();
	entitydata_to_name.clear();

	std::vector<RC::Unreal::UObject*> entities;
	RC::Unreal::UObjectGlobals::FindAllOf(STR("EntityStaticData"), entities);
	for (const auto entity : entities)
	{
		EntityStaticData entity_data = entity;
		auto name = boost::nowide::narrow(entity_data->GetName());

		if (name_to_entitydata.contains(name))
		{
			RC::Output::send<RC::LogLevel::Error>(STR("Error: Database: Duplicate entity name: {}\n"), boost::nowide::widen(name));
			continue;
		}

		name_to_entitydata[name] = entity_data;
		entitydata_to_name[entity_data] = name;
	}

	has_inited = true;
}

ShipStaticData Database::GetShipData(std::string_view name)
{
	if (!has_inited)
	{
		RC::Output::send<RC::LogLevel::Error>(STR("Error: Database has not been initialized.\n"), boost::nowide::widen(name));
		return nullptr;
	}

	if (const auto found = name_to_shipdata.find(name); found != name_to_shipdata.end())
	{
		return found->second;
	}

	RC::Output::send<RC::LogLevel::Error>(STR("Error: No ship type with name {}\n"), boost::nowide::widen(name));
	return nullptr;
}

std::string Database::GetShipName(const ShipStaticData& data)
{
	if (!has_inited)
	{
		RC::Output::send<RC::LogLevel::Error>(STR("Error: Database has not been initialized.\n"));
		return "";
	}
	if (const auto found = shipdata_to_name.find(data); found != shipdata_to_name.end())
	{
		return found->second;
	}
	
	RC::Output::send<RC::LogLevel::Error>(STR("Error: No ship of this type\n"));
	return "";
}

EntityStaticData Database::GetEntityData(std::string_view name)
{
	if (!has_inited)
	{
		RC::Output::send<RC::LogLevel::Error>(STR("Error: Database has not been initialized.\n"), boost::nowide::widen(name));
		return nullptr;
	}

	if (const auto found = name_to_entitydata.find(name); found != name_to_entitydata.end())
	{
		return found->second;
	}

	RC::Output::send<RC::LogLevel::Error>(STR("Error: No entity type with name {}\n"), boost::nowide::widen(name));
	return nullptr;
}

std::string Database::GetEntityName(const EntityStaticData& data)
{
	if (!has_inited)
	{
		RC::Output::send<RC::LogLevel::Error>(STR("Error: Database has not been initialized.\n"));
		return "";
	}
	if (const auto found = entitydata_to_name.find(data); found != entitydata_to_name.end())
	{
		return found->second;
	}

	RC::Output::send<RC::LogLevel::Error>(STR("Error: No entity of this type\n"));
	return "";
}
