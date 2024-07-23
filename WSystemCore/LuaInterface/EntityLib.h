#pragma once
#include <pch.h>

#include <DataWrapper/UnitsInfoSubsystem.h>
#include <LibWrapper/TiirEntityFunctionLibrary.h>
#include <Core/Database.h>

#include "SobGroupLib.h"

class LuaInterface;

class EntityLibInterface
{
public:
	EntityLibInterface() = default;

	EntityLibInterface(const EntityLibInterface& o) = delete;
	EntityLibInterface& operator=(const EntityLibInterface& o) = delete;
	EntityLibInterface(EntityLibInterface&& o) noexcept = default;
	EntityLibInterface& operator=(EntityLibInterface&& o) noexcept = default;

	~EntityLibInterface() = default;

	void Initialize(sol::state_view* lua, TiirEntityFunctionLibrary* lib, SobGroupManager* sob_group_manager, Database* database, LuaInterface* lua_interface);
	void Begin_InitScenario(UnitsInfoSubsystem units_info_subsystem);

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
	void MakeDead(std::uint64_t entity_id, bool instant, bool no_aoe_damage, bool no_debris, bool no_zombie) const;
	void LaunchSelf(std::uint64_t entity_id) const;
	void LaunchAll(std::uint64_t entity_id) const;
	void LatchInstantly(std::uint64_t entity_id, std::uint64_t latch_target_entity) const;
	void Kamikaze(std::uint64_t entity_id, std::string_view target_group) const;
	[[nodiscard]] bool IsValid_OnPres(std::uint64_t entity_id) const;
	[[nodiscard]] bool IsValid(std::uint64_t entity_id) const;
	[[nodiscard]] bool IsInHyperspace(std::uint64_t entity_id) const;
	[[nodiscard]] bool IsInCombat(std::uint64_t entity_id) const;
	[[nodiscard]] bool IsCloaking(std::uint64_t entity_id) const;
	[[nodiscard]] bool IsBeingCaptured(std::uint64_t entity_id) const;
	[[nodiscard]] bool IsBeingAttacked(std::uint64_t entity_id) const;
	[[nodiscard]] bool IsAttacking(std::uint64_t entity_id) const;
	[[nodiscard]] bool IsAlive(std::uint64_t entity_id) const;
	void Guard(std::uint64_t entity_id, std::string_view target_group) const;
	[[nodiscard]] float GetVisualRange(std::uint64_t entity_id) const;
	[[nodiscard]] float GetSecondarySensorRange(std::uint64_t entity_id) const;
	[[nodiscard]] float GetPrimarySensorRange(std::uint64_t entity_id) const;
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
	bool RemoveStatusEffectByHandle(const TiirStatusEffectHandle& handle) const;
	bool RemoveStatusEffect(std::uint64_t entity_id, std::string_view status) const;
	TiirStatusEffectHandle AddStatusEffect(std::uint64_t entity_id, std::string_view status_effect) const;
	void AddObtainableArtifactToShip(std::uint64_t entity_id, std::string_view artifact_static_data) const;

	[[nodiscard]] bool IsShip(std::uint64_t entity_id) const;
	[[nodiscard]] bool IsMilitary(std::uint64_t entity_id) const;
	[[nodiscard]] bool IsDamaged(std::uint64_t entity_id) const;
	[[nodiscard]] bool IsAliveAndVisibleEntity(std::uint64_t entity_id) const;
	[[nodiscard]] bool CanHeal(std::uint64_t entity_id) const;
	[[nodiscard]] bool CanBeFocused(std::uint64_t entity_id) const;
	[[nodiscard]] bool IsResource(std::uint64_t entity_id) const;
	[[nodiscard]] bool IsMissile(std::uint64_t entity_id) const;
	[[nodiscard]] std::string GetEntityInternalName(std::uint64_t entity_id) const;

	[[nodiscard]] SquadronStance GetStance(std::uint64_t entity_id) const;
	[[nodiscard]] std::string GetFormation(std::uint64_t entity_id) const;

	[[nodiscard]] bool IsNis(std::uint64_t entity_id) const;
	[[nodiscard]] float GetShipScreenSize(std::uint64_t entity_id) const;
	[[nodiscard]] float GetShipNormalizedScreenSize(std::uint64_t entity_id) const;
	[[nodiscard]] float GetShipAudioSignificance(std::uint64_t entity_id) const;
	[[nodiscard]] std::int32_t GetSquadronID(std::uint64_t entity_id) const;
	[[nodiscard]] bool IsSquadronLeader(std::uint64_t entity_id) const;
	[[nodiscard]] std::uint64_t GetSquadronLeader(std::uint64_t entity_id) const;
	[[nodiscard]] std::string GetPilotName(std::uint64_t entity_id) const;
	[[nodiscard]] std::string GetLocalizedUnitName(std::uint64_t entity_id) const;
	[[nodiscard]] std::string GetLocalizedUnitDescription(std::uint64_t entity_id) const;
	[[nodiscard]] std::string GetLocalizedUnitFlavourText(std::uint64_t entity_id) const;
	[[nodiscard]] std::string GetCreationMap(std::uint64_t entity_id) const;
	[[nodiscard]] float GetAudioFocusWeight(std::uint64_t entity_id) const;
	[[nodiscard]] float GetAudioFocusWeightContextualMultiplier(std::uint64_t entity_id) const;
	[[nodiscard]] std::int32_t GetAudioFocusRank(std::uint64_t entity_id) const;
	[[nodiscard]] float GetAudioFocusRankNormalized(std::uint64_t entity_id) const;
	[[nodiscard]] std::int32_t GetControlGroupsFlags(std::uint64_t entity_id) const;
	[[nodiscard]] bool IsCenterFocused(std::uint64_t entity_id) const;
	[[nodiscard]] TurretDeploymentState GetDeployState(std::uint64_t entity_id) const;
	[[nodiscard]] std::tuple<double, double, double> GetDeployLocation(std::uint64_t entity_id) const;
	[[nodiscard]] std::tuple<double, double, double> GetDeployNormal(std::uint64_t entity_id) const;
	[[nodiscard]] bool IsDeployedInTacticalPause(std::uint64_t entity_id) const;
	[[nodiscard]] bool IsLatched(std::uint64_t entity_id) const;
	[[nodiscard]] float GetWeaponRange(std::uint64_t entity_id) const;
	[[nodiscard]] float GetSpecialWeaponRange(std::uint64_t entity_id) const;
	[[nodiscard]] float GetHealWeaponRange(std::uint64_t entity_id) const;
	[[nodiscard]] float GetHealSpecialWeaponRange(std::uint64_t entity_id) const;
	[[nodiscard]] float GetHyperspaceProgress(std::uint64_t entity_id) const;
	[[nodiscard]] std::uint64_t GetOpposingShip(std::uint64_t entity_id) const;
	[[nodiscard]] float GetZombieTime(std::uint64_t entity_id) const;
	[[nodiscard]] std::tuple<bool, bool, bool, bool> GetDeathModifiers(std::uint64_t entity_id) const;
	[[nodiscard]] float GetSignificance(std::uint64_t entity_id) const;
	[[nodiscard]] float GetDistanceToCamera(std::uint64_t entity_id) const;
	[[nodiscard]] float GetBackstageEffectiveness(std::uint64_t entity_id) const;
	[[nodiscard]] std::uint64_t GetDockWith(std::uint64_t entity_id) const;
	[[nodiscard]] DockingStage GetDockingStage(std::uint64_t entity_id) const;
	[[nodiscard]] bool IsDocked(std::uint64_t entity_id) const;
	[[nodiscard]] bool IsDocking(std::uint64_t entity_id) const;
	[[nodiscard]] bool HasPower(std::uint64_t entity_id) const;
	[[nodiscard]] bool IsHandlingExternalMove(std::uint64_t entity_id) const;
	[[nodiscard]] bool CanRally(std::uint64_t entity_id) const;
	[[nodiscard]] HyperspaceStatus GetHyperspaceStatus(std::uint64_t entity_id) const;
	[[nodiscard]] std::uint64_t GetParent(std::uint64_t entity_id) const;
	[[nodiscard]] sol::table GetCollectors(std::uint64_t entity_id) const;
	[[nodiscard]] sol::table GetAnimationStates(std::uint64_t entity_id) const;
	[[nodiscard]] UCommandType GetActiveCommandType(std::uint64_t entity_id) const;
	[[nodiscard]] std::tuple<double, double, double> GetShipVelocity(std::uint64_t entity_id) const;
private:
	sol::state_view* lua = nullptr;
	SobGroupManager* sob_group_manager = nullptr;
	Database* database = nullptr;
	LuaInterface* lua_interface = nullptr;
	UnitsInfoSubsystem units_info_subsystem = nullptr;
	TiirEntityFunctionLibrary* lib = nullptr;
};