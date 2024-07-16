#include <format>
#include <stdexcept>

#include "RuleLib.h"

#include "DynamicOutput/Output.hpp"

void ScriptRule::Call() const
{
	if (!Func.valid())
	{
		throw std::runtime_error("Invalid function");
	}
	if (const auto result = Func(); !result.valid())
	{
		const sol::error err = result;
		const auto error_msg = std::format("Error in {}: {}", Name, err.what());
		throw std::runtime_error(error_msg);
	}
}

void ScriptParamRule::Call() const
{
	if (!Func.valid())
	{
		throw std::runtime_error("Invalid function");
	}
	if (const auto result = Func(Param); !result.valid())
	{
		const sol::error err = result;
		const auto error_msg = std::format("Error in {}.{}: {}", Name, Param, err.what());
		throw std::runtime_error(error_msg);
	}
}

void ScriptRuleManager::AddRule(std::string_view name)
{
	if (IsRuleExists(name))
	{
		const auto err_msg = std::format("AddRule failed: rule with name `{}` already exists", name);
		throw std::runtime_error(err_msg);
	}

	ScriptRule rule;
	rule.Name = name;
	rule.Func = FindFunc(name);

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

void ScriptRuleManager::AddRuleParam(std::string_view name, std::string_view param)
{
	if (IsRuleParamExists(name, param))
	{
		const auto err_msg = std::format("AddRuleParam failed: rule with name `{}` and param `{}` already exists", name, param);
	}

	ScriptParamRule rule;
	rule.Name = name;
	rule.Param = param;
	rule.Func = FindFunc(name);

	param_rules.insert(std::move(rule));
}

void ScriptRuleManager::AddRuleParamInterval(std::string_view name, std::string_view param, std::int64_t interval)
{
	AddRuleParamInterval_Impl(name, param, interval, true);
}

void ScriptRuleManager::AddRuleParamIntervalOneTime(std::string_view name, std::string_view param, std::int64_t interval)
{
	AddRuleParamInterval_Impl(name, param, interval, false);
}

void ScriptRuleManager::AddRuleInterval_Impl(std::string_view name, std::int64_t interval, bool repeat)
{
	if (IsRuleExists(name))
	{
		const auto err_msg = std::format("AddRule failed: rule with name `{}` already exists", name);
		throw std::runtime_error(err_msg);
	}

	ScriptIntervalRule rule;
	rule.Name = name;
	rule.Func = FindFunc(name);
	rule.TickInterval = interval;
	rule.NextTick = current_tick + interval;
	rule.Repeat = repeat;

	const auto h = interval_rules.emplace(std::move(rule));
	(*h).Handle = h;
}

void ScriptRuleManager::AddRuleParamInterval_Impl(std::string_view name, std::string_view param, std::int64_t interval, bool repeat)
{
	if (IsRuleParamExists(name, param))
	{
		const auto err_msg = std::format("AddRuleParam failed: rule with name `{}` and param `{}` already exists", name, param);
		throw std::runtime_error(err_msg);
	}

	ScriptParamIntervalRule rule;
	rule.Name = name;
	rule.Param = param;
	rule.Func = FindFunc(name);
	rule.TickInterval = interval;
	rule.NextTick = current_tick + interval;
	rule.Repeat = repeat;

	const auto h = param_interval_rules.emplace(std::move(rule));
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
	const auto err_msg = std::format("RemoveRule failed: rule `{}` not found", name);
	throw std::runtime_error(err_msg);
}

void ScriptRuleManager::RemoveRuleParam(std::string_view name, std::string_view param)
{
	for (auto it = begin(param_rules); it != end(param_rules); ++it)
	{
		if (it->Name == name && it->Param == param)
		{
			param_rules.erase(it);
			return;
		}
	}
	for (auto& rule : param_interval_rules)
	{
		if (rule.Name == name && rule.Param == param)
		{
			param_interval_rules.erase(rule.Handle);
			return;
		}
	}
	const auto err_msg = std::format("RemoveRuleParam failed: rule `{}` with param `{}` not found", name, param);
	throw std::runtime_error(err_msg);
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

bool ScriptRuleManager::IsRuleParamExists(std::string_view name, std::string_view param)
{
	for (const auto& rule : param_rules)
	{
		if (rule.Name == name && rule.Param == param)
		{
			return true;
		}
	}
	for (const auto& rule : param_interval_rules)
	{
		if (rule.Name == name && rule.Param == param)
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
		rule.Call();
	}
	for (auto& rule : param_rules)
	{
		rule.Call();
	}
	while (IsTopIntervalRuleReady())
	{
		auto& rule = interval_rules.top();
		rule.Call();
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
	while (IsTopParamIntervalRuleReady())
	{
		auto& rule = param_interval_rules.top();
		rule.Call();
		if (rule.Repeat)
		{
			(*rule.Handle).NextTick += rule.TickInterval;
			param_interval_rules.update(rule.Handle);
		}
		else
		{
			param_interval_rules.pop();
		}
	}
}

void ScriptRuleManager::BindLuaState(sol::state_view* lua)
{
	this->lua = lua;

	auto rule_manager_t = lua->new_usertype<ScriptRuleManager>(
		"Rule",
		// functions
		"Add", &ScriptRuleManager::AddRule,
		"AddInterval", &ScriptRuleManager::AddRuleInterval,
		"AddIntervalOneTime", &ScriptRuleManager::AddRuleIntervalOneTime,
		"AddParam", &ScriptRuleManager::AddRuleParam,
		"AddParamInterval", &ScriptRuleManager::AddRuleParamInterval,
		"AddParamIntervalOneTime", &ScriptRuleManager::AddRuleParamIntervalOneTime,
		"Remove", &ScriptRuleManager::RemoveRule,
		"RemoveParam", &ScriptRuleManager::RemoveRuleParam,
		"Exists", &ScriptRuleManager::IsRuleExists,
		"ParamExists", &ScriptRuleManager::IsRuleParamExists
	);
}

bool ScriptRuleManager::IsTopIntervalRuleReady() const
{
	if (interval_rules.empty())
	{
		return false;
	}

	return interval_rules.top().NextTick <= current_tick;
}

bool ScriptRuleManager::IsTopParamIntervalRuleReady() const
{
	if (param_interval_rules.empty())
	{
		return false;
	}

	return param_interval_rules.top().NextTick <= current_tick;
}

sol::protected_function ScriptRuleManager::FindFunc(std::string_view name) const
{
	if (!lua)
	{
		throw std::runtime_error("Error: lua state not initialized.");
	}
	auto func = (*lua)[name];
	if (!func.valid())
	{
		const auto err_msg = std::format("Error: function `{}` not found in Lua", name);
		throw std::runtime_error(err_msg);
	}
	return func;
}
