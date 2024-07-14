#pragma once

#include "TiirEntityFunctionLibrary.h"
#include "TiirEntityGroupFunctionLibrary.h"
#include "TiirPlayerFunctionLibrary.h"
#include "TiirResearchFunctionLibrary.h"

class FunctionLibs
{
public:
	void Init();

	TiirEntityFunctionLibrary Entity;
	TiirEntityGroupFunctionLibrary EntityGroup;
	TiirPlayerFunctionLibrary Player;
	TiirResearchFunctionLibrary Research;
};