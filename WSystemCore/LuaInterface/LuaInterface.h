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
	void AddResearchCondition(
		std::string_view target_research, 
		std::string_view all_of_units, 
		std::string_view none_of_units,
		std::string_view all_of_researches,
		std::string_view none_of_researches) const;
private:
	WSystemCore* wsystem_core;
};