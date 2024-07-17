#pragma once
#include <cstdint>
#include <string>
#include <string_view>
#include <map>
#include <vector>

#include <sol/sol.hpp>

#include <Core/Database.h>
#include <LibWrapper/TiirEntityGroupFunctionLibrary.h>

class SobGroupManager
{
public:
	SobGroupManager() = default;

	SobGroupManager(const SobGroupManager& o) = delete;
	SobGroupManager& operator=(const SobGroupManager& o) = delete;
	SobGroupManager(SobGroupManager&& o) noexcept = default;
	SobGroupManager& operator=(SobGroupManager&& o) noexcept = default;

	~SobGroupManager() = default;

	void BindLuaState(sol::state_view* lua, TiirEntityGroupFunctionLibrary* lib, Database* database);
	TiirEntityGroup& FindGroup(std::string_view name);
	void SetGroup(std::string_view name, TiirEntityGroup&& group);
	void SetGroup(std::string_view name, const TiirEntityGroup& group);

	bool CreateOrClear(std::string_view name);
	bool CreateIfNotExists(std::string_view name);
	bool IsExists(std::string_view name) const;
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
		bool skip_placement_logic);
	void Teleport(
		std::string_view group,
		double dest_rotation_w, double dest_rotation_x, double dest_rotation_y, double dest_rotation_z,
		double dest_position_x, double dest_position_y, double dest_position_z,
		double scale_x, double scale_y, double scale_z,
		bool skip_placement_logic);
	std::int32_t FillGroupFromFilteredType(
		std::string_view group,
		std::string_view source_group,
		sol::table desired_types);
	std::int32_t GroupCount(std::string_view group);
	void TakeDamageAbsolute(std::string_view group, float damage_absolute);
	void TakeDamage(std::string_view group, float damage_percentage);
	void Stop(std::string_view group);
	void SetVelocity(std::string_view group, double x, double y, double z);
private:
	sol::state_view* lua = nullptr;
	TiirEntityGroupFunctionLibrary* lib = nullptr;
	Database* database = nullptr;
	std::map<std::string, TiirEntityGroup, std::less<>> groups;
};
