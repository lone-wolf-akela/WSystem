#pragma once
#include <pch.h>

#include "TiirEntityFunctionLibrary.h"
#include "TiirEntityGroupFunctionLibrary.h"
#include "TiirPlayerFunctionLibrary.h"
#include "TiirResearchFunctionLibrary.h"
#include "SimOrderFactory.h"

class FunctionLibs
{
public:
	void Init();

	TiirEntityFunctionLibrary Entity;
	TiirEntityGroupFunctionLibrary EntityGroup;
	TiirPlayerFunctionLibrary Player;
	TiirResearchFunctionLibrary Research;
	SimOrderFactory OrderFactory;
};