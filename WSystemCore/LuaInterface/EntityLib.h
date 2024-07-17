#pragma once
#include <cstdint>
#include <string>
#include <string_view>
#include <tuple>

#include <sol/sol.hpp>

#include <LibWrapper/TiirEntityFunctionLibrary.h>

#include "SobGroupLib.h"

class EntityLibInterface
{
public:
	EntityLibInterface() = default;

	EntityLibInterface(const EntityLibInterface& o) = delete;
	EntityLibInterface& operator=(const EntityLibInterface& o) = delete;
	EntityLibInterface(EntityLibInterface&& o) noexcept = default;
	EntityLibInterface& operator=(EntityLibInterface&& o) noexcept = default;

	~EntityLibInterface() = default;

	void BindLuaState(sol::state_view* lua, TiirEntityFunctionLibrary* lib, SobGroupManager* sob_group_manager);

	void UndeployTurret(std::uint64_t entity_id, bool instantaneous) const;
	void Teleport(
		std::uint64_t entity_id, 
		double dest_rotation_w, double dest_rotation_x, double dest_rotation_y, double dest_rotation_z,
		double dest_position_x, double dest_position_y, double dest_position_z,
		double scale_x, double scale_y, double scale_z, 
		bool teleport_ships_in_parade) const;
	void SetVelocity(std::uint64_t entity_id, double x, double y, double z) const;
	void SetTransform(
		std::uint64_t entity_id, 
		double rotation_w, double rotation_x, double rotation_y, double rotation_z,
		double position_x, double position_y, double position_z,
		double scale_x, double scale_y, double scale_z) const;
	void SetTactics(std::uint64_t entity_id, SquadronTactics tactics) const;
	void SetStance(std::uint64_t entity_id, SquadronStance stance) const;
	void SetRotation(std::uint64_t entity_id, double pitch, double yaw, double roll) const;
	void SetNoRetaliate(std::uint64_t entity_id, bool enabled) const;
	void SetMetaDataValue(std::uint64_t entity_id, std::string_view key, std::int32_t value) const;
	void SetLocation(std::uint64_t entity_id, double x, double y, double z) const;
	void SetInvincible(std::uint64_t entity_id, bool enabled) const;
	void SetIgnoreForPersistentFleet(std::uint64_t entity_id, bool enabled) const;
	void SetIgnoreDamage(std::uint64_t entity_id, bool enabled) const;
	void SetGhost(std::uint64_t entity_id, bool enabled) const;
	void SetCloaking(std::uint64_t entity_id, bool enabled) const;
	void SetAutoLaunch(std::uint64_t entity_id, AutoLaunchSetting auto_launch_setting) const;
	void SetAngularVelocity(std::uint64_t entity_id, double x, double y, double z) const;
	void Scuttle(std::uint64_t entity_id) const;
	void SalvageCapture(std::uint64_t entity_id, std::string_view target_group) const;
	void RevealInFow(std::uint64_t entity_id, bool revealed) const;
	void RetireTo(std::uint64_t entity_id, std::uint64_t target_id) const;
	void Retire(std::uint64_t entity_id) const;
	void Repair(std::uint64_t entity_id, std::string_view target_group) const;
	void RemoveObtainableArtifactFromShip(std::uint64_t entity_id) const;
	void OverrideRetaliationSetting(std::uint64_t entity_id, RetaliationSetting retaliation_setting) const;
	void MovePingPong(std::uint64_t entity_id, sol::table locations, bool attack_move) const;
	void MoveAlong(std::uint64_t entity_id, sol::table path, bool loop, bool attack_move) const;
	void MakeDead(std::uint64_t entity_id, bool Instant, bool NoAoeDamage, bool NoDebris, bool NoZombie) const;
	void LaunchSelf(std::uint64_t entity_id) const;
	void LaunchAll(std::uint64_t entity_id) const;
	void LatchInstantly(std::uint64_t entity_id, std::uint64_t latch_target_entity) const;
	void Kamikaze(std::uint64_t entity_id, std::string_view target_group) const;
	bool IsValid_OnPres(std::uint64_t entity_id) const;
	bool IsValid(std::uint64_t entity_id) const;
	bool IsInHyperspace(std::uint64_t entity_id) const;
	bool IsInCombat(std::uint64_t entity_id) const;
	bool IsCloaking(std::uint64_t entity_id) const;
	bool IsBeingCaptured(std::uint64_t entity_id) const;
	bool IsBeingAttacked(std::uint64_t entity_id) const;
	bool IsAttacking(std::uint64_t entity_id) const;
	bool IsAlive(std::uint64_t entity_id) const;
	void Guard(std::uint64_t entity_id, std::string_view target_group) const;
	float GetVisualRange(std::uint64_t entity_id) const;
	float GetSecondarySensorRange(std::uint64_t entity_id) const;
	float GetPrimarySensorRange(std::uint64_t entity_id) const;
	std::tuple<double, double, double> GetPosition(std::uint64_t entity_id) const;
	TiirCommander GetOwningPlayer(std::uint64_t entity_id) const;
	std::tuple<double, double, double> GetOrientation(std::uint64_t entity_id) const;
	std::int32_t GetNumberOfQueuedOrders(std::uint64_t entity_id) const;
	std::tuple<bool, std::int32_t> GetMetaDataValue(std::uint64_t entity_id, std::string_view key) const;
	float GetHealthAbsolute(std::uint64_t entity_id) const;
	float GetHealth(std::uint64_t entity_id) const;
	std::int32_t GetBuildTime(std::uint64_t entity_id) const;
	void GatherResource(std::uint64_t entity_id, std::string_view target_group) const;
	std::string FindShipType(std::uint64_t entity_id) const;
	void DockInstantly(std::uint64_t entity_id, std::uint64_t dock_target_entity) const;
	void Dock(std::uint64_t entity_id, std::uint64_t dock_target_entity, bool stay_docked, bool dock_only) const;
	void DeployTurretAtPositionAndOrientation(
		std::uint64_t entity_id,
		double x, double y, double z,
		double pitch, double yaw, double roll,
		bool instantaneous) const;
	void DeployTurretAtPositionAndNormal(
		std::uint64_t entity_id,
		double position_x, double position_y, double position_z,
		double normal_x, double normal_y, double normal_z,
		bool instantaneous) const;
	void DeployTurret(std::uint64_t entity_id, bool instantaneous) const;
	void CustomCommand(std::uint64_t entity_id, std::string_view target_group) const;
	bool ClearStatusEffects(std::uint64_t entity_id) const;
	void ClearRetaliationSetting(std::uint64_t entity_id) const;
	bool ClearModifiers(std::uint64_t entity_id) const;
	void ChangeOwner(std::uint64_t entity_id, std::int32_t target_player) const;
	void ChangeCommander(std::uint64_t entity_id, const TiirCommander& new_commander) const;
	void BindInstantly(std::uint64_t entity_id, std::uint64_t bind_target_entity) const;
	void Attack(std::uint64_t entity_id, std::string_view target_group, bool maintain_guard) const;
	TiirModifierHandle AddOverrideModifier(
		std::uint64_t entity_id, 
		SobPropertyType property, 
		float value, 
		InfluenceType influence_type, 
		float influence_radius) const;
	bool RemoveModifier(const TiirModifierHandle& modifier) const;
	TiirModifierHandle AddMultiplierModifier(
		std::uint64_t entity_id, 
		MultiplierType multiplier, 
		float multiplier_value, 
		InfluenceType influence_type, 
		float influence_radius, 
		ActivityRelation multiplier_value_relation, 
		float multiplier_interp_min_value) const;
	TiirModifierHandle AddAbilityModifier(
		std::uint64_t entity_id, 
		AbilityType ability, 
		bool ability_state, 
		InfluenceType influence_type, 
		float influence_radius) const;

private:
	sol::state_view* lua = nullptr;
	SobGroupManager* sob_group_manager = nullptr;
	TiirEntityFunctionLibrary* lib = nullptr;
};