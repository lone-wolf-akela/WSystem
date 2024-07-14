#pragma once
#include <cstdint>
#include <string>
#include <string_view>

#include <sol/sol.hpp>
#undef check
#include <boost/heap/fibonacci_heap.hpp>
#include <plf_colony.h>

struct WSysRule
{
	std::string Name;
	sol::protected_function Func;
};

struct WSysIntervalRule : WSysRule
{
	std::int64_t TickInterval;
	std::int64_t NextTick;
	bool Repeat;

	boost::heap::fibonacci_heap<WSysIntervalRule>::handle_type Handle;

	friend bool operator<(const WSysIntervalRule& lhs, const WSysIntervalRule& rhs)
	{
		return lhs.NextTick > rhs.NextTick;
	}
};

class WSysRuleManager
{
public:
	explicit WSysRuleManager(std::optional<sol::state_view>* lua);
	void AddRule(std::string_view name);
	void AddRuleInterval(std::string_view name, std::int64_t interval);
	void AddRuleIntervalOneTime(std::string_view name, std::int64_t interval);
	void RemoveRule(std::string_view name);
	bool IsRuleExists(std::string_view name);
	void ResetTickTimer();
	void Tick();
private:
	std::optional<sol::state_view>* lua;
	std::int64_t current_tick = 0;
	boost::heap::fibonacci_heap<WSysIntervalRule> interval_rules;
	plf::colony<WSysRule> normal_rules;

	void AddRuleInterval_Impl(std::string_view name, std::int64_t interval, bool repeat);

	bool IsTopIntervalRuleReady() const;
};