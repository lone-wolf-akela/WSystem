#pragma once

#include <string>
#include <map>

#include <DataWrapper/EntityStaticData.h>
#include <DataWrapper/ShipStaticData.h>
#include <DataWrapper/StatusEffectStaticData.h>
#include <DataWrapper/StrikeGroupFormationStaticData.h>
#include <DataWrapper/ArtifactStaticData.h>
#include <DataWrapper/WeaponStaticData.h>
#include <DataWrapper/AttackFamily.h>

class Database
{
public:
	void ScanData();
	ShipStaticData GetShipData(std::string_view name) const;
	std::string GetShipName(const ShipStaticData& data) const;
	EntityStaticData GetEntityData(std::string_view name) const;
	std::string GetEntityName(const EntityStaticData& data) const;
	StatusEffectStaticData GetStatusEffectData(std::string_view name) const;
	std::string GetStatusEffectName(const StatusEffectStaticData& data) const;
	StrikeGroupFormationStaticData GetStrikeGroupFormationData(std::string_view name) const;
	std::string GetStrikeGroupFormationName(const StrikeGroupFormationStaticData& data) const;
	ArtifactStaticData GetArtifactData(std::string_view name) const;
	std::string GetArtifactName(const ArtifactStaticData& data) const;
	WeaponStaticData GetWeaponData(std::string_view name) const;
	std::string GetWeaponName(const WeaponStaticData& data) const;
	AttackFamily GetAttackFamily(std::string_view name) const;
	std::string GetAttackFamilyName(const AttackFamily& data) const;
private:
	bool has_inited = false;
	
	std::map<std::string, ShipStaticData, std::less<>> name_to_shipdata;
	std::map<ShipStaticData, std::string> shipdata_to_name;

	std::map<std::string, EntityStaticData, std::less<>> name_to_entitydata;
	std::map<EntityStaticData, std::string> entitydata_to_name;

	std::map<std::string, StatusEffectStaticData, std::less<>> name_to_statuseffectdata;
	std::map<StatusEffectStaticData, std::string> statuseffectdata_to_name;

	std::map<std::string, StrikeGroupFormationStaticData, std::less<>> name_to_strikegroupformationdata;
	std::map<StrikeGroupFormationStaticData, std::string> strikegroupformationdata_to_name;

	std::map<std::string, ArtifactStaticData, std::less<>> name_to_artifactdata;
	std::map<ArtifactStaticData, std::string> artifactdata_to_name;

	std::map<std::string, WeaponStaticData, std::less<>> name_to_weapondata;
	std::map<WeaponStaticData, std::string> weapondata_to_name;

	std::map<std::string, AttackFamily, std::less<>> name_to_attackfamily;
	std::map<AttackFamily, std::string> attackfamily_to_name;
};