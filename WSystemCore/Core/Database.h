#pragma once
#include <pch.h>

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
	UShipStaticData GetShipData(std::string_view name) const;
	std::string GetShipName(const UShipStaticData& data) const;
	UEntityStaticData GetEntityData(std::string_view name) const;
	std::string GetEntityName(const UEntityStaticData& data) const;
	UStatusEffectStaticData GetStatusEffectData(std::string_view name) const;
	std::string GetStatusEffectName(const UStatusEffectStaticData& data) const;
	UStrikeGroupFormationStaticData GetStrikeGroupFormationData(std::string_view name) const;
	std::string GetStrikeGroupFormationName(const UStrikeGroupFormationStaticData& data) const;
	UArtifactStaticData GetArtifactData(std::string_view name) const;
	std::string GetArtifactName(const UArtifactStaticData& data) const;
	UWeaponStaticData GetWeaponData(std::string_view name) const;
	std::string GetWeaponName(const UWeaponStaticData& data) const;
	UAttackFamily GetAttackFamily(std::string_view name) const;
	std::string GetAttackFamilyName(const UAttackFamily& data) const;
private:
	bool has_inited = false;
	
	std::map<std::string, UShipStaticData, std::less<>> name_to_shipdata;
	std::map<UShipStaticData, std::string> shipdata_to_name;

	std::map<std::string, UEntityStaticData, std::less<>> name_to_entitydata;
	std::map<UEntityStaticData, std::string> entitydata_to_name;

	std::map<std::string, UStatusEffectStaticData, std::less<>> name_to_statuseffectdata;
	std::map<UStatusEffectStaticData, std::string> statuseffectdata_to_name;

	std::map<std::string, UStrikeGroupFormationStaticData, std::less<>> name_to_strikegroupformationdata;
	std::map<UStrikeGroupFormationStaticData, std::string> strikegroupformationdata_to_name;

	std::map<std::string, UArtifactStaticData, std::less<>> name_to_artifactdata;
	std::map<UArtifactStaticData, std::string> artifactdata_to_name;

	std::map<std::string, UWeaponStaticData, std::less<>> name_to_weapondata;
	std::map<UWeaponStaticData, std::string> weapondata_to_name;

	std::map<std::string, UAttackFamily, std::less<>> name_to_attackfamily;
	std::map<UAttackFamily, std::string> attackfamily_to_name;
};