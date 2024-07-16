#include <format>
#include <stdexcept>

#include "RuleLib.h"

#include <ranges>

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

	normal_rules.emplace(name, std::move(rule));
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

	param_rules.emplace(NameParamPair{ std::string(name), std::string(param) }, std::move(rule));
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

	interval_rules.emplace(name, std::move(rule));
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

	param_interval_rules.emplace(NameParamPair{ std::string(name), std::string(param) }, std::move(rule));
}

void ScriptRuleManager::RemoveRule(std::string_view name)
{
	if (const auto found = normal_rules.find(name); found != normal_rules.end())
	{
		normal_rules.erase(found);
		return;
	}
	if (const auto found = interval_rules.find(name); found != interval_rules.end())
	{
		interval_rules.erase(found);
		return;
	}

	const auto err_msg = std::format("RemoveRule failed: rule `{}` not found", name);
	throw std::runtime_error(err_msg);
}

void ScriptRuleManager::RemoveRuleParam(std::string_view name, std::string_view param)
{
	if (const auto found = param_rules.find(NameParamPairView{ name, param }); found != param_rules.end())
	{
		param_rules.erase(found);
		return;
	}
	if (const auto found = param_interval_rules.find(NameParamPairView{ name, param }); found != param_interval_rules.end())
	{
		param_interval_rules.erase(found);
		return;
	}
	
	const auto err_msg = std::format("RemoveRuleParam failed: rule `{}` with param `{}` not found", name, param);
	throw std::runtime_error(err_msg);
}

bool ScriptRuleManager::IsRuleExists(std::string_view name) const
{
	return normal_rules.contains(name) || interval_rules.contains(name);
}

bool ScriptRuleManager::IsRuleParamExists(std::string_view name, std::string_view param) const
{
	return param_rules.contains(NameParamPairView{ name, param }) || param_interval_rules.contains(NameParamPairView{ name, param });
}

void ScriptRuleManager::ResetTickTimer()
{
	current_tick = 0;
}

void ScriptRuleManager::Tick()
{
	current_tick++;
	for(auto& rule : normal_rules | std::views::values)
	{
		rule.Call();
	}
	for (auto& rule : param_rules | std::views::values)
	{
		rule.Call();
	}
	std::vector<std::string> to_remove_names;
	for(auto& [name, rule] : interval_rules)
	{
		if (rule.NextTick <= current_tick)
		{
			rule.Call();
			if (rule.Repeat)
			{
				rule.NextTick += rule.TickInterval;
			}
			else
			{
				to_remove_names.push_back(name);
			}
		}
	}
	for(auto& name : to_remove_names)
	{
		interval_rules.erase(name);
	}

	std::vector<NameParamPair> to_remove_name_params;
	for(auto& [name_param, rule] : param_interval_rules)
	{
		if (rule.NextTick <= current_tick)
		{
			rule.Call();
			if (rule.Repeat)
			{
				rule.NextTick += rule.TickInterval;
			}
			else
			{
				to_remove_name_params.push_back(name_param);
			}
		}
	}
	for(auto& name_param : to_remove_name_params)
	{
		param_interval_rules.erase(name_param);
	}
}

void ScriptRuleManager::BindLuaState(sol::state_view* lua)
{
	this->lua = lua;

	auto rule_manager_t = lua->new_usertype<ScriptRuleManager>(
		"ScriptRuleManagerType",
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
