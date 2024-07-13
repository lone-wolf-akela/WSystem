#pragma once
#include <string>
#include <string_view>

class WSystemCore;

class LuaInterface
{
public:
	explicit LuaInterface(WSystemCore* wsystem_core);

	void Initialize();
	void ScanForResearchConditions() const;

	// interface part
public:
	void AddResearchCondition(std::string_view research_name, std::string_view all_of, std::string_view none_of) const;
private:
	WSystemCore* wsystem_core;
};