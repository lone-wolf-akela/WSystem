#pragma once
#include <pch.h>

#include <DataWrapper/ResearchStaticData.h>

#include "LibBase.h"
#include "LibDataTypes.h"

class TiirResearchFunctionLibrary : public LibBase<TiirResearchFunctionLibrary>
{
public:
	static constexpr auto LibPath = STR("/Script/RavenSimulation.TiirResearchFunctionLibrary");
	
	WSYS_MEMBER_FUNCTION(bool, UnrestrictResearchForPlayer, std::int32_t, player_index, UResearchStaticData, research_static_data)

	WSYS_MEMBER_FUNCTION(bool, UnlockResearchForPlayer, std::int32_t, player_index, UResearchStaticData, research_static_data)

	WSYS_MEMBER_FUNCTION_VOID(UnlockAllResearchForPlayer, std::int32_t, player_index)

	WSYS_MEMBER_FUNCTION(bool, StartResearchForPlayer, std::int32_t, player_index, UResearchStaticData, research_static_data)

	WSYS_MEMBER_FUNCTION_VOID(RestrictResearchTechTreeForPlayer, std::int32_t, player_index, bool, restrict_tech_tree)

	WSYS_MEMBER_FUNCTION(bool, RestrictResearchForPlayer, std::int32_t, player_index, UResearchStaticData, research_static_data)

	WSYS_MEMBER_FUNCTION_VOID(RestrictAllResearchForPlayer, std::int32_t, player_index)

	WSYS_MEMBER_FUNCTION(bool, NotEqual_TiirResearchTiirResearch, const TiirResearch&, a, const TiirResearch&, b)

	WSYS_MEMBER_FUNCTION(bool, MoveResearchToTopForPlayer, std::int32_t, player_index, UResearchStaticData, research_static_data)

	WSYS_MEMBER_FUNCTION(bool, IsResearchOfType, const TiirResearch&, research_id, UResearchStaticData, research_type)

	WSYS_MEMBER_FUNCTION(bool, IsResearchOfAnyType, const TiirResearch&, research_id, const UC::TArray<UResearchStaticData>&, research_type_list)

	WSYS_MEMBER_FUNCTION(bool, HasPlayerCompletedResearch, std::int32_t, player_index, UResearchStaticData, research_static_data)

	WSYS_MEMBER_FUNCTION(TiirResearch, GetResearchID, UResearchStaticData, research_type)

	WSYS_MEMBER_FUNCTION(bool, EqualEqual_TiirResearchTiirResearch, const TiirResearch&, a, const TiirResearch&, b)

	WSYS_MEMBER_FUNCTION_VOID(CancelResearchForPlayer, std::int32_t, player_index, UResearchStaticData, research_static_data)

	WSYS_MEMBER_FUNCTION_VOID(CancelAllResearchForPlayer, std::int32_t, player_index)

	// todo: bind to lua
	WSYS_MEMBER_FUNCTION_VOID(SetMaxActiveResearchPerFamily, std::int32_t, player_index, std::int32_t, max_active_research)

	// todo: bind to lua
	WSYS_MEMBER_FUNCTION_VOID(SetMaxActiveResearch, std::int32_t, player_index, std::int32_t, max_active_research)
};
