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
	void RemoveRule(std::string_view name);
	bool IsRuleExists(std::string_view name);
	void ResetTickTimer();
	void Tick();
	void BindLuaState(sol::state_view* lua);

private:
	sol::state_view* lua = nullptr;
	std::int64_t current_tick = 0;
	boost::heap::fibonacci_heap<ScriptIntervalRule> interval_rules;
	plf::colony<ScriptRule> normal_rules;

	void AddRuleInterval_Impl(std::string_view name, std::int64_t interval, bool repeat);

	bool IsTopIntervalRuleReady() const;
};