#pragma once

#include <string>
#include <map>

#include <DataWrapper/EntityStaticData.h>
#include <DataWrapper/ShipStaticData.h>

class Database
{
public:
	void ScanData();
	ShipStaticData GetShipData(std::string_view name);
	std::string GetShipName(const ShipStaticData& data);
	EntityStaticData GetEntityData(std::string_view name);
	std::string GetEntityName(const EntityStaticData& data);
private:
	bool has_inited = false;
	
	std::map<std::string, ShipStaticData, std::less<>> name_to_shipdata;
	std::map<ShipStaticData, std::string> shipdata_to_name;

	std::map<std::string, EntityStaticData, std::less<>> name_to_entitydata;
	std::map<EntityStaticData, std::string> entitydata_to_name;
};