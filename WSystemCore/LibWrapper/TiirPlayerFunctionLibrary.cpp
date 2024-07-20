#include <pch.h>
#include "TiirPlayerFunctionLibrary.h"

bool TiirPlayerFunctionLibrary::GetPlayerFromIndex(std::int32_t player_index, TiirCommander& player, const std::source_location& location) const
{
	const auto func = FindFunction(STR("GetPlayerFromIndex"), location);
	struct {
		std::int32_t player_index;
		TiirCommander player;
		bool result;
	} args{
		player_index,
		player,
		{}
	};
	lib_class->ProcessEvent(func, &args);
	player = args.player;
	return args.result;
}
