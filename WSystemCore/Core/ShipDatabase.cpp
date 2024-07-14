#include <Unreal/UObjectGlobals.hpp>

#include "ShipDatabase.h"

void ShipDatabase::ScanShipData()
{
	if (has_inited)
	{
		return;
	}

	RC::Output::send<RC::LogLevel::Verbose>(STR("Scanning ship data...\n"));

	name_to_shipdata.clear();
	shipdata_to_name.clear();

	std::vector<RC::Unreal::UObject*> ships;
	RC::Unreal::UObjectGlobals::FindAllOf(STR("ShipStaticData"), ships);
	for (const auto ship : ships)
	{
		ShipStaticData ship_data = ship;
		auto name = ship_data->GetName();

		if (name_to_shipdata.contains(name))
		{
			RC::Output::send<RC::LogLevel::Error>(STR("Error: ShipDatabase: Duplicate ship name: {}\n"), name);
			continue;
		}

		name_to_shipdata[name] = ship_data;
		shipdata_to_name[ship_data] = name;

		RC::Output::send<RC::LogLevel::Verbose>(STR("ShipDatabase: Found ship: {}\n"), name);
	}

	has_inited = true;
}

ShipStaticData ShipDatabase::GetShipData(const RC::StringType& name)
{
	if (!has_inited)
	{
		RC::Output::send<RC::LogLevel::Error>(STR("Error: ShipDatabase has not been initialized.\n"), name);
		return nullptr;
	}

	return name_to_shipdata[name];
}

RC::StringType ShipDatabase::GetShipName(const ShipStaticData& data)
{
	if (!has_inited)
	{
		RC::Output::send<RC::LogLevel::Error>(STR("Error: ShipDatabase has not been initialized.\n"));
		return STR("");
	}

	return shipdata_to_name[data];
}
