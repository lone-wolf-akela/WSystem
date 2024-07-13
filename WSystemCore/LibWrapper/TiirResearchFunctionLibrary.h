#pragma once
#include <cstdint>

#include <ThirdParty/UnrealContainers/UnrealContainers.h>

#include <DataWrapper/ResearchStaticData.h>

#include "LibBase.h"

struct TiirResearch 
{
	std::uint32_t ResearchID;
};

class TiirResearchFunctionLibrary : public LibBase<TiirResearchFunctionLibrary>
{
public:
	static constexpr auto LibPath = STR("/Script/RavenSimulation.TiirResearchFunctionLibrary");
	
	WSYS_MEMBER_FUNCTION(bool, UnrestrictResearchForPlayer, std::int32_t, player_index, ResearchStaticData, research_static_data)
	WSYS_MEMBER_FUNCTION(bool, UnlockResearchForPlayer, std::int32_t, player_index, ResearchStaticData, research_static_data)
	WSYS_MEMBER_FUNCTION(bool, StartResearchForPlayer, std::int32_t, player_index, ResearchStaticData, research_static_data)
	WSYS_MEMBER_FUNCTION_VOID(CancelResearchForPlayer, std::int32_t, player_index, ResearchStaticData, research_static_data)
	WSYS_MEMBER_FUNCTION(bool, RestrictResearchForPlayer, std::int32_t, player_index, ResearchStaticData, research_static_data)
	WSYS_MEMBER_FUNCTION(bool, MoveResearchToTopForPlayer, std::int32_t, player_index, ResearchStaticData, research_static_data)

	WSYS_MEMBER_FUNCTION(bool, HasPlayerCompletedResearch, std::int32_t, player_index, ResearchStaticData, research_static_data)

	WSYS_MEMBER_FUNCTION_VOID(UnlockAllResearchForPlayer, std::int32_t, player_index)
	WSYS_MEMBER_FUNCTION_VOID(CancelAllResearchForPlayer, std::int32_t, player_index)
	WSYS_MEMBER_FUNCTION_VOID(RestrictAllResearchForPlayer, std::int32_t, player_index)
	WSYS_MEMBER_FUNCTION_VOID(RestrictResearchTechTreeForPlayer, std::int32_t, player_index, bool, restrict_tech_tree)
	
	
	WSYS_MEMBER_FUNCTION(bool, NotEqual_TiirResearchTiirResearch, TiirResearch&, a, TiirResearch&, b)
	WSYS_MEMBER_FUNCTION(bool, EqualEqual_TiirResearchTiirResearch, TiirResearch&, a, TiirResearch&, b)

	WSYS_MEMBER_FUNCTION(bool, IsResearchOfType, TiirResearch&, research_id, ResearchStaticData, research_type)
	WSYS_MEMBER_FUNCTION(bool, IsResearchOfAnyType, TiirResearch&, research_id, UC::TArray<ResearchStaticData>*, research_type_list)
	
	WSYS_MEMBER_FUNCTION(TiirResearch, GetResearchID, ResearchStaticData, research_type)
};
