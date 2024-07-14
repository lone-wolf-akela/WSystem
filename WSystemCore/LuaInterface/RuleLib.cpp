#include <boost/nowide/convert.hpp>

#include <DynamicOutput/Output.hpp>

#include "RuleLib.h"

void ScriptRuleManager::AddRule(std::string_view name)
{
	if (!lua)
	{
		RC::Output::send<RC::LogLevel::LogLevel::Error>(STR("Error: lua state not initialized.\n"));
		return;
	}

	if (IsRuleExists(name))
	{
		RC::Output::send<RC::LogLevel::LogLevel::Error>(
			STR("AddRule failed: rule with name `{}` already exists\n"),
			boost::nowide::widen(name));
		return;
	}

	ScriptRule rule;
	rule.Name = name;
	rule.Func = (*lua)[name];

	if (!rule.Func.valid())
	{
		RC::Output::send<RC::LogLevel::LogLevel::Error>(
			STR("AddRule failed: invalid rule name `{}`\n"), 
			boost::nowide::widen(name));
		return;
	}

	normal_rules.insert(std::move(rule));
}

void ScriptRuleManager::AddRuleInterval(std::string_view name, std::int64_t interval)
{
	AddRuleInterval_Impl(name, interval, true);
}

void ScriptRuleManager::AddRuleIntervalOneTime(std::string_view name, std::int64_t interval)
{
	AddRuleInterval_Impl(name, interval, false);
}

void ScriptRuleManager::AddRuleInterval_Impl(std::string_view name, std::int64_t interval, bool repeat)
{
	if (!lua)
	{
		RC::Output::send<RC::LogLevel::LogLevel::Error>(STR("Error: lua state not initialized.\n"));
		return;
	}

	if (IsRuleExists(name))
	{
		RC::Output::send<RC::LogLevel::LogLevel::Error>(
			STR("AddRule failed: rule with name `{}` already exists\n"),
			boost::nowide::widen(name));
		return;
	}

	ScriptIntervalRule rule;
	rule.Name = name;
	rule.Func = (*lua)[name];
	rule.TickInterval = interval;
	rule.NextTick = current_tick + interval;
	rule.Repeat = repeat;

	if (!rule.Func.valid())
	{
		RC::Output::send<RC::LogLevel::LogLevel::Error>(
			STR("AddRuleInterval failed: invalid rule name `{}`\n"),
			boost::nowide::widen(name));
		return;
	}

	const auto h = interval_rules.emplace(std::move(rule));
	(*h).Handle = h;
}

void ScriptRuleManager::RemoveRule(std::string_view name)
{
	for (auto it = begin(normal_rules); it != end(normal_rules); ++it)
	{
		if (it->Name == name)
		{
			normal_rules.erase(it);
			return;
		}
	}
	for (auto& rule : interval_rules)
	{
		if (rule.Name == name)
		{
			interval_rules.erase(rule.Handle);
			return;
		}
	}
	RC::Output::send<RC::LogLevel::LogLevel::Error>(
		STR("RemoveRule failed: rule `{}` not found\n"),
		boost::nowide::widen(name));
}

bool ScriptRuleManager::IsRuleExists(std::string_view name)
{
	for (const auto& rule : normal_rules)
	{
		if (rule.Name == name)
		{
			return true;
		}
	}
	for (const auto& rule : interval_rules)
	{
		if (rule.Name == name)
		{
			return true;
		}
	}
	return false;
}

void ScriptRuleManager::ResetTickTimer()
{
	current_tick = 0;
}

void ScriptRuleManager::Tick()
{
	current_tick++;
	for(auto& rule : normal_rules)
	{
		if (const auto result = rule.Func(); !result.valid())
		{
			const sol::error err = result;
			RC::Output::send<RC::LogLevel::LogLevel::Error>(
				STR("Error in rule `{}`: {}\n"), 
				boost::nowide::widen(rule.Name),
				boost::nowide::widen(err.what()));
		}
	}
	while (IsTopIntervalRuleReady())
	{
		auto& rule = interval_rules.top();
		if (const auto result = rule.Func(); !result.valid())
		{
			const sol::error err = result;
			RC::Output::send<RC::LogLevel::LogLevel::Error>(
				STR("Error in rule `{}`: {}\n"),
				boost::nowide::widen(rule.Name),
				boost::nowide::widen(err.what()));
		}
		if (rule.Repeat)
		{
			(*rule.Handle).NextTick += rule.TickInterval;
			interval_rules.update(rule.Handle);
		}
		else
		{
			interval_rules.pop();
		}
	}
}

void ScriptRuleManager::BindLuaState(sol::state_view* lua)
{
	this->lua = lua;
}

bool ScriptRuleManager::IsTopIntervalRuleReady() const
{
	if (interval_rules.empty())
	{
		return false;
	}

	return interval_rules.top().NextTick <= current_tick;
}
