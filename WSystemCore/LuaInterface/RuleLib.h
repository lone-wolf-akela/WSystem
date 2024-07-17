#pragma once
#include <compare>
#include <cstdint>
#include <string>
#include <string_view>
#include <map>

#include <sol/sol.hpp>

struct ScriptRule
{
	std::string Name;
	sol::protected_function Func;
	void Call() const;
};

struct ScriptParamRule : ScriptRule
{
	std::string Param;
	void Call() const;
};


struct ScriptIntervalRule : ScriptRule
{
	std::int64_t TickInterval;
	std::int64_t NextTick;
	bool Repeat;
};

struct ScriptParamIntervalRule : ScriptParamRule
{
	std::int64_t TickInterval;
	std::int64_t NextTick;
	bool Repeat;
};

struct NameParamPairView
{
	std::string_view Name;
	std::string_view Param;
	friend std::strong_ordering operator<=>(const NameParamPairView&, const NameParamPairView&) = default;
};

struct NameParamPair
{
	std::string Name;
	std::string Param;
	friend std::strong_ordering operator<=>(const NameParamPair&, const NameParamPair&) = default;
	friend std::strong_ordering operator<=>(const NameParamPair& lhs, const NameParamPairView& rhs)
	{
		return NameParamPairView{ lhs.Name, lhs.Param } <=> rhs;
	}
	friend std::strong_ordering operator<=>(const NameParamPairView& lhs, const NameParamPair& rhs)
	{
		return lhs <=> NameParamPairView{ rhs.Name, rhs.Param };
	}
};

class ScriptRuleManager
{
public:
	ScriptRuleManager() = default;

	ScriptRuleManager(const ScriptRuleManager& o) = delete;
	ScriptRuleManager& operator=(const ScriptRuleManager& o) = delete;
	ScriptRuleManager(ScriptRuleManager&& o) noexcept = default;
	ScriptRuleManager& operator=(ScriptRuleManager&& o) noexcept = default;
	~ScriptRuleManager() = default;


	void AddRule(std::string_view name);
	void AddRuleInterval(std::string_view name, std::int64_t interval);
	void AddRuleIntervalOneTime(std::string_view name, std::int64_t interval);
	void AddRuleParam(std::string_view name, std::string_view param);
	void AddRuleParamInterval(std::string_view name, std::string_view param, std::int64_t interval);
	void AddRuleParamIntervalOneTime(std::string_view name, std::string_view param, std::int64_t interval);
	void RemoveRule(std::string_view name);
	void RemoveRuleParam(std::string_view name, std::string_view param);
	[[nodiscard]] bool IsRuleExists(std::string_view name) const;
	[[nodiscard]] bool IsRuleParamExists(std::string_view name, std::string_view param) const;
	
	
	void ResetTickTimer();
	void Tick();
	void BindLuaState(sol::state_view* lua);
private:
	sol::state_view* lua = nullptr;
	std::int64_t current_tick = 0;
	std::map<std::string, ScriptIntervalRule, std::less<>> interval_rules;
	std::map<NameParamPair, ScriptParamIntervalRule, std::less<>> param_interval_rules;
	std::map<std::string, ScriptRule, std::less<>> normal_rules;
	std::map<NameParamPair, ScriptParamRule, std::less<>> param_rules;

	void AddRuleInterval_Impl(std::string_view name, std::int64_t interval, bool repeat);
	void AddRuleParamInterval_Impl(std::string_view name, std::string_view param, std::int64_t interval, bool repeat);

	[[nodiscard]] sol::protected_function FindFunc(std::string_view name) const;
};