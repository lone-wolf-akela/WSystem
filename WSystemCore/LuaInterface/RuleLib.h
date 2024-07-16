#pragma once
#include <cstdint>
#include <string>
#include <string_view>

#include <sol/sol.hpp>
#undef check
#include <boost/heap/fibonacci_heap.hpp>
#include <plf_colony.h>

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

	boost::heap::fibonacci_heap<ScriptIntervalRule>::handle_type Handle;

	friend bool operator<(const ScriptIntervalRule& lhs, const ScriptIntervalRule& rhs)
	{
		return lhs.NextTick > rhs.NextTick;
	}
};

struct ScriptParamIntervalRule : ScriptParamRule
{
	std::int64_t TickInterval;
	std::int64_t NextTick;
	bool Repeat;

	boost::heap::fibonacci_heap<ScriptParamIntervalRule>::handle_type Handle;

	friend bool operator<(const ScriptParamIntervalRule& lhs, const ScriptParamIntervalRule& rhs)
	{
		return lhs.NextTick > rhs.NextTick;
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
	bool IsRuleExists(std::string_view name);
	bool IsRuleParamExists(std::string_view name, std::string_view param);
	
	
	void ResetTickTimer();
	void Tick();
	void BindLuaState(sol::state_view* lua);
private:
	sol::state_view* lua = nullptr;
	std::int64_t current_tick = 0;
	boost::heap::fibonacci_heap<ScriptIntervalRule> interval_rules;
	boost::heap::fibonacci_heap<ScriptParamIntervalRule> param_interval_rules;
	plf::colony<ScriptRule> normal_rules;
	plf::colony<ScriptParamRule> param_rules;

	void AddRuleInterval_Impl(std::string_view name, std::int64_t interval, bool repeat);
	void AddRuleParamInterval_Impl(std::string_view name, std::string_view param, std::int64_t interval, bool repeat);

	bool IsTopIntervalRuleReady() const;
	bool IsTopParamIntervalRuleReady() const;
	sol::protected_function FindFunc(std::string_view name) const;
};