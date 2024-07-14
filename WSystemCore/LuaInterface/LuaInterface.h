#pragma once
#include <string>
#include <string_view>

class WSystemCore;

class LuaInterface
{
public:
	explicit LuaInterface(WSystemCore* wsystem_core);

	LuaInterface(const LuaInterface& o);
	LuaInterface& operator=(const LuaInterface& o);
	LuaInterface(LuaInterface&& o) noexcept;
	LuaInterface& operator=(LuaInterface&& o) noexcept;

	~LuaInterface() = default;

	void Initialize();
	void ScanForResearchConditions() const;
	void Rule_OnInit() const;

	// interface part
public:
	// research manage
	void AddResearchCondition(
		std::string_view target_research, 
		std::string_view all_of_units, 
		std::string_view none_of_units,
		std::string_view all_of_researches,
		std::string_view none_of_researches) const;
	// rule manage
	void AddRule(std::string_view name) const;
	void AddRuleInterval(std::string_view name, std::int64_t interval) const;
	void AddRuleIntervalOneTime(std::string_view name, std::int64_t interval) const;
	void RemoveRule(std::string_view name) const;
	bool IsRuleExists(std::string_view name) const;
private:
	WSystemCore* wsystem_core;
};