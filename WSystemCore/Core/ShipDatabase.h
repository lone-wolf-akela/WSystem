#pragma once

#include <string>
#include <map>

#include <DataWrapper/ShipStaticData.h>

class ShipDatabase
{
public:
	void ScanShipData();
	ShipStaticData GetShipData(const RC::StringType& name);
	RC::StringType GetShipName(const ShipStaticData& data);
private:
	bool has_inited = false;
	std::map<RC::StringType, ShipStaticData> name_to_shipdata;
	std::map<ShipStaticData, RC::StringType> shipdata_to_name;
};