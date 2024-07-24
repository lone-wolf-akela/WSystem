#pragma once
#include <pch.h>

#include <Core/Database.h>
#include <LibWrapper/TiirEntityGroupFunctionLibrary.h>
#include <DataWrapper/RavenSimulationProxy.h>
#include <DataWrapper/UnitsInfoSubsystem.h>

#include "EntityIdManager.h"

class SobGroupManager
{
public:
	SobGroupManager() = default;

	SobGroupManager(const SobGroupManager& o) = delete;
	SobGroupManager& operator=(const SobGroupManager& o) = delete;
	SobGroupManager(SobGroupManager&& o) noexcept = default;
	SobGroupManager& operator=(SobGroupManager&& o) noexcept = default;

	~SobGroupManager() = default;

	void Initialize(sol::state_view* lua, TiirEntityGroupFunctionLibrary* lib, Database* database, EntityIdManager* entity_id_manager);
	void Begin_InitScenario(UnitsInfoSubsystem units_info_subsystem);
	void Begin_InGame(RavenSimulationProxy sim_proxy);

	[[nodiscard]] TiirEntityGroup& FindGroup(std::string_view name);
	[[nodiscard]] const TiirEntityGroup& FindGroup(std::string_view name) const;
	void SetGroup(std::string_view name, TiirEntityGroup&& group);
	void SetGroup(std::string_view name, const TiirEntityGroup& group);

	bool CreateOrClear(std::string_view name);
	bool CreateIfNotExists(std::string_view name);
	[[nodiscard]] bool IsExists(std::string_view name) const;
	[[nodiscard]] bool IsEmptyOrNotExists(std::string_view name) const;
	bool Delete(std::string_view name);

	std::int32_t FillGroupFromPlayer(
		std::string_view group, 
		std::int32_t owning_player, 
		bool include_docked, 
		bool include_in_hyperspace, 
		bool include_dead);
	void HyperspaceToDestination(
		std::string_view group,
		double dest_rotation_w, double dest_rotation_x, double dest_rotation_y, double dest_rotation_z,
		double dest_position_x, double dest_position_y, double dest_position_z,
		double scale_x, double scale_y, double scale_z,
		bool skip_placement_logic) const;
	void Teleport(
		std::string_view group,
		double dest_rotation_w, double dest_rotation_x, double dest_rotation_y, double dest_rotation_z,
		double dest_position_x, double dest_position_y, double dest_position_z,
		double scale_x, double scale_y, double scale_z,
		bool skip_placement_logic) const;
	std::int32_t FillGroupFromFilteredType(
		std::string_view group,
		std::string_view source_group,
		sol::table desired_types);
	[[nodiscard]] std::int32_t GroupCount(std::string_view group) const;
	void TakeDamageAbsolute(std::string_view group, float damage_absolute) const;
	void TakeDamage(std::string_view group, float damage_percentage) const;
	void Stop(std::string_view group) const;
	void SetVelocity(std::string_view group, double x, double y, double z) const;
	void UndeployTurret(std::string_view group, bool instantaneous) const;
	void ToggleAlternativeShipOrientation(std::string_view group) const;
	void Spawn(
		std::string_view group,
		double rotation_w, double rotation_x, double rotation_y, double rotation_z,
		double translation_x, double translation_y, double translation_z,
		double scale_x, double scale_y, double scale_z,
		bool skip_placement_logic) const;
	void SetTransform(
		std::string_view group,
		double rotation_w, double rotation_x, double rotation_y, double rotation_z,
		double translation_x, double translation_y, double translation_z,
		double scale_x, double scale_y, double scale_z) const;
	void SetTactics(std::string_view group, SquadronTactics tactics) const;
	void SetStrikeGroupFormation(std::string_view group, std::string_view formation) const;
	void SetStance(std::string_view group, SquadronStance stance) const;
	void SetRotation(std::string_view group, double pitch, double yaw, double roll) const;
	void SetNoRetaliate(std::string_view group, bool enabled) const;
	void SetLocation(std::string_view group, double x, double y, double z) const;
	void SetInvincible(std::string_view group, bool enabled) const;
	void SetIgnoreForPersistentFleet(std::string_view group, bool enabled) const;
	void SetIgnoreDamage(std::string_view group, bool enabled) const;
	void SetHealth(std::string_view group, float health_percentage) const;
	void SetGhost(std::string_view group, bool enabled) const;
	void SetCloaking(std::string_view group, bool enabled) const;
	void SetAutoLaunch(std::string_view group, AutoLaunchSetting auto_launch_setting) const;
	void Scuttle(std::string_view group) const;
	void SalvageCapture(std::string_view group, std::string_view targets) const;
	void RevealInFow(std::string_view group, bool revealed) const;
	void RetireTo(const std::string& group, std::uint64_t target_entity_id) const;
	void Retire(std::string_view group) const;
	void Repair(std::string_view group, std::string_view target_group) const;
	void RemoveStatusEffectsByHandles(sol::table handles) const;
	void RemoveStatusEffect(std::string_view group, std::string_view status) const;
	void RemoveObtainableArtifactFromShips(std::string_view group) const;
	void ParadeAround(std::string_view group, std::uint64_t parade_around_entity_id, ParadeMode parade_mode) const;
	void OverrideRetaliationSetting(std::string_view group, RetaliationSetting the_retaliation_setting) const;
	void MoveTo(std::string_view group, double dest_x, double dest_y, double dest_z, bool attack_move) const;
	void MovePingPong(std::string_view group, sol::table locations, bool attack_move) const;
	void MoveAlong(std::string_view group, sol::table path, bool loop, bool attack_move) const;
	void MakeDead(std::string_view group, bool instant, bool no_aoe_damage, bool no_debris, bool no_zombie) const;
	void LaunchSelf(std::string_view group) const;
	void LaunchAll(std::string_view group) const;
	void LatchInstantly(std::string_view group, std::string_view latch_target_group) const;
	void KillUnit(std::string_view group, bool by_damage) const;
	[[nodiscard]] bool IsWithinPlayerSensorRange(std::string_view group, std::int32_t target_player) const;
	[[nodiscard]] bool IsInHyperspace(std::string_view group) const;
	[[nodiscard]] bool IsGroupInCombat(std::string_view group, bool require_everyone) const;
	[[nodiscard]] bool IsDeSpawned(std::string_view group) const;
	[[nodiscard]] bool IsCloaking(std::string_view group, bool require_all) const;
	void HyperspaceExit(
		std::string_view group, 
		double dest_rotation_w, double dest_rotation_x, double dest_rotation_y, double dest_rotation_z,
		double dest_position_x, double dest_position_y, double dest_position_z,
		double scale_x, double scale_y, double scale_z, 
		bool skip_placement_logic) const;
	void HyperspaceEnter(std::string_view group) const;
	[[nodiscard]] bool HasStatusEffect(std::string_view group, std::string_view status_effect, bool check_for_all) const;
	void Guard(std::string_view group, std::string_view targets) const;
	std::int32_t GroupRemoveEntity(std::string_view group, std::uint64_t entity_id);
	std::int32_t GroupRemove(std::string_view group, std::string_view source_group);
	std::int32_t GroupPurgeDead(std::string_view group);
	std::int32_t GroupPurgeAlive(std::string_view group);
	[[nodiscard]] sol::table GroupMembers(std::string_view group) const;
	[[nodiscard]] std::int32_t GroupCountFiltered(std::string_view group, bool awake, bool docked, bool in_hyperspace, bool in_combat);
	void GroupClear(std::string_view group);
	std::int32_t GroupAddEntity(std::string_view group, std::uint64_t entity_id);
	std::int32_t GroupAdd(std::string_view group, std::string_view source_group);
	[[nodiscard]] std::tuple<double, double, double> GetPosition(std::string_view group) const;
	[[nodiscard]] std::tuple<double, double, double> GetOrientation(std::string_view group) const;
	[[nodiscard]] std::string GenerateDebugString(std::string_view group) const;
	void GatherResource(std::string_view group, std::string_view targets) const;
	bool FireAtNoTarget(
		std::string_view group, std::string_view weapon_type, bool all_sources_fire, std::string_view fire_from_socket,
		double muzzle_offset_x, double muzzle_offset_y, double muzzle_offset_z) const;
	bool FireAt(
		std::string_view group, std::string_view target_group, std::string_view weapon_type, bool all_sources_fire,
		bool fire_at_all_targets, std::string_view fire_from_socket,
		double muzzle_offset_x, double muzzle_offset_y, double muzzle_offset_z) const;
	std::int32_t FillGroupIncludingPlayer(std::string_view group, std::string_view source_group, const TiirCommander& owning_player);
	std::int32_t FillGroupFromPlayerMothershipList(std::string_view group, std::int32_t owning_player, bool include_dead);
	std::int32_t FillGroupFromFilteredFamily(std::string_view group, std::string_view source_group, sol::table desired_types);
	std::int32_t FillGroupExcludingPlayer(std::string_view group, std::string_view source_group, std::int32_t excluding_player);
	std::int32_t FillGroupByProximityToLocation(
		std::string_view group, std::string_view source_group, 
		double location_x, double location_y, double location_z,
		double distance_x, double distance_y, double distance_z);
	std::int32_t FillGroupByProximityToGroup(
		std::string_view group, std::string_view source_group, std::string_view near_group, 
		double distance_x, double distance_y, double distance_z);
	void DockInstantly(std::string_view group, std::string_view dock_target_entity_group) const;
	void Dock(std::string_view group, std::string_view dock_target_entity_group, bool stay_docked, bool dock_only) const;
	void DisbandStrikeGroup(std::string_view group) const;
	void Despawn(std::string_view group, bool ignore_active_commands) const;
	void DeployTurretAtPositionAndOrientation(
		std::string_view group,
		double position_x, double position_y, double position_z,
		double pitch, double yaw, double roll,
		bool instantaneous) const;
	void DeployTurretAtPositionAndNormal(
		std::string_view group,
		double position_x, double position_y, double position_z,
		double normal_x, double normal_y, double normal_z,
		bool instantaneous) const;
	void DeployTurret(std::string_view group, bool instantaneous) const;
	void CustomCommand(std::string_view group, std::string_view targets) const;
	[[nodiscard]] std::int32_t CountShipTypePresentInGroup(std::string_view group, sol::table filter_types) const;
	[[nodiscard]] std::int32_t CountAttackFamilyPresentInGroup(std::string_view group, sol::table filter_families) const;
	void ClearStatusEffects(std::string_view group) const;
	void ClearRetaliationSetting(std::string_view group) const;
	void ChangeOwner(std::string_view group, std::int32_t target_player) const;
	void ChangeCommander(std::string_view group, const TiirCommander& new_commander) const;
	void BindInstantly(std::string_view group, std::string_view bind_target_entity_group) const;
	void AttackPlayer(std::string_view group, std::int32_t target_player, bool can_attack_cloaked_units) const;
	void Attack(std::string_view group, std::string_view target_group, bool maintain_guard, bool can_attack_cloaked_units) const;
	[[nodiscard]] sol::table AddStatusEffect(std::string_view group, std::string_view status) const;
	void AddObtainableArtifactToShips(std::string_view group, std::string_view artifact_static_data) const;

	void CreateShipSimple(
		std::string_view group,
		double x, double y, double z,
		double pitch, double yaw, double roll,
		std::int32_t owning_player, bool start_in_hyperspace, bool skip_placement_logic,
		std::string_view ship_type, std::int32_t ship_count, SquadronStance stance,
		bool use_retaliation_override, RetaliationSetting retaliation_override,
		bool do_not_retaliate_against_me);

	void FillGroupAllEntitiesInGame(std::string_view group);
	void FillGroupAllShipsInGame(std::string_view group);
	void FillGroupAllNonShipEntitiesInGame(std::string_view group);
	void FillGroupAllAliveShipsInGame(std::string_view group);
	void FillGroupAllAliveEntitiesInGame(std::string_view group);
	void FillGroupAllAliveNonShipEntitiesInGame(std::string_view group);

	[[nodiscard]] std::int32_t GroupCountAliveEntities(std::string_view group) const;
	[[nodiscard]] std::tuple<bool, SquadronStance> GetStance(std::string_view group) const;
	[[nodiscard]] std::tuple<bool, std::string> GetFormation(std::string_view group) const;
private:
	sol::state_view* lua = nullptr;
	TiirEntityGroupFunctionLibrary* lib = nullptr;
	Database* database = nullptr;
	RavenSimulationProxy sim_proxy;
	EntityIdManager* entity_id_manager = nullptr;
	UnitsInfoSubsystem units_info_subsystem = nullptr;
	std::map<std::string, TiirEntityGroup, std::less<>> groups;
};
